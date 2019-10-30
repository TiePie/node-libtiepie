/**
 * ListDevices.js
 *
 * This example prints all the available devices to the screen.
 *
 * Find more information on http://www.tiepie.com/LibTiePie .
 */

"use strict";

const libtiepie = require('libtiepie');

// Enable network search:
libtiepie.api.NetSetAutoDetectEnabled(true);

// Update device list:
libtiepie.api.LstUpdate();

// Get the number of connected devices:
var connectedDevices = libtiepie.api.LstGetCount();

if(connectedDevices != 0)
{
  console.log();
  console.log('Available devices:');

  for(let index = 0; index < connectedDevices; index++)
  {
    try
    {
      console.log('  Name: ' + libtiepie.api.LstDevGetName(libtiepie.const.IDKIND_INDEX, index));
      console.log('    Serial number  : ' + libtiepie.api.LstDevGetSerialNumber(libtiepie.const.IDKIND_INDEX, index));

      var deviceTypes = [];
      var value = libtiepie.api.LstDevGetTypes(libtiepie.const.IDKIND_INDEX, index);
      if(value & libtiepie.const.DEVICETYPE_OSCILLOSCOPE)
        deviceTypes.push('Oscilloscope');
      if(value & libtiepie.const.DEVICETYPE_GENERATOR)
        deviceTypes.push('Generator');
      if(value & libtiepie.const.DEVICETYPE_I2CHOST)
        deviceTypes.push('I2C Host');
      console.log('    Available types: ' + deviceTypes.join(', '));

      if(libtiepie.api.LstDevHasServer(libtiepie.const.IDKIND_INDEX, index))
      {
        var server = libtiepie.api.LstDevGetServer(libtiepie.const.IDKIND_INDEX, index);
        try
        {
          console.log('    Server         : ' + libtiepie.api.SrvGetURL(server) + ' (' + libtiepie.api.SrvGetName(server) + ')');
        }
        finally
        {
          libtiepie.api.ObjClose(server);
        }
      }
    }
    catch(err)
    {
      console.error(err);
      process.exitCode = 1;
    }
  }
}
else
  console.log('No devices found!');
