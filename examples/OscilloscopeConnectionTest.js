/**
 * OscilloscopeConnectionTest.c - for LibTiePie 0.7+
 *
 * This example performs a connection test.
 *
 * Find more information on http://www.tiepie.com/LibTiePie .
 */

"use strict";

const libtiepie = require('libtiepie');
const sleep = require('sleep');

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
    if(scp != libtiepie.const.TPDEVICEHANDLE_INVALID && libtiepie.api.ScpHasConnectionTest(scp))
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

  // Enable all channels that support connection testing:
  for(let ch = 0; ch < channelCount; ch++)
  {
    let b = libtiepie.api.ScpChHasConnectionTest(scp, ch);
    libtiepie.api.ScpChSetEnabled(scp, ch, b);
  }

  // Start connection test on current active channels:
  libtiepie.api.ScpStartConnectionTest(scp);

  // Wait for connection test to complete:
  while(!libtiepie.api.ScpIsConnectionTestCompleted(scp) && !libtiepie.api.ObjIsRemoved(scp))
  {
    sleep.msleep(10); // 10 ms delay, to save CPU time.
  }

  // Get data:
  const data = libtiepie.api.ScpGetConnectionTestData(scp, channelCount);

  // Print results:
  console.log('Connection test result:');
  for(let ch = 0; ch < channelCount; ch++)
  {
    console.log('Ch' + (ch + 1).toString() + ' = ' + data[ch].toString());
  }

  // Close oscilloscope:
  libtiepie.api.ObjClose(scp);
}
else
{
  console.error('No oscilloscope available with connection test support!');
  process.exitCode = 1;
}
