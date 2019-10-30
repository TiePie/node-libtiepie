/**
 * OscilloscopeBlock.js - for LibTiePie 0.7+
 *
 * This example performs a block mode measurment and writes the data to OscilloscopeBlock.csv.
 *
 * Find more information on http://www.tiepie.com/LibTiePie .
 */

"use strict";

const libtiepie = require('libtiepie');
const sleep = require('sleep');
const fs = require('fs');
const EOL = require('os').EOL;

// Enable network search:
libtiepie.api.NetSetAutoDetectEnabled(true);

// Update device list:
libtiepie.api.LstUpdate();

// Try to open an oscilloscope with block measurement support:
var scp = libtiepie.const.TPDEVICEHANDLE_INVALID;

for(let index = 0; index < libtiepie.api.LstGetCount(); index++)
{
  if(libtiepie.api.LstDevCanOpen(libtiepie.const.IDKIND_INDEX, index, libtiepie.const.DEVICETYPE_OSCILLOSCOPE))
  {
    scp = libtiepie.api.LstOpenOscilloscope(libtiepie.const.IDKIND_INDEX, index);

    // Check for valid handle and block measurement support:
    if(scp != libtiepie.const.TPDEVICEHANDLE_INVALID && (libtiepie.api.ScpGetMeasureModes(scp) & libtiepie.const.MM_BLOCK))
    {
      break;
    }
    else
    {
      scp = libtiepie.const.TPDEVICEHANDLE_INVALID;
    }
  }
}

if(scp != libtiepie.const.TPDEVICEHANDLE_INVALID)
{
  // Get the number of channels:
  const channelCount = libtiepie.api.ScpGetChannelCount(scp);

  // Set measure mode:
  libtiepie.api.ScpSetMeasureMode(scp, libtiepie.const.MM_BLOCK);

  // Set sample frequency:
  libtiepie.api.ScpSetSampleFrequency(scp, 1e6); // 1 MHz

  // Set record length:
  const recordLength = libtiepie.api.ScpSetRecordLength(scp, 10000); // 10 kS

  // Set pre sample ratio:
  libtiepie.api.ScpSetPreSampleRatio(scp, 0); // 0 %

  // For all channels:
  for(let ch = 0; ch < channelCount; ch++)
  {
    // Enable channel to measure it:
    libtiepie.api.ScpChSetEnabled(scp, ch, true);

    // Set range:
    libtiepie.api.ScpChSetRange(scp, ch, 8); // 8 V

    // Set coupling:
    libtiepie.api.ScpChSetCoupling(scp, ch, libtiepie.const.CK_DCV); // DC Volt
  }

  // Set trigger timeout:
  libtiepie.api.ScpSetTriggerTimeOut(scp, 100e-3); // 100 ms

  // Disable all channel trigger sources:
  for(let ch = 0; ch < channelCount; ch++)
  {
    libtiepie.api.ScpChTrSetEnabled(scp, ch, false);
  }

  // Setup channel trigger:
  const triggerChannel = 0; // Ch 1

  // Enable trigger source:
  libtiepie.api.ScpChTrSetEnabled(scp, triggerChannel, true);

  // Kind:
  libtiepie.api.ScpChTrSetKind(scp, triggerChannel, libtiepie.const.TK_RISINGEDGE); // Rising edge

  // Level:
  libtiepie.api.ScpChTrSetLevel(scp, triggerChannel, 0, 0.5); // 50 %

  // Hysteresis:
  libtiepie.api.ScpChTrSetHysteresis(scp, triggerChannel, 0, 0.05); // 5 %

  // Start measurement:
  libtiepie.api.ScpStart(scp);

  // Wait for measurement to complete:
  while(!libtiepie.api.ScpIsDataReady(scp) && !libtiepie.api.ObjIsRemoved(scp))
  {
    sleep.msleep(10); // 10 ms delay, to save CPU time.
  }

  if(libtiepie.api.ObjIsRemoved(scp))
  {
    console.error('Device gone!');
    process.exitCode = 1;
  }
  else if(libtiepie.api.ScpIsDataReady(scp))
  {
    // Get the data from the scope:
    const channelData = libtiepie.api.ScpGetData(scp, channelCount, 0, recordLength);

    let fd = undefined;
    try
    {
      const filename = 'OscilloscopeBlock.csv';

      // Open file with write permissions:
      fd = fs.openSync(filename, 'w');

      // Write csv header:
      fs.writeSync(fd, 'Sample');
      for(let ch = 0; ch < channelCount; ch++)
      {
        fs.writeSync(fd, ';Ch' + ch.toString());
      }
      fs.writeSync(fd, EOL);

      // Write the data to csv:
      for(let i = 0; i < recordLength; i++)
      {
        fs.writeSync(fd, i.toString());
        for(let ch = 0; ch < channelCount; ch++)
        {
          fs.writeSync(fd, ';' + channelData[ch][i].toString());
        }
        fs.writeSync(fd, EOL);
      }

      console.log('Data written to: ' + filename);
    }
    catch(err)
    {
      console.error(err);
      process.exitCode = 1;
    }
    finally
    {
      // Close file:
      if(fd !== undefined)
        fs.closeSync(fd);
    }
  }

  // Close oscilloscope:
  libtiepie.api.ObjClose(scp);
}
else
{
  console.error('No oscilloscope available with block measurement support!');
  process.exitCode = 1;
}
