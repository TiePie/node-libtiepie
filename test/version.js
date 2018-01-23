const test = require('tap').test
const libtiepie = require('../lib/index.js')

test('symbols', function(t)
{
  t.plan(1);
  t.type(libtiepie.api.LibGetVersion(), 'string');
})
