#include <nan.h>
#include <libtiepie.h>
#include <string>
#include <sstream>
#include <limits>

#define CHECK_PARAMETER_COUNT(expected) { const int length = info.Length(); if(length != expected) { std::stringstream ss; ss << "Invalid parameter count, expected " << expected << " got " << length << "."; return Nan::ThrowSyntaxError(ss.str().c_str()); } }
#define CHECK_RANGE(value, min, max) { if((value < min) || (value > max)) return Nan::ThrowRangeError("Value out of range"); }
#define CHECK_LAST_STATUS() { LibTiePieStatus_t status = LibGetLastStatus(); if(status < LIBTIEPIESTATUS_SUCCESS) return Nan::ThrowError(LibGetLastStatusStr()); }

std::string tpVersionToStr(TpVersion_t version)
{
  std::stringstream ss;
  ss << TPVERSION_MAJOR(version) << "." << TPVERSION_MINOR(version) << "." << TPVERSION_RELEASE(version) << "." << TPVERSION_BUILD(version);
  return ss.str();
}

void AtExit(void*)
{
  LibExit();
}

NAN_METHOD(LibGetVersionWrapper)
{
  CHECK_PARAMETER_COUNT(0);

  const TpVersion_t result = LibGetVersion();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(LibGetVersionExtraWrapper)
{
  CHECK_PARAMETER_COUNT(0);

  const char* result = LibGetVersionExtra();

  info.GetReturnValue().Set(Nan::New(result ? std::string(result) : std::string()).ToLocalChecked());
}

NAN_METHOD(LibGetConfigWrapper)
{
  CHECK_PARAMETER_COUNT(0);

  const uint32_t length = LibGetConfig(0, 0) + 1;
  std::vector<uint8_t> buffer;
  buffer.resize(length);
  LibGetConfig(&buffer[0], length);
  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for(uint64_t i = 0; i < length; ++i)
    result->Set(i, Nan::New<v8::Uint32>(buffer[i]));

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LibGetLastStatusWrapper)
{
  CHECK_PARAMETER_COUNT(0);

  const LibTiePieStatus_t result = LibGetLastStatus();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LibGetLastStatusStrWrapper)
{
  CHECK_PARAMETER_COUNT(0);

  const char* result = LibGetLastStatusStr();

  info.GetReturnValue().Set(Nan::New(result ? std::string(result) : std::string()).ToLocalChecked());
}

NAN_METHOD(LstUpdateWrapper)
{
  CHECK_PARAMETER_COUNT(0);

  LstUpdate();
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(LstGetCountWrapper)
{
  CHECK_PARAMETER_COUNT(0);

  const uint32_t result = LstGetCount();
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstOpenDeviceWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t deviceType = Nan::To<uint32_t>(info[2]).FromJust();

  const LibTiePieHandle_t result = LstOpenDevice(idKind, id, deviceType);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstOpenOscilloscopeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const LibTiePieHandle_t result = LstOpenOscilloscope(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstOpenGeneratorWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const LibTiePieHandle_t result = LstOpenGenerator(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstOpenI2CHostWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const LibTiePieHandle_t result = LstOpenI2CHost(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstRemoveDeviceWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const uint32_t serialNumber = Nan::To<uint32_t>(info[0]).FromJust();

  LstRemoveDevice(serialNumber);
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(LstDevCanOpenWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t deviceType = Nan::To<uint32_t>(info[2]).FromJust();

  const bool8_t result = LstDevCanOpen(idKind, id, deviceType);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(LstDevGetProductIdWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = LstDevGetProductId(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstDevGetVendorIdWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = LstDevGetVendorId(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstDevGetNameWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t length = LstDevGetName(idKind, id, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  LstDevGetName(idKind, id, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(LstDevGetNameShortWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t length = LstDevGetNameShort(idKind, id, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  LstDevGetNameShort(idKind, id, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(LstDevGetNameShortestWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t length = LstDevGetNameShortest(idKind, id, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  LstDevGetNameShortest(idKind, id, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(LstDevGetDriverVersionWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const TpVersion_t result = LstDevGetDriverVersion(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(LstDevGetRecommendedDriverVersionWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const TpVersion_t result = LstDevGetRecommendedDriverVersion(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(LstDevGetFirmwareVersionWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const TpVersion_t result = LstDevGetFirmwareVersion(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(LstDevGetRecommendedFirmwareVersionWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const TpVersion_t result = LstDevGetRecommendedFirmwareVersion(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(LstDevGetCalibrationDateWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const TpDate_t result = LstDevGetCalibrationDate(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstDevGetSerialNumberWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = LstDevGetSerialNumber(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstDevGetTypesWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = LstDevGetTypes(idKind, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstDevGetContainedSerialNumbersWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t length = LstDevGetContainedSerialNumbers(idKind, id, 0, 0) + 1;
  CHECK_LAST_STATUS();
  std::vector<uint32_t> buffer;
  buffer.resize(length);
  LstDevGetContainedSerialNumbers(idKind, id, &buffer[0], length);
  CHECK_LAST_STATUS();
  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for(uint64_t i = 0; i < length; ++i)
    result->Set(i, Nan::New<v8::Uint32>(buffer[i]));

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstCbDevGetProductIdWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const uint32_t result = LstCbDevGetProductId(idKind, id, containedDeviceSerialNumber);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstCbDevGetVendorIdWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const uint32_t result = LstCbDevGetVendorId(idKind, id, containedDeviceSerialNumber);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstCbDevGetNameWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const uint32_t length = LstCbDevGetName(idKind, id, containedDeviceSerialNumber, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  LstCbDevGetName(idKind, id, containedDeviceSerialNumber, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(LstCbDevGetNameShortWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const uint32_t length = LstCbDevGetNameShort(idKind, id, containedDeviceSerialNumber, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  LstCbDevGetNameShort(idKind, id, containedDeviceSerialNumber, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(LstCbDevGetNameShortestWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const uint32_t length = LstCbDevGetNameShortest(idKind, id, containedDeviceSerialNumber, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  LstCbDevGetNameShortest(idKind, id, containedDeviceSerialNumber, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(LstCbDevGetDriverVersionWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const TpVersion_t result = LstCbDevGetDriverVersion(idKind, id, containedDeviceSerialNumber);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(LstCbDevGetFirmwareVersionWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const TpVersion_t result = LstCbDevGetFirmwareVersion(idKind, id, containedDeviceSerialNumber);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(LstCbDevGetCalibrationDateWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const TpDate_t result = LstCbDevGetCalibrationDate(idKind, id, containedDeviceSerialNumber);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(LstCbScpGetChannelCountWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const uint32_t idKind = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();
  const uint32_t containedDeviceSerialNumber = Nan::To<uint32_t>(info[2]).FromJust();

  const uint16_t result = LstCbScpGetChannelCount(idKind, id, containedDeviceSerialNumber);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ObjCloseWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t handle = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  ObjClose(handle);
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(ObjIsRemovedWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t handle = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ObjIsRemoved(handle);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ObjGetInterfacesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t handle = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = ObjGetInterfaces(handle);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(DevGetDriverVersionWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const TpVersion_t result = DevGetDriverVersion(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(DevGetFirmwareVersionWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const TpVersion_t result = DevGetFirmwareVersion(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(tpVersionToStr(result)).ToLocalChecked());
}

NAN_METHOD(DevGetCalibrationDateWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const TpDate_t result = DevGetCalibrationDate(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(DevGetCalibrationTokenWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t length = DevGetCalibrationToken(device, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  DevGetCalibrationToken(device, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(DevGetSerialNumberWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = DevGetSerialNumber(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(DevGetProductIdWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = DevGetProductId(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(DevGetVendorIdWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = DevGetVendorId(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(DevGetTypeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = DevGetType(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(DevGetNameWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t length = DevGetName(device, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  DevGetName(device, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(DevGetNameShortWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t length = DevGetNameShort(device, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  DevGetNameShort(device, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(DevGetNameShortestWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t length = DevGetNameShortest(device, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  DevGetNameShortest(device, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(DevTrGetInputCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint16_t result = DevTrGetInputCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(DevTrGetInputIndexByIdWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint16_t result = DevTrGetInputIndexById(device, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpTrInIsTriggeredWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpTrInIsTriggered(device, input);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(DevTrInGetEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = DevTrInGetEnabled(device, input);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(DevTrInSetEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const bool enable = Nan::To<bool>(info[2]).FromJust();

  const bool8_t result = DevTrInSetEnabled(device, input, enable ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(DevTrInGetKindsWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint64_t result = DevTrInGetKinds(device, input);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(DevTrInGetKindWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint64_t result = DevTrInGetKind(device, input);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(DevTrInSetKindWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t kind = Nan::To<uint32_t>(info[2]).FromJust();

  const uint64_t result = DevTrInSetKind(device, input, kind);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(DevTrInIsAvailableWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = DevTrInIsAvailable(device, input);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(DevTrInGetIdWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = DevTrInGetId(device, input);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(DevTrInGetNameWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t input = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(input, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t length = DevTrInGetName(device, input, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  DevTrInGetName(device, input, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(DevTrGetOutputCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint16_t result = DevTrGetOutputCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(DevTrGetOutputIndexByIdWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t id = Nan::To<uint32_t>(info[1]).FromJust();

  const uint16_t result = DevTrGetOutputIndexById(device, id);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(DevTrOutGetEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t output = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(output, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = DevTrOutGetEnabled(device, output);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(DevTrOutSetEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t output = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(output, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const bool enable = Nan::To<bool>(info[2]).FromJust();

  const bool8_t result = DevTrOutSetEnabled(device, output, enable ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(DevTrOutGetIdWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t output = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(output, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = DevTrOutGetId(device, output);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(DevTrOutGetNameWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t output = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(output, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t length = DevTrOutGetName(device, output, 0, 0);
  CHECK_LAST_STATUS();
  std::vector<char> s;
  s.resize(length);
  DevTrOutGetName(device, output, &s[0], length);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(Nan::New(&s[0]).ToLocalChecked());
}

NAN_METHOD(DevTrOutTriggerWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t output = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(output, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = DevTrOutTrigger(device, output);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpGetChannelCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint16_t result = ScpGetChannelCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpChIsAvailableWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChIsAvailable(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChGetConnectorTypeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = ScpChGetConnectorType(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChIsDifferentialWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChIsDifferential(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChGetImpedanceWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetImpedance(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetBandwidthsWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t length = ScpChGetBandwidths(device, ch, 0, 0) + 1;
  CHECK_LAST_STATUS();
  std::vector<double> buffer;
  buffer.resize(length);
  ScpChGetBandwidths(device, ch, &buffer[0], length);
  CHECK_LAST_STATUS();
  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for(uint64_t i = 0; i < length; ++i)
    result->Set(i, Nan::New<v8::Number>(buffer[i]));

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetBandwidthWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetBandwidth(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChSetBandwidthWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const double bandwidth = Nan::To<double>(info[2]).FromJust();

  const double result = ScpChSetBandwidth(device, ch, bandwidth);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetCouplingsWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint64_t result = ScpChGetCouplings(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpChGetCouplingWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint64_t result = ScpChGetCoupling(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpChSetCouplingWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t coupling = Nan::To<uint32_t>(info[2]).FromJust();

  const uint64_t result = ScpChSetCoupling(device, ch, coupling);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpChGetEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChGetEnabled(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChSetEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const bool enable = Nan::To<bool>(info[2]).FromJust();

  const bool8_t result = ScpChSetEnabled(device, ch, enable ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChGetProbeGainWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetProbeGain(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChSetProbeGainWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const double probeGain = Nan::To<double>(info[2]).FromJust();

  const double result = ScpChSetProbeGain(device, ch, probeGain);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetProbeOffsetWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetProbeOffset(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChSetProbeOffsetWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const double probeOffset = Nan::To<double>(info[2]).FromJust();

  const double result = ScpChSetProbeOffset(device, ch, probeOffset);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetAutoRangingWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChGetAutoRanging(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChSetAutoRangingWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const bool enable = Nan::To<bool>(info[2]).FromJust();

  const bool8_t result = ScpChSetAutoRanging(device, ch, enable ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChGetRangesWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t length = ScpChGetRanges(device, ch, 0, 0) + 1;
  CHECK_LAST_STATUS();
  std::vector<double> buffer;
  buffer.resize(length);
  ScpChGetRanges(device, ch, &buffer[0], length);
  CHECK_LAST_STATUS();
  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for(uint64_t i = 0; i < length; ++i)
    result->Set(i, Nan::New<v8::Number>(buffer[i]));

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetRangeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetRange(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChSetRangeWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const double range = Nan::To<double>(info[2]).FromJust();

  const double result = ScpChSetRange(device, ch, range);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChHasSafeGroundWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChHasSafeGround(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChGetSafeGroundEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChGetSafeGroundEnabled(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChSetSafeGroundEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const bool enable = Nan::To<bool>(info[2]).FromJust();

  const bool8_t result = ScpChSetSafeGroundEnabled(device, ch, enable ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChGetSafeGroundThresholdMinWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetSafeGroundThresholdMin(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetSafeGroundThresholdMaxWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetSafeGroundThresholdMax(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetSafeGroundThresholdWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetSafeGroundThreshold(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChSetSafeGroundThresholdWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const double threshold = Nan::To<double>(info[2]).FromJust();

  const double result = ScpChSetSafeGroundThreshold(device, ch, threshold);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChVerifySafeGroundThresholdWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const double threshold = Nan::To<double>(info[2]).FromJust();

  const double result = ScpChVerifySafeGroundThreshold(device, ch, threshold);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChHasTriggerWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChHasTrigger(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChTrIsAvailableWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChTrIsAvailable(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChTrIsTriggeredWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChTrIsTriggered(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChTrGetEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChTrGetEnabled(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChTrSetEnabledWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const bool enable = Nan::To<bool>(info[2]).FromJust();

  const bool8_t result = ScpChTrSetEnabled(device, ch, enable ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChTrGetKindsWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint64_t result = ScpChTrGetKinds(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpChTrGetKindWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint64_t result = ScpChTrGetKind(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpChTrSetKindWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t triggerKind = Nan::To<uint32_t>(info[2]).FromJust();

  const uint64_t result = ScpChTrSetKind(device, ch, triggerKind);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpChTrGetLevelModesWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = ScpChTrGetLevelModes(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetLevelModeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = ScpChTrGetLevelMode(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrSetLevelModeWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t levelMode = Nan::To<uint32_t>(info[2]).FromJust();

  const uint32_t result = ScpChTrSetLevelMode(device, ch, levelMode);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetLevelCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = ScpChTrGetLevelCount(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetLevelWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t index = Nan::To<uint32_t>(info[2]).FromJust();

  const double result = ScpChTrGetLevel(device, ch, index);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrSetLevelWrapper)
{
  CHECK_PARAMETER_COUNT(4);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t index = Nan::To<uint32_t>(info[2]).FromJust();
  const double level = Nan::To<double>(info[3]).FromJust();

  const double result = ScpChTrSetLevel(device, ch, index, level);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetHysteresisCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = ScpChTrGetHysteresisCount(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetHysteresisWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t index = Nan::To<uint32_t>(info[2]).FromJust();

  const double result = ScpChTrGetHysteresis(device, ch, index);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrSetHysteresisWrapper)
{
  CHECK_PARAMETER_COUNT(4);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t index = Nan::To<uint32_t>(info[2]).FromJust();
  const double hysteresis = Nan::To<double>(info[3]).FromJust();

  const double result = ScpChTrSetHysteresis(device, ch, index, hysteresis);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetConditionsWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = ScpChTrGetConditions(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetConditionWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = ScpChTrGetCondition(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrSetConditionWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t condition = Nan::To<uint32_t>(info[2]).FromJust();

  const uint32_t result = ScpChTrSetCondition(device, ch, condition);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetTimeCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const uint32_t result = ScpChTrGetTimeCount(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrGetTimeWrapper)
{
  CHECK_PARAMETER_COUNT(3);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t index = Nan::To<uint32_t>(info[2]).FromJust();

  const double result = ScpChTrGetTime(device, ch, index);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrSetTimeWrapper)
{
  CHECK_PARAMETER_COUNT(4);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t index = Nan::To<uint32_t>(info[2]).FromJust();
  const double time = Nan::To<double>(info[3]).FromJust();

  const double result = ScpChTrSetTime(device, ch, index, time);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChTrVerifyTimeWrapper)
{
  CHECK_PARAMETER_COUNT(4);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint32_t index = Nan::To<uint32_t>(info[2]).FromJust();
  const double time = Nan::To<double>(info[3]).FromJust();

  const double result = ScpChTrVerifyTime(device, ch, index, time);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetDataWrapper)
{
  CHECK_PARAMETER_COUNT(4);
  const LibTiePieHandle_t device = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t channelCount = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(channelCount, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
  const uint64_t startIndex = Nan::To<uint32_t>(info[2]).FromJust();
  uint64_t sampleCount = Nan::To<uint32_t>(info[3]).FromJust();

  std::vector<std::vector<float>> buffers;
  std::vector<float*> bufferPointers;
  buffers.resize(channelCount);
  bufferPointers.resize(channelCount);
  for(uint_fast16_t i = 0; i < channelCount; ++i)
  {
    buffers[i].resize(sampleCount);
    bufferPointers[i] = &buffers[i][0];
  }

  sampleCount = ScpGetData(device, &bufferPointers[0], channelCount, startIndex, sampleCount);

  v8::Local<v8::Array> result = Nan::New<v8::Array>(channelCount);
  for(uint_fast16_t i = 0; i < channelCount; ++i)
  {
    if(bufferPointers[i] != 0)
    {
      v8::Local<v8::Array> tmp = Nan::New<v8::Array>();
      for(uint_fast64_t j = 0; j < sampleCount; ++j)
        tmp->Set(j, Nan::New<v8::Number>(buffers[i][j]));
      result->Set(i, tmp);
    }
    else
      result->Set(i, Nan::Undefined());
  }

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetValidPreSampleCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = ScpGetValidPreSampleCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpChGetDataValueMinWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetDataValueMin(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChGetDataValueMaxWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const double result = ScpChGetDataValueMax(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpChIsRangeMaxReachableWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChIsRangeMaxReachable(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpStartWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  ScpStart(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(ScpStopWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  ScpStop(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(ScpForceTriggerWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  ScpForceTrigger(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(ScpGetMeasureModesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetMeasureModes(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetMeasureModeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetMeasureMode(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetMeasureModeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t measureMode = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = ScpSetMeasureMode(device, measureMode);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpIsRunningWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpIsRunning(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpIsTriggeredWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpIsTriggered(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpIsTimeOutTriggeredWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpIsTimeOutTriggered(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpIsForceTriggeredWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpIsForceTriggered(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpIsDataReadyWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpIsDataReady(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpIsDataOverflowWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpIsDataOverflow(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpGetAutoResolutionModesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetAutoResolutionModes(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetAutoResolutionModeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetAutoResolutionMode(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetAutoResolutionModeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t autoResolutionMode = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = ScpSetAutoResolutionMode(device, autoResolutionMode);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetResolutionsWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t length = ScpGetResolutions(device, 0, 0) + 1;
  CHECK_LAST_STATUS();
  std::vector<uint8_t> buffer;
  buffer.resize(length);
  ScpGetResolutions(device, &buffer[0], length);
  CHECK_LAST_STATUS();
  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for(uint64_t i = 0; i < length; ++i)
    result->Set(i, Nan::New<v8::Uint32>(buffer[i]));

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetResolutionWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint8_t result = ScpGetResolution(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpSetResolutionWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t resolution = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(resolution, std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max());

  const uint8_t result = ScpSetResolution(device, resolution);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpIsResolutionEnhancedWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpIsResolutionEnhanced(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpGetClockSourcesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetClockSources(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetClockSourceWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetClockSource(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetClockSourceWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t clockSource = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = ScpSetClockSource(device, clockSource);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetClockSourceFrequenciesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t length = ScpGetClockSourceFrequencies(device, 0, 0) + 1;
  CHECK_LAST_STATUS();
  std::vector<double> buffer;
  buffer.resize(length);
  ScpGetClockSourceFrequencies(device, &buffer[0], length);
  CHECK_LAST_STATUS();
  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for(uint64_t i = 0; i < length; ++i)
    result->Set(i, Nan::New<v8::Number>(buffer[i]));

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetClockSourceFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = ScpGetClockSourceFrequency(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetClockSourceFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double clockSourceFrequency = Nan::To<double>(info[1]).FromJust();

  const double result = ScpSetClockSourceFrequency(device, clockSourceFrequency);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetClockOutputsWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetClockOutputs(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetClockOutputWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetClockOutput(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetClockOutputWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t clockOutput = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = ScpSetClockOutput(device, clockOutput);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetClockOutputFrequenciesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t length = ScpGetClockOutputFrequencies(device, 0, 0) + 1;
  CHECK_LAST_STATUS();
  std::vector<double> buffer;
  buffer.resize(length);
  ScpGetClockOutputFrequencies(device, &buffer[0], length);
  CHECK_LAST_STATUS();
  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for(uint64_t i = 0; i < length; ++i)
    result->Set(i, Nan::New<v8::Number>(buffer[i]));

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetClockOutputFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = ScpGetClockOutputFrequency(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetClockOutputFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double clockOutputFrequency = Nan::To<double>(info[1]).FromJust();

  const double result = ScpSetClockOutputFrequency(device, clockOutputFrequency);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetSampleFrequencyMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = ScpGetSampleFrequencyMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetSampleFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = ScpGetSampleFrequency(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetSampleFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double sampleFrequency = Nan::To<double>(info[1]).FromJust();

  const double result = ScpSetSampleFrequency(device, sampleFrequency);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpVerifySampleFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double sampleFrequency = Nan::To<double>(info[1]).FromJust();

  const double result = ScpVerifySampleFrequency(device, sampleFrequency);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetRecordLengthMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = ScpGetRecordLengthMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpGetRecordLengthWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = ScpGetRecordLength(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpSetRecordLengthWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t recordLength = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = ScpSetRecordLength(device, recordLength);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpVerifyRecordLengthWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t recordLength = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = ScpVerifyRecordLength(device, recordLength);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpGetPreSampleRatioWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = ScpGetPreSampleRatio(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetPreSampleRatioWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double preSampleRatio = Nan::To<double>(info[1]).FromJust();

  const double result = ScpSetPreSampleRatio(device, preSampleRatio);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetSegmentCountMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetSegmentCountMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetSegmentCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = ScpGetSegmentCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetSegmentCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t segmentCount = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = ScpSetSegmentCount(device, segmentCount);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpVerifySegmentCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t segmentCount = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = ScpVerifySegmentCount(device, segmentCount);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpHasTriggerWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpHasTrigger(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpGetTriggerTimeOutWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = ScpGetTriggerTimeOut(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetTriggerTimeOutWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double timeOut = Nan::To<double>(info[1]).FromJust();

  const double result = ScpSetTriggerTimeOut(device, timeOut);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpVerifyTriggerTimeOutWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double timeOut = Nan::To<double>(info[1]).FromJust();

  const double result = ScpVerifyTriggerTimeOut(device, timeOut);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpHasTriggerDelayWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpHasTriggerDelay(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpGetTriggerDelayMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = ScpGetTriggerDelayMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpGetTriggerDelayWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = ScpGetTriggerDelay(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpSetTriggerDelayWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double delay = Nan::To<double>(info[1]).FromJust();

  const double result = ScpSetTriggerDelay(device, delay);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpVerifyTriggerDelayWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double delay = Nan::To<double>(info[1]).FromJust();

  const double result = ScpVerifyTriggerDelay(device, delay);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(ScpHasTriggerHoldOffWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpHasTriggerHoldOff(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpGetTriggerHoldOffCountMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = ScpGetTriggerHoldOffCountMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpGetTriggerHoldOffCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = ScpGetTriggerHoldOffCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpSetTriggerHoldOffCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t triggerHoldOffCount = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = ScpSetTriggerHoldOffCount(device, triggerHoldOffCount);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(ScpHasConnectionTestWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpHasConnectionTest(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpChHasConnectionTestWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t ch = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(ch, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  const bool8_t result = ScpChHasConnectionTest(device, ch);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpStartConnectionTestWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  ScpStartConnectionTest(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(ScpIsConnectionTestCompletedWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = ScpIsConnectionTestCompleted(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(ScpGetConnectionTestDataWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<uint32_t>(info[0]).FromJust();
  const uint32_t channelCount = Nan::To<uint32_t>(info[1]).FromJust();
  CHECK_RANGE(channelCount, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());

  std::vector<LibTiePieTriState_t> buffer;
  buffer.resize(channelCount);

  const uint16_t elementsWritten = ScpGetConnectionTestData(device, &buffer[0], channelCount);

  v8::Local<v8::Array> result = Nan::New<v8::Array>(channelCount);
  for(uint_fast16_t i = 0; i < channelCount; ++i)
  {
    if(i < elementsWritten || buffer[i] == LIBTIEPIE_TRISTATE_UNDEFINED)
      result->Set(i, buffer[i] == LIBTIEPIE_TRISTATE_TRUE ? Nan::True() : Nan::False());
    else
      result->Set(i, Nan::Undefined());
  }

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetConnectorTypeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = GenGetConnectorType(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenIsDifferentialWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenIsDifferential(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetImpedanceWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetImpedance(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetResolutionWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint8_t result = GenGetResolution(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetOutputValueMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetOutputValueMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetOutputValueMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetOutputValueMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenIsControllableWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenIsControllable(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenIsRunningWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenIsRunning(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetStatusWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = GenGetStatus(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetOutputOnWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenGetOutputOn(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenSetOutputOnWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const bool outputOn = Nan::To<bool>(info[1]).FromJust();

  const bool8_t result = GenSetOutputOn(device, outputOn ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenHasOutputInvertWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasOutputInvert(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetOutputInvertWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenGetOutputInvert(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenSetOutputInvertWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const bool invert = Nan::To<bool>(info[1]).FromJust();

  const bool8_t result = GenSetOutputInvert(device, invert ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenStartWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  GenStart(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(GenStopWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  GenStop(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(GenGetSignalTypesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = GenGetSignalTypes(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetSignalTypeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = GenGetSignalType(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetSignalTypeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t signalType = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = GenSetSignalType(device, signalType);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenHasAmplitudeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasAmplitude(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetAmplitudeMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetAmplitudeMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetAmplitudeMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetAmplitudeMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetAmplitudeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetAmplitude(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetAmplitudeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double amplitude = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetAmplitude(device, amplitude);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenVerifyAmplitudeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double amplitude = Nan::To<double>(info[1]).FromJust();

  const double result = GenVerifyAmplitude(device, amplitude);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetAmplitudeRangesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t length = GenGetAmplitudeRanges(device, 0, 0) + 1;
  CHECK_LAST_STATUS();
  std::vector<double> buffer;
  buffer.resize(length);
  GenGetAmplitudeRanges(device, &buffer[0], length);
  CHECK_LAST_STATUS();
  v8::Local<v8::Array> result = Nan::New<v8::Array>();
  for(uint64_t i = 0; i < length; ++i)
    result->Set(i, Nan::New<v8::Number>(buffer[i]));

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetAmplitudeRangeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetAmplitudeRange(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetAmplitudeRangeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double range = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetAmplitudeRange(device, range);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetAmplitudeAutoRangingWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenGetAmplitudeAutoRanging(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenSetAmplitudeAutoRangingWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const bool enable = Nan::To<bool>(info[1]).FromJust();

  const bool8_t result = GenSetAmplitudeAutoRanging(device, enable ? BOOL8_TRUE : BOOL8_FALSE);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenHasOffsetWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasOffset(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetOffsetMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetOffsetMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetOffsetMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetOffsetMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetOffsetWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetOffset(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetOffsetWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double offset = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetOffset(device, offset);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenVerifyOffsetWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double offset = Nan::To<double>(info[1]).FromJust();

  const double result = GenVerifyOffset(device, offset);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetFrequencyModesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = GenGetFrequencyModes(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetFrequencyModeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint32_t result = GenGetFrequencyMode(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetFrequencyModeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t frequencyMode = Nan::To<uint32_t>(info[1]).FromJust();

  const uint32_t result = GenSetFrequencyMode(device, frequencyMode);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenHasFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasFrequency(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetFrequencyMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetFrequencyMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetFrequencyMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetFrequencyMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetFrequency(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double frequency = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetFrequency(device, frequency);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenVerifyFrequencyWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double frequency = Nan::To<double>(info[1]).FromJust();

  const double result = GenVerifyFrequency(device, frequency);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenHasPhaseWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasPhase(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetPhaseMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetPhaseMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetPhaseMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetPhaseMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetPhaseWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetPhase(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetPhaseWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double phase = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetPhase(device, phase);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenVerifyPhaseWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double phase = Nan::To<double>(info[1]).FromJust();

  const double result = GenVerifyPhase(device, phase);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenHasSymmetryWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasSymmetry(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetSymmetryMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetSymmetryMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetSymmetryMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetSymmetryMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetSymmetryWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetSymmetry(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetSymmetryWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double symmetry = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetSymmetry(device, symmetry);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenVerifySymmetryWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double symmetry = Nan::To<double>(info[1]).FromJust();

  const double result = GenVerifySymmetry(device, symmetry);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenHasWidthWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasWidth(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetWidthMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetWidthMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetWidthMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetWidthMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetWidthWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetWidth(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetWidthWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double width = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetWidth(device, width);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenVerifyWidthWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double width = Nan::To<double>(info[1]).FromJust();

  const double result = GenVerifyWidth(device, width);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenHasEdgeTimeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasEdgeTime(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetLeadingEdgeTimeMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetLeadingEdgeTimeMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetLeadingEdgeTimeMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetLeadingEdgeTimeMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetLeadingEdgeTimeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetLeadingEdgeTime(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetLeadingEdgeTimeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double leadingEdgeTime = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetLeadingEdgeTime(device, leadingEdgeTime);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenVerifyLeadingEdgeTimeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double leadingEdgeTime = Nan::To<double>(info[1]).FromJust();

  const double result = GenVerifyLeadingEdgeTime(device, leadingEdgeTime);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetTrailingEdgeTimeMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetTrailingEdgeTimeMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetTrailingEdgeTimeMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetTrailingEdgeTimeMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenGetTrailingEdgeTimeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const double result = GenGetTrailingEdgeTime(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenSetTrailingEdgeTimeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double trailingEdgeTime = Nan::To<double>(info[1]).FromJust();

  const double result = GenSetTrailingEdgeTime(device, trailingEdgeTime);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenVerifyTrailingEdgeTimeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const double trailingEdgeTime = Nan::To<double>(info[1]).FromJust();

  const double result = GenVerifyTrailingEdgeTime(device, trailingEdgeTime);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result);
}

NAN_METHOD(GenHasDataWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenHasData(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetDataLengthMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetDataLengthMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetDataLengthMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetDataLengthMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetDataLengthWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetDataLength(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenVerifyDataLengthWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t dataLength = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = GenVerifyDataLength(device, dataLength);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetModesWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetModes(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetModesNativeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetModesNative(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetModeWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetMode(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenSetModeWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t generatorMode = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = GenSetMode(device, generatorMode);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenIsBurstActiveWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const bool8_t result = GenIsBurstActive(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set(result != BOOL8_FALSE);
}

NAN_METHOD(GenGetBurstCountMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstCountMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetBurstCountMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstCountMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetBurstCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenSetBurstCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t burstCount = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = GenSetBurstCount(device, burstCount);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetBurstSampleCountMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstSampleCountMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetBurstSampleCountMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstSampleCountMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetBurstSampleCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstSampleCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenSetBurstSampleCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t burstSampleCount = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = GenSetBurstSampleCount(device, burstSampleCount);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetBurstSegmentCountMinWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstSegmentCountMin(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetBurstSegmentCountMaxWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstSegmentCountMax(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenGetBurstSegmentCountWrapper)
{
  CHECK_PARAMETER_COUNT(1);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();

  const uint64_t result = GenGetBurstSegmentCount(device);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenSetBurstSegmentCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t burstSegmentCount = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = GenSetBurstSegmentCount(device, burstSegmentCount);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_METHOD(GenVerifyBurstSegmentCountWrapper)
{
  CHECK_PARAMETER_COUNT(2);
  const LibTiePieHandle_t device = Nan::To<LibTiePieHandle_t>(info[0]).FromJust();
  const uint32_t burstSegmentCount = Nan::To<uint32_t>(info[1]).FromJust();

  const uint64_t result = GenVerifyBurstSegmentCount(device, burstSegmentCount);
  CHECK_LAST_STATUS();

  info.GetReturnValue().Set((uint32_t)result);
}

NAN_MODULE_INIT(init)
{
  v8::Local<v8::Array> api = Nan::New<v8::Array>();
  Nan::Set(api, Nan::New<v8::String>("LibGetVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LibGetVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LibGetVersionExtra").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LibGetVersionExtraWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LibGetConfig").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LibGetConfigWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LibGetLastStatus").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LibGetLastStatusWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LibGetLastStatusStr").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LibGetLastStatusStrWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstUpdate").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstUpdateWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstGetCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstGetCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstOpenDevice").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstOpenDeviceWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstOpenOscilloscope").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstOpenOscilloscopeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstOpenGenerator").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstOpenGeneratorWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstOpenI2CHost").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstOpenI2CHostWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstRemoveDevice").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstRemoveDeviceWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevCanOpen").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevCanOpenWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetProductId").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetProductIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetVendorId").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetVendorIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetName").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetNameWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetNameShort").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetNameShortWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetNameShortest").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetNameShortestWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetDriverVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetDriverVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetRecommendedDriverVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetRecommendedDriverVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetFirmwareVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetFirmwareVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetRecommendedFirmwareVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetRecommendedFirmwareVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetCalibrationDate").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetCalibrationDateWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetSerialNumber").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetSerialNumberWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetTypes").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetTypesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstDevGetContainedSerialNumbers").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstDevGetContainedSerialNumbersWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbDevGetProductId").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbDevGetProductIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbDevGetVendorId").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbDevGetVendorIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbDevGetName").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbDevGetNameWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbDevGetNameShort").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbDevGetNameShortWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbDevGetNameShortest").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbDevGetNameShortestWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbDevGetDriverVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbDevGetDriverVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbDevGetFirmwareVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbDevGetFirmwareVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbDevGetCalibrationDate").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbDevGetCalibrationDateWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("LstCbScpGetChannelCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(LstCbScpGetChannelCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ObjClose").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ObjCloseWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ObjIsRemoved").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ObjIsRemovedWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ObjGetInterfaces").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ObjGetInterfacesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetDriverVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetDriverVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetFirmwareVersion").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetFirmwareVersionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetCalibrationDate").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetCalibrationDateWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetCalibrationToken").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetCalibrationTokenWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetSerialNumber").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetSerialNumberWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetProductId").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetProductIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetVendorId").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetVendorIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetType").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetTypeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetName").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetNameWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetNameShort").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetNameShortWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevGetNameShortest").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevGetNameShortestWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrGetInputCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrGetInputCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrGetInputIndexById").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrGetInputIndexByIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpTrInIsTriggered").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpTrInIsTriggeredWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrInGetEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrInGetEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrInSetEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrInSetEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrInGetKinds").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrInGetKindsWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrInGetKind").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrInGetKindWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrInSetKind").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrInSetKindWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrInIsAvailable").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrInIsAvailableWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrInGetId").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrInGetIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrInGetName").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrInGetNameWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrGetOutputCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrGetOutputCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrGetOutputIndexById").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrGetOutputIndexByIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrOutGetEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrOutGetEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrOutSetEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrOutSetEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrOutGetId").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrOutGetIdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrOutGetName").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrOutGetNameWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("DevTrOutTrigger").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(DevTrOutTriggerWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetChannelCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetChannelCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChIsAvailable").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChIsAvailableWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetConnectorType").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetConnectorTypeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChIsDifferential").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChIsDifferentialWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetImpedance").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetImpedanceWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetBandwidths").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetBandwidthsWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetBandwidth").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetBandwidthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetBandwidth").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetBandwidthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetCouplings").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetCouplingsWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetCoupling").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetCouplingWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetCoupling").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetCouplingWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetProbeGain").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetProbeGainWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetProbeGain").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetProbeGainWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetProbeOffset").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetProbeOffsetWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetProbeOffset").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetProbeOffsetWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetAutoRanging").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetAutoRangingWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetAutoRanging").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetAutoRangingWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetRanges").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetRangesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetRange").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetRangeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetRange").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetRangeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChHasSafeGround").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChHasSafeGroundWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetSafeGroundEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetSafeGroundEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetSafeGroundEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetSafeGroundEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetSafeGroundThresholdMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetSafeGroundThresholdMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetSafeGroundThresholdMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetSafeGroundThresholdMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetSafeGroundThreshold").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetSafeGroundThresholdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChSetSafeGroundThreshold").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChSetSafeGroundThresholdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChVerifySafeGroundThreshold").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChVerifySafeGroundThresholdWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChHasTrigger").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChHasTriggerWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrIsAvailable").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrIsAvailableWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrIsTriggered").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrIsTriggeredWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrSetEnabled").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrSetEnabledWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetKinds").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetKindsWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetKind").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetKindWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrSetKind").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrSetKindWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetLevelModes").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetLevelModesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetLevelMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetLevelModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrSetLevelMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrSetLevelModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetLevelCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetLevelCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetLevel").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetLevelWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrSetLevel").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrSetLevelWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetHysteresisCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetHysteresisCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetHysteresis").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetHysteresisWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrSetHysteresis").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrSetHysteresisWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetConditions").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetConditionsWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetCondition").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetConditionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrSetCondition").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrSetConditionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetTimeCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetTimeCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrGetTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrGetTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrSetTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrSetTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChTrVerifyTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChTrVerifyTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetData").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetDataWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetValidPreSampleCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetValidPreSampleCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetDataValueMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetDataValueMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChGetDataValueMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChGetDataValueMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChIsRangeMaxReachable").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChIsRangeMaxReachableWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpStart").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpStartWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpStop").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpStopWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpForceTrigger").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpForceTriggerWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetMeasureModes").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetMeasureModesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetMeasureMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetMeasureModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetMeasureMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetMeasureModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpIsRunning").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpIsRunningWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpIsTriggered").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpIsTriggeredWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpIsTimeOutTriggered").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpIsTimeOutTriggeredWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpIsForceTriggered").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpIsForceTriggeredWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpIsDataReady").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpIsDataReadyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpIsDataOverflow").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpIsDataOverflowWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetAutoResolutionModes").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetAutoResolutionModesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetAutoResolutionMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetAutoResolutionModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetAutoResolutionMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetAutoResolutionModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetResolutions").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetResolutionsWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetResolution").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetResolutionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetResolution").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetResolutionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpIsResolutionEnhanced").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpIsResolutionEnhancedWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetClockSources").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetClockSourcesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetClockSource").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetClockSourceWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetClockSource").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetClockSourceWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetClockSourceFrequencies").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetClockSourceFrequenciesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetClockSourceFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetClockSourceFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetClockSourceFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetClockSourceFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetClockOutputs").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetClockOutputsWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetClockOutput").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetClockOutputWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetClockOutput").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetClockOutputWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetClockOutputFrequencies").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetClockOutputFrequenciesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetClockOutputFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetClockOutputFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetClockOutputFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetClockOutputFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetSampleFrequencyMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetSampleFrequencyMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetSampleFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetSampleFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetSampleFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetSampleFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpVerifySampleFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpVerifySampleFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetRecordLengthMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetRecordLengthMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetRecordLength").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetRecordLengthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetRecordLength").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetRecordLengthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpVerifyRecordLength").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpVerifyRecordLengthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetPreSampleRatio").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetPreSampleRatioWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetPreSampleRatio").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetPreSampleRatioWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetSegmentCountMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetSegmentCountMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetSegmentCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetSegmentCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetSegmentCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetSegmentCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpVerifySegmentCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpVerifySegmentCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpHasTrigger").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpHasTriggerWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetTriggerTimeOut").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetTriggerTimeOutWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetTriggerTimeOut").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetTriggerTimeOutWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpVerifyTriggerTimeOut").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpVerifyTriggerTimeOutWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpHasTriggerDelay").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpHasTriggerDelayWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetTriggerDelayMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetTriggerDelayMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetTriggerDelay").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetTriggerDelayWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetTriggerDelay").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetTriggerDelayWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpVerifyTriggerDelay").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpVerifyTriggerDelayWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpHasTriggerHoldOff").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpHasTriggerHoldOffWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetTriggerHoldOffCountMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetTriggerHoldOffCountMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetTriggerHoldOffCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetTriggerHoldOffCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpSetTriggerHoldOffCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpSetTriggerHoldOffCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpHasConnectionTest").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpHasConnectionTestWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpChHasConnectionTest").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpChHasConnectionTestWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpStartConnectionTest").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpStartConnectionTestWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpIsConnectionTestCompleted").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpIsConnectionTestCompletedWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("ScpGetConnectionTestData").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(ScpGetConnectionTestDataWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetConnectorType").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetConnectorTypeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenIsDifferential").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenIsDifferentialWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetImpedance").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetImpedanceWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetResolution").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetResolutionWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetOutputValueMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetOutputValueMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetOutputValueMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetOutputValueMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenIsControllable").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenIsControllableWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenIsRunning").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenIsRunningWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetStatus").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetStatusWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetOutputOn").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetOutputOnWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetOutputOn").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetOutputOnWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasOutputInvert").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasOutputInvertWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetOutputInvert").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetOutputInvertWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetOutputInvert").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetOutputInvertWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenStart").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenStartWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenStop").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenStopWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetSignalTypes").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetSignalTypesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetSignalType").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetSignalTypeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetSignalType").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetSignalTypeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasAmplitude").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasAmplitudeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetAmplitudeMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetAmplitudeMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetAmplitudeMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetAmplitudeMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetAmplitude").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetAmplitudeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetAmplitude").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetAmplitudeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyAmplitude").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyAmplitudeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetAmplitudeRanges").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetAmplitudeRangesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetAmplitudeRange").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetAmplitudeRangeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetAmplitudeRange").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetAmplitudeRangeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetAmplitudeAutoRanging").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetAmplitudeAutoRangingWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetAmplitudeAutoRanging").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetAmplitudeAutoRangingWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasOffset").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasOffsetWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetOffsetMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetOffsetMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetOffsetMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetOffsetMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetOffset").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetOffsetWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetOffset").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetOffsetWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyOffset").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyOffsetWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetFrequencyModes").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetFrequencyModesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetFrequencyMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetFrequencyModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetFrequencyMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetFrequencyModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetFrequencyMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetFrequencyMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetFrequencyMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetFrequencyMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyFrequency").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyFrequencyWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasPhase").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasPhaseWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetPhaseMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetPhaseMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetPhaseMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetPhaseMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetPhase").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetPhaseWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetPhase").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetPhaseWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyPhase").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyPhaseWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasSymmetry").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasSymmetryWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetSymmetryMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetSymmetryMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetSymmetryMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetSymmetryMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetSymmetry").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetSymmetryWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetSymmetry").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetSymmetryWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifySymmetry").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifySymmetryWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasWidth").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasWidthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetWidthMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetWidthMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetWidthMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetWidthMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetWidth").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetWidthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetWidth").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetWidthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyWidth").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyWidthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasEdgeTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasEdgeTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetLeadingEdgeTimeMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetLeadingEdgeTimeMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetLeadingEdgeTimeMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetLeadingEdgeTimeMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetLeadingEdgeTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetLeadingEdgeTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetLeadingEdgeTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetLeadingEdgeTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyLeadingEdgeTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyLeadingEdgeTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetTrailingEdgeTimeMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetTrailingEdgeTimeMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetTrailingEdgeTimeMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetTrailingEdgeTimeMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetTrailingEdgeTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetTrailingEdgeTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetTrailingEdgeTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetTrailingEdgeTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyTrailingEdgeTime").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyTrailingEdgeTimeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenHasData").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenHasDataWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetDataLengthMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetDataLengthMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetDataLengthMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetDataLengthMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetDataLength").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetDataLengthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyDataLength").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyDataLengthWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetModes").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetModesWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetModesNative").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetModesNativeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetMode").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetModeWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenIsBurstActive").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenIsBurstActiveWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstCountMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstCountMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstCountMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstCountMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetBurstCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetBurstCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstSampleCountMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstSampleCountMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstSampleCountMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstSampleCountMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstSampleCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstSampleCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetBurstSampleCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetBurstSampleCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstSegmentCountMin").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstSegmentCountMinWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstSegmentCountMax").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstSegmentCountMaxWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenGetBurstSegmentCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenGetBurstSegmentCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenSetBurstSegmentCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenSetBurstSegmentCountWrapper)->GetFunction());
  Nan::Set(api, Nan::New<v8::String>("GenVerifyBurstSegmentCount").ToLocalChecked(), Nan::New<v8::FunctionTemplate>(GenVerifyBurstSegmentCountWrapper)->GetFunction());

  v8::Local<v8::Array> constants = Nan::New<v8::Array>();
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_VERSION_MAJOR").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_VERSION_MAJOR), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_VERSION_MINOR").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_VERSION_MINOR), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_VERSION_RELEASE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_VERSION_RELEASE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_VERSION_NUMBER").ToLocalChecked(), Nan::New<v8::String>(LIBTIEPIE_VERSION_NUMBER).ToLocalChecked(), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_VERSION").ToLocalChecked(), Nan::New<v8::String>(LIBTIEPIE_VERSION).ToLocalChecked(), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_REVISION").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_REVISION), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_HANDLE_INVALID").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_HANDLE_INVALID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_INTERFACE_DEVICE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_INTERFACE_DEVICE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_INTERFACE_OSCILLOSCOPE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_INTERFACE_OSCILLOSCOPE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_INTERFACE_GENERATOR").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_INTERFACE_GENERATOR), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_INTERFACE_I2CHOST").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_INTERFACE_I2CHOST), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DEVICETYPE_OSCILLOSCOPE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DEVICETYPE_OSCILLOSCOPE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DEVICETYPE_GENERATOR").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DEVICETYPE_GENERATOR), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DEVICETYPE_I2CHOST").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DEVICETYPE_I2CHOST), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DEVICETYPE_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DEVICETYPE_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("IDKIND_PRODUCTID").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)IDKIND_PRODUCTID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("IDKIND_INDEX").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)IDKIND_INDEX), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("IDKIND_SERIALNUMBER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)IDKIND_SERIALNUMBER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("IDKIND_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)IDKIND_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_SUCCESS").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_SUCCESS), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_VALUE_CLIPPED").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_VALUE_CLIPPED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_VALUE_MODIFIED").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_VALUE_MODIFIED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_UNSUCCESSFUL").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_UNSUCCESSFUL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_NOT_SUPPORTED").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_NOT_SUPPORTED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_HANDLE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_HANDLE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_VALUE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_VALUE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_CHANNEL").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_CHANNEL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_TRIGGER_SOURCE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_TRIGGER_SOURCE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_DEVICE_TYPE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_DEVICE_TYPE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_DEVICE_INDEX").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_DEVICE_INDEX), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_PRODUCT_ID").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_PRODUCT_ID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_DEVICE_SERIALNUMBER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_OBJECT_GONE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_OBJECT_GONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INTERNAL_ADDRESS").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INTERNAL_ADDRESS), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_NOT_CONTROLLABLE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_NOT_CONTROLLABLE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_BIT_ERROR").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_BIT_ERROR), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_NO_ACKNOWLEDGE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_NO_ACKNOWLEDGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_CONTAINED_DEVICE_SERIALNUMBER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_INPUT").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_INPUT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_OUTPUT").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_OUTPUT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_DRIVER").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_DRIVER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_NOT_AVAILABLE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_NOT_AVAILABLE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_FIRMWARE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_FIRMWARE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_INDEX").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_INDEX), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_EEPROM").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_EEPROM), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INITIALIZATION_FAILED").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INITIALIZATION_FAILED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_LIBRARY_NOT_INITIALIZED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_NO_TRIGGER_ENABLED").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_NO_TRIGGER_ENABLED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_SYNCHRONIZATION_FAILED").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_SYNCHRONIZATION_FAILED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_INVALID_HS56_COMBINED_DEVICE").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_INVALID_HS56_COMBINED_DEVICE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIESTATUS_MEASUREMENT_RUNNING").ToLocalChecked(), Nan::New<v8::Int32>((int32_t)LIBTIEPIESTATUS_MEASUREMENT_RUNNING), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CONNECTORTYPE_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CONNECTORTYPE_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CONNECTORTYPE_BNC").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CONNECTORTYPE_BNC), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CONNECTORTYPE_BANANA").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CONNECTORTYPE_BANANA), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CONNECTORTYPE_POWERPLUG").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CONNECTORTYPE_POWERPLUG), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CONNECTORTYPE_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CONNECTORTYPE_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CONNECTORTYPE_MASK").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CONNECTORTYPE_MASK), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_INT8").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_INT8), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_INT16").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_INT16), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_INT32").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_INT32), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_INT64").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_INT64), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_UINT8").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_UINT8), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_UINT16").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_UINT16), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_UINT32").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_UINT32), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_UINT64").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_UINT64), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_FLOAT32").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_FLOAT32), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_FLOAT64").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_FLOAT64), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_MASK_INT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_MASK_INT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_MASK_UINT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_MASK_UINT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_MASK_FLOAT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_MASK_FLOAT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DATARAWTYPE_MASK_FIXED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DATARAWTYPE_MASK_FIXED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_TRIGGERIO_INDEX_INVALID").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_TRIGGERIO_INDEX_INVALID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_STRING_LENGTH_NULL_TERMINATED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("LIBTIEPIE_RANGEINDEX_AUTO").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)LIBTIEPIE_RANGEINDEX_AUTO), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ARN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ARN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ARB_DISABLED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ARB_DISABLED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ARB_NATIVEONLY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ARB_NATIVEONLY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ARB_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ARB_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("AR_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)AR_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("AR_DISABLED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)AR_DISABLED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("AR_NATIVEONLY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)AR_NATIVEONLY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("AR_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)AR_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ARM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ARM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ARM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ARM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ARM_ENABLED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ARM_ENABLED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKB_DCV").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKB_DCV), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKB_ACV").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKB_ACV), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKB_DCA").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKB_DCA), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKB_ACA").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKB_ACA), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKB_OHM").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKB_OHM), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CK_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CK_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CK_DCV").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CK_DCV), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CK_ACV").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CK_ACV), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CK_DCA").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CK_DCA), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CK_ACA").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CK_ACA), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CK_OHM").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CK_OHM), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKM_V").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKM_V), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKM_A").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKM_A), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKM_OHM").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKM_OHM), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKM_ASYMMETRICRANGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKM_ASYMMETRICRANGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CKM_SYMMETRICRANGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CKM_SYMMETRICRANGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CON_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CON_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("COB_DISABLED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)COB_DISABLED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("COB_SAMPLE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)COB_SAMPLE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("COB_FIXED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)COB_FIXED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CO_DISABLED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CO_DISABLED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CO_SAMPLE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CO_SAMPLE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CO_FIXED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CO_FIXED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("COM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)COM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("COM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)COM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("COM_ENABLED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)COM_ENABLED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("COM_FREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)COM_FREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CSN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CSN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CSB_EXTERNAL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CSB_EXTERNAL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CSB_INTERNAL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CSB_INTERNAL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CS_EXTERNAL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CS_EXTERNAL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CS_INTERNAL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CS_INTERNAL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CSM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CSM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CSM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CSM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("CSM_FREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)CSM_FREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FMN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FMN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FMB_SIGNALFREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FMB_SIGNALFREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FMB_SAMPLEFREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FMB_SAMPLEFREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FM_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FM_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FM_SIGNALFREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FM_SIGNALFREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FM_SAMPLEFREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FM_SAMPLEFREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FMM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FMM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FMM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FMM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_CONTINUOUS").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_CONTINUOUS), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_BURST_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_BURST_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_GATED_PERIODS").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_GATED_PERIODS), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_GATED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_GATED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_GATED_PERIOD_START").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_GATED_PERIOD_START), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_GATED_PERIOD_FINISH").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_GATED_PERIOD_FINISH), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_GATED_RUN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_GATED_RUN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_GATED_RUN_OUTPUT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_GATED_RUN_OUTPUT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_BURST_SAMPLE_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_BURST_SAMPLE_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_BURST_SAMPLE_COUNT_OUTPUT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_BURST_SAMPLE_COUNT_OUTPUT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_BURST_SEGMENT_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_BURST_SEGMENT_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMB_BURST_SEGMENT_COUNT_OUTPUT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMB_BURST_SEGMENT_COUNT_OUTPUT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_CONTINUOUS").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_CONTINUOUS), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_BURST_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_BURST_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_GATED_PERIODS").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_GATED_PERIODS), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_GATED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_GATED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_GATED_PERIOD_START").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_GATED_PERIOD_START), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_GATED_PERIOD_FINISH").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_GATED_PERIOD_FINISH), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_GATED_RUN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_GATED_RUN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_GATED_RUN_OUTPUT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_GATED_RUN_OUTPUT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_BURST_SAMPLE_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_BURST_SAMPLE_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_BURST_SAMPLE_COUNT_OUTPUT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_BURST_SAMPLE_COUNT_OUTPUT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_BURST_SEGMENT_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_BURST_SEGMENT_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GM_BURST_SEGMENT_COUNT_OUTPUT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GM_BURST_SEGMENT_COUNT_OUTPUT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_BURST_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_BURST_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_GATED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_GATED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_BURST_SAMPLE_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_BURST_SAMPLE_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_BURST_SEGMENT_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_BURST_SEGMENT_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_BURST").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_BURST), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_REQUIRE_TRIGGER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_REQUIRE_TRIGGER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_SIGNALFREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_SIGNALFREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_SAMPLEFREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_SAMPLEFREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_SINE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_SINE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_TRIANGLE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_TRIANGLE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_SQUARE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_SQUARE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_DC").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_DC), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_NOISE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_NOISE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_ARBITRARY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_ARBITRARY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GMM_PULSE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GMM_PULSE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GSN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GSN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GSB_STOPPED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GSB_STOPPED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GSB_RUNNING").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GSB_RUNNING), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GSB_BURSTACTIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GSB_BURSTACTIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GSB_WAITING").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GSB_WAITING), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GS_STOPPED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GS_STOPPED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GS_RUNNING").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GS_RUNNING), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GS_BURSTACTIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GS_BURSTACTIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GS_WAITING").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GS_WAITING), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GSM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GSM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("GSM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)GSM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("MMN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)MMN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("MMB_STREAM").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)MMB_STREAM), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("MMB_BLOCK").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)MMB_BLOCK), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("MMM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)MMM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("MMM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)MMM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("MM_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)MM_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("MM_STREAM").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)MM_STREAM), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("MM_BLOCK").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)MM_BLOCK), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STB_SINE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STB_SINE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STB_TRIANGLE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STB_TRIANGLE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STB_SQUARE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STB_SQUARE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STB_DC").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STB_DC), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STB_NOISE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STB_NOISE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STB_ARBITRARY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STB_ARBITRARY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STB_PULSE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STB_PULSE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ST_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ST_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ST_SINE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ST_SINE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ST_TRIANGLE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ST_TRIANGLE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ST_SQUARE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ST_SQUARE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ST_DC").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ST_DC), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ST_NOISE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ST_NOISE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ST_ARBITRARY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ST_ARBITRARY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("ST_PULSE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)ST_PULSE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_AMPLITUDE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_AMPLITUDE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_OFFSET").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_OFFSET), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_FREQUENCY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_FREQUENCY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_PHASE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_PHASE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_SYMMETRY").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_SYMMETRY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_WIDTH").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_WIDTH), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_LEADINGEDGETIME").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_LEADINGEDGETIME), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_TRAILINGEDGETIME").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_TRAILINGEDGETIME), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_DATALENGTH").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_DATALENGTH), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_DATA").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_DATA), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("STM_EDGETIME").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)STM_EDGETIME), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCB_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCB_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCB_SMALLER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCB_SMALLER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCB_LARGER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCB_LARGER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCB_INSIDE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCB_INSIDE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCB_OUTSIDE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCB_OUTSIDE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TC_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TC_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TC_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TC_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TC_SMALLER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TC_SMALLER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TC_LARGER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TC_LARGER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TC_INSIDE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TC_INSIDE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TC_OUTSIDE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TC_OUTSIDE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TCM_ENABLED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TCM_ENABLED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TH_ALLPRESAMPLES").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TH_ALLPRESAMPLES), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DN_MAIN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DN_MAIN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DN_SUB_FIRST").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DN_SUB_FIRST), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("DN_SUB_SECOND").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)DN_SUB_SECOND), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PGID_OSCILLOSCOPE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PGID_OSCILLOSCOPE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PGID_GENERATOR").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PGID_GENERATOR), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PGID_EXTERNAL_DSUB").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PGID_EXTERNAL_DSUB), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("SGID_MAIN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)SGID_MAIN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("SGID_CHANNEL1").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)SGID_CHANNEL1), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("SGID_CHANNEL2").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)SGID_CHANNEL2), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("SGID_PIN1").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)SGID_PIN1), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("SGID_PIN2").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)SGID_PIN2), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("SGID_PIN3").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)SGID_PIN3), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FID_SCP_TRIGGERED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FID_SCP_TRIGGERED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FID_GEN_START").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FID_GEN_START), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FID_GEN_STOP").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FID_GEN_STOP), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FID_GEN_NEW_PERIOD").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FID_GEN_NEW_PERIOD), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("FID_EXT_TRIGGERED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)FID_EXT_TRIGGERED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIOID_SHIFT_PGID").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIOID_SHIFT_PGID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIOID_SHIFT_DN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIOID_SHIFT_DN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIOID_SHIFT_SGID").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIOID_SHIFT_SGID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIOID_SHIFT_FID").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIOID_SHIFT_FID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIID_INVALID").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIID_INVALID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIID_EXT1").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIID_EXT1), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIID_EXT2").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIID_EXT2), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIID_EXT3").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIID_EXT3), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIID_GENERATOR_START").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIID_GENERATOR_START), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIID_GENERATOR_STOP").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIID_GENERATOR_STOP), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TIID_GENERATOR_NEW_PERIOD").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TIID_GENERATOR_NEW_PERIOD), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOID_INVALID").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOID_INVALID), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOID_EXT1").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOID_EXT1), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOID_EXT2").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOID_EXT2), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOID_EXT3").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOID_EXT3), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_RISINGEDGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_RISINGEDGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_FALLINGEDGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_FALLINGEDGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_INWINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_INWINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_OUTWINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_OUTWINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_ANYEDGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_ANYEDGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_ENTERWINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_ENTERWINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_EXITWINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_EXITWINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_PULSEWIDTHPOSITIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_PULSEWIDTHPOSITIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_PULSEWIDTHNEGATIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_PULSEWIDTHNEGATIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_PULSEWIDTHEITHER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_PULSEWIDTHEITHER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_RUNTPULSEPOSITIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_RUNTPULSEPOSITIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_RUNTPULSENEGATIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_RUNTPULSENEGATIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKB_RUNTPULSEEITHER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKB_RUNTPULSEEITHER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_RISINGEDGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_RISINGEDGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_FALLINGEDGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_FALLINGEDGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_INWINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_INWINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_OUTWINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_OUTWINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_ANYEDGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_ANYEDGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_ENTERWINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_ENTERWINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_EXITWINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_EXITWINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_PULSEWIDTHPOSITIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_PULSEWIDTHPOSITIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_PULSEWIDTHNEGATIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_PULSEWIDTHNEGATIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_PULSEWIDTHEITHER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_PULSEWIDTHEITHER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_RUNTPULSEPOSITIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_RUNTPULSEPOSITIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_RUNTPULSENEGATIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_RUNTPULSENEGATIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TK_RUNTPULSEEITHER").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TK_RUNTPULSEEITHER), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKM_EDGE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKM_EDGE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKM_WINDOW").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKM_WINDOW), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKM_PULSEWIDTH").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKM_PULSEWIDTH), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKM_RUNTPULSE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKM_RUNTPULSE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKM_PULSE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKM_PULSE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKM_TIME").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKM_TIME), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TKM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TKM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TLMN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TLMN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TLMB_RELATIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TLMB_RELATIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TLMB_ABSOLUTE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TLMB_ABSOLUTE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TLM_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TLM_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TLM_RELATIVE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TLM_RELATIVE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TLM_ABSOLUTE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TLM_ABSOLUTE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TLMM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TLMM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TLMM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TLMM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TO_INFINITY").ToLocalChecked(), Nan::New<v8::Number>(TO_INFINITY), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEN_COUNT").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEN_COUNT), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEB_GENERATOR_START").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEB_GENERATOR_START), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEB_GENERATOR_STOP").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEB_GENERATOR_STOP), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEB_GENERATOR_NEWPERIOD").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEB_GENERATOR_NEWPERIOD), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEB_OSCILLOSCOPE_RUNNING").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEB_OSCILLOSCOPE_RUNNING), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEB_OSCILLOSCOPE_TRIGGERED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEB_OSCILLOSCOPE_TRIGGERED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEB_MANUAL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEB_MANUAL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOE_UNKNOWN").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOE_UNKNOWN), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOE_GENERATOR_START").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOE_GENERATOR_START), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOE_GENERATOR_STOP").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOE_GENERATOR_STOP), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOE_GENERATOR_NEWPERIOD").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOE_GENERATOR_NEWPERIOD), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOE_OSCILLOSCOPE_RUNNING").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOE_OSCILLOSCOPE_RUNNING), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOE_OSCILLOSCOPE_TRIGGERED").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOE_OSCILLOSCOPE_TRIGGERED), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOE_MANUAL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOE_MANUAL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEM_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEM_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEM_GENERATOR").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEM_GENERATOR), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEM_OSCILLOSCOPE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEM_OSCILLOSCOPE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("TOEM_ALL").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)TOEM_ALL), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_NONE").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_NONE), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_COMBI").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_COMBI), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_HS3").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_HS3), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_HS4").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_HS4), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_HP3").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_HP3), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_TP450").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_TP450), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_HS4D").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_HS4D), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_HS5").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_HS5), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_HS6D").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_HS6D), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_ATS610004D").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_ATS610004D), v8::ReadOnly);
  Nan::DefineOwnProperty(constants, Nan::New<v8::String>("PID_ATS605004D").ToLocalChecked(), Nan::New<v8::Uint32>((uint32_t)PID_ATS605004D), v8::ReadOnly);

  Nan::Set(target, Nan::New<v8::String>("const").ToLocalChecked(), constants);
  Nan::Set(target, Nan::New<v8::String>("api").ToLocalChecked(), api);

  LibInit();
  node::AtExit(AtExit);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)
