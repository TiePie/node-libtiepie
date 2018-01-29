var libtiepie = require(__dirname + '/../build/Release/node_libtiepie.node');

if(process.platform === 'win32')
{
  if(process.arch === 'x64')
  {
    libtiepie.loader.LibTiePieLoad(__dirname + '\\..\\deps\\libtiepie\\win\\x86-64\\libtiepie.dll');
  }
  else
  {
    libtiepie.loader.LibTiePieLoad(__dirname + '\\..\\deps\\libtiepie\\win\\x86\\libtiepie.dll');
  }
}

module.exports = libtiepie;
