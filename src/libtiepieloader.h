/**
 * \file libtiepieloader.h
 * \brief Dynamic loader for libtiepie.
 */

#ifndef _LIBTIEPIELOADER_H_
#define _LIBTIEPIELOADER_H_

#ifndef LIBTIEPIE_DYNAMIC
#  error LIBTIEPIE_DYNAMIC not defined!
#endif

#include <libtiepie.h>

extern LibTiePieLibInit_t LibInit;
extern LibTiePieLibIsInitialized_t LibIsInitialized;
extern LibTiePieLibExit_t LibExit;
extern LibTiePieLibGetVersion_t LibGetVersion;
extern LibTiePieLibGetVersionExtra_t LibGetVersionExtra;
extern LibTiePieLibGetConfig_t LibGetConfig;
extern LibTiePieLibGetLastStatus_t LibGetLastStatus;
extern LibTiePieLibGetLastStatusStr_t LibGetLastStatusStr;
extern LibTiePieLstUpdate_t LstUpdate;
extern LibTiePieLstGetCount_t LstGetCount;
extern LibTiePieLstOpenDevice_t LstOpenDevice;
extern LibTiePieLstOpenOscilloscope_t LstOpenOscilloscope;
extern LibTiePieLstOpenGenerator_t LstOpenGenerator;
extern LibTiePieLstOpenI2CHost_t LstOpenI2CHost;
extern LibTiePieLstCreateCombinedDevice_t LstCreateCombinedDevice;
extern LibTiePieLstCreateAndOpenCombinedDevice_t LstCreateAndOpenCombinedDevice;
extern LibTiePieLstRemoveDevice_t LstRemoveDevice;
extern LibTiePieLstDevCanOpen_t LstDevCanOpen;
extern LibTiePieLstDevGetProductId_t LstDevGetProductId;
extern LibTiePieLstDevGetVendorId_t LstDevGetVendorId;
extern LibTiePieLstDevGetName_t LstDevGetName;
extern LibTiePieLstDevGetNameShort_t LstDevGetNameShort;
extern LibTiePieLstDevGetNameShortest_t LstDevGetNameShortest;
extern LibTiePieLstDevGetDriverVersion_t LstDevGetDriverVersion;
extern LibTiePieLstDevGetRecommendedDriverVersion_t LstDevGetRecommendedDriverVersion;
extern LibTiePieLstDevGetFirmwareVersion_t LstDevGetFirmwareVersion;
extern LibTiePieLstDevGetRecommendedFirmwareVersion_t LstDevGetRecommendedFirmwareVersion;
extern LibTiePieLstDevGetCalibrationDate_t LstDevGetCalibrationDate;
extern LibTiePieLstDevGetSerialNumber_t LstDevGetSerialNumber;
extern LibTiePieLstDevGetIPv4Address_t LstDevGetIPv4Address;
extern LibTiePieLstDevGetIPPort_t LstDevGetIPPort;
extern LibTiePieLstDevHasServer_t LstDevHasServer;
extern LibTiePieLstDevGetServer_t LstDevGetServer;
extern LibTiePieLstDevGetTypes_t LstDevGetTypes;
extern LibTiePieLstDevGetContainedSerialNumbers_t LstDevGetContainedSerialNumbers;
extern LibTiePieLstCbDevGetProductId_t LstCbDevGetProductId;
extern LibTiePieLstCbDevGetVendorId_t LstCbDevGetVendorId;
extern LibTiePieLstCbDevGetName_t LstCbDevGetName;
extern LibTiePieLstCbDevGetNameShort_t LstCbDevGetNameShort;
extern LibTiePieLstCbDevGetNameShortest_t LstCbDevGetNameShortest;
extern LibTiePieLstCbDevGetDriverVersion_t LstCbDevGetDriverVersion;
extern LibTiePieLstCbDevGetFirmwareVersion_t LstCbDevGetFirmwareVersion;
extern LibTiePieLstCbDevGetCalibrationDate_t LstCbDevGetCalibrationDate;
extern LibTiePieLstCbScpGetChannelCount_t LstCbScpGetChannelCount;
extern LibTiePieLstSetCallbackDeviceAdded_t LstSetCallbackDeviceAdded;
extern LibTiePieLstSetCallbackDeviceRemoved_t LstSetCallbackDeviceRemoved;
extern LibTiePieLstSetCallbackDeviceCanOpenChanged_t LstSetCallbackDeviceCanOpenChanged;
#ifdef LIBTIEPIE_LINUX
extern LibTiePieLstSetEventDeviceAdded_t LstSetEventDeviceAdded;
extern LibTiePieLstSetEventDeviceRemoved_t LstSetEventDeviceRemoved;
extern LibTiePieLstSetEventDeviceCanOpenChanged_t LstSetEventDeviceCanOpenChanged;
#endif
#ifdef LIBTIEPIE_WINDOWS
extern LibTiePieLstSetEventDeviceAdded_t LstSetEventDeviceAdded;
extern LibTiePieLstSetEventDeviceRemoved_t LstSetEventDeviceRemoved;
extern LibTiePieLstSetEventDeviceCanOpenChanged_t LstSetEventDeviceCanOpenChanged;
extern LibTiePieLstSetMessageDeviceAdded_t LstSetMessageDeviceAdded;
extern LibTiePieLstSetMessageDeviceRemoved_t LstSetMessageDeviceRemoved;
extern LibTiePieLstSetMessageDeviceCanOpenChanged_t LstSetMessageDeviceCanOpenChanged;
#endif
extern LibTiePieNetGetAutoDetectEnabled_t NetGetAutoDetectEnabled;
extern LibTiePieNetSetAutoDetectEnabled_t NetSetAutoDetectEnabled;
extern LibTiePieNetSrvAdd_t NetSrvAdd;
extern LibTiePieNetSrvRemove_t NetSrvRemove;
extern LibTiePieNetSrvGetCount_t NetSrvGetCount;
extern LibTiePieNetSrvGetByIndex_t NetSrvGetByIndex;
extern LibTiePieNetSrvGetByURL_t NetSrvGetByURL;
extern LibTiePieNetSrvSetCallbackAdded_t NetSrvSetCallbackAdded;
#ifdef LIBTIEPIE_LINUX
extern LibTiePieNetSrvSetEventAdded_t NetSrvSetEventAdded;
#endif
#ifdef LIBTIEPIE_WINDOWS
extern LibTiePieNetSrvSetEventAdded_t NetSrvSetEventAdded;
extern LibTiePieNetSrvSetMessageAdded_t NetSrvSetMessageAdded;
#endif
extern LibTiePieObjClose_t ObjClose;
extern LibTiePieObjIsRemoved_t ObjIsRemoved;
extern LibTiePieObjGetInterfaces_t ObjGetInterfaces;
extern LibTiePieObjSetEventCallback_t ObjSetEventCallback;
extern LibTiePieObjGetEvent_t ObjGetEvent;
#ifdef LIBTIEPIE_LINUX
extern LibTiePieObjSetEventEvent_t ObjSetEventEvent;
#endif
#ifdef LIBTIEPIE_WINDOWS
extern LibTiePieObjSetEventEvent_t ObjSetEventEvent;
extern LibTiePieObjSetEventWindowHandle_t ObjSetEventWindowHandle;
#endif
extern LibTiePieDevClose_t DevClose;
extern LibTiePieDevIsRemoved_t DevIsRemoved;
extern LibTiePieDevGetDriverVersion_t DevGetDriverVersion;
extern LibTiePieDevGetFirmwareVersion_t DevGetFirmwareVersion;
extern LibTiePieDevGetCalibrationDate_t DevGetCalibrationDate;
extern LibTiePieDevGetCalibrationToken_t DevGetCalibrationToken;
extern LibTiePieDevGetSerialNumber_t DevGetSerialNumber;
extern LibTiePieDevGetIPv4Address_t DevGetIPv4Address;
extern LibTiePieDevGetIPPort_t DevGetIPPort;
extern LibTiePieDevGetProductId_t DevGetProductId;
extern LibTiePieDevGetVendorId_t DevGetVendorId;
extern LibTiePieDevGetType_t DevGetType;
extern LibTiePieDevGetName_t DevGetName;
extern LibTiePieDevGetNameShort_t DevGetNameShort;
extern LibTiePieDevGetNameShortest_t DevGetNameShortest;
extern LibTiePieDevHasBattery_t DevHasBattery;
extern LibTiePieDevGetBatteryCharge_t DevGetBatteryCharge;
extern LibTiePieDevGetBatteryTimeToEmpty_t DevGetBatteryTimeToEmpty;
extern LibTiePieDevGetBatteryTimeToFull_t DevGetBatteryTimeToFull;
extern LibTiePieDevIsBatteryChargerConnected_t DevIsBatteryChargerConnected;
extern LibTiePieDevIsBatteryCharging_t DevIsBatteryCharging;
extern LibTiePieDevIsBatteryBroken_t DevIsBatteryBroken;
extern LibTiePieDevSetCallbackRemoved_t DevSetCallbackRemoved;
#ifdef LIBTIEPIE_LINUX
extern LibTiePieDevSetEventRemoved_t DevSetEventRemoved;
#endif
#ifdef LIBTIEPIE_WINDOWS
extern LibTiePieDevSetEventRemoved_t DevSetEventRemoved;
extern LibTiePieDevSetMessageRemoved_t DevSetMessageRemoved;
#endif
extern LibTiePieDevTrGetInputCount_t DevTrGetInputCount;
extern LibTiePieDevTrGetInputIndexById_t DevTrGetInputIndexById;
extern LibTiePieScpTrInIsTriggered_t ScpTrInIsTriggered;
extern LibTiePieDevTrInGetEnabled_t DevTrInGetEnabled;
extern LibTiePieDevTrInSetEnabled_t DevTrInSetEnabled;
extern LibTiePieDevTrInGetKinds_t DevTrInGetKinds;
extern LibTiePieScpTrInGetKindsEx_t ScpTrInGetKindsEx;
extern LibTiePieDevTrInGetKind_t DevTrInGetKind;
extern LibTiePieDevTrInSetKind_t DevTrInSetKind;
extern LibTiePieDevTrInIsAvailable_t DevTrInIsAvailable;
extern LibTiePieScpTrInIsAvailableEx_t ScpTrInIsAvailableEx;
extern LibTiePieDevTrInGetId_t DevTrInGetId;
extern LibTiePieDevTrInGetName_t DevTrInGetName;
extern LibTiePieDevTrGetOutputCount_t DevTrGetOutputCount;
extern LibTiePieDevTrGetOutputIndexById_t DevTrGetOutputIndexById;
extern LibTiePieDevTrOutGetEnabled_t DevTrOutGetEnabled;
extern LibTiePieDevTrOutSetEnabled_t DevTrOutSetEnabled;
extern LibTiePieDevTrOutGetEvents_t DevTrOutGetEvents;
extern LibTiePieDevTrOutGetEvent_t DevTrOutGetEvent;
extern LibTiePieDevTrOutSetEvent_t DevTrOutSetEvent;
extern LibTiePieDevTrOutGetId_t DevTrOutGetId;
extern LibTiePieDevTrOutGetName_t DevTrOutGetName;
extern LibTiePieDevTrOutTrigger_t DevTrOutTrigger;
extern LibTiePieScpGetChannelCount_t ScpGetChannelCount;
extern LibTiePieScpChIsAvailable_t ScpChIsAvailable;
extern LibTiePieScpChIsAvailableEx_t ScpChIsAvailableEx;
extern LibTiePieScpChGetConnectorType_t ScpChGetConnectorType;
extern LibTiePieScpChIsDifferential_t ScpChIsDifferential;
extern LibTiePieScpChGetImpedance_t ScpChGetImpedance;
extern LibTiePieScpChGetBandwidths_t ScpChGetBandwidths;
extern LibTiePieScpChGetBandwidth_t ScpChGetBandwidth;
extern LibTiePieScpChSetBandwidth_t ScpChSetBandwidth;
extern LibTiePieScpChGetCouplings_t ScpChGetCouplings;
extern LibTiePieScpChGetCoupling_t ScpChGetCoupling;
extern LibTiePieScpChSetCoupling_t ScpChSetCoupling;
extern LibTiePieScpChGetEnabled_t ScpChGetEnabled;
extern LibTiePieScpChSetEnabled_t ScpChSetEnabled;
extern LibTiePieScpChGetProbeGain_t ScpChGetProbeGain;
extern LibTiePieScpChSetProbeGain_t ScpChSetProbeGain;
extern LibTiePieScpChGetProbeOffset_t ScpChGetProbeOffset;
extern LibTiePieScpChSetProbeOffset_t ScpChSetProbeOffset;
extern LibTiePieScpChGetAutoRanging_t ScpChGetAutoRanging;
extern LibTiePieScpChSetAutoRanging_t ScpChSetAutoRanging;
extern LibTiePieScpChGetRanges_t ScpChGetRanges;
extern LibTiePieScpChGetRangesEx_t ScpChGetRangesEx;
extern LibTiePieScpChGetRange_t ScpChGetRange;
extern LibTiePieScpChSetRange_t ScpChSetRange;
extern LibTiePieScpChHasSafeGround_t ScpChHasSafeGround;
extern LibTiePieScpChGetSafeGroundEnabled_t ScpChGetSafeGroundEnabled;
extern LibTiePieScpChSetSafeGroundEnabled_t ScpChSetSafeGroundEnabled;
extern LibTiePieScpChGetSafeGroundThresholdMin_t ScpChGetSafeGroundThresholdMin;
extern LibTiePieScpChGetSafeGroundThresholdMax_t ScpChGetSafeGroundThresholdMax;
extern LibTiePieScpChGetSafeGroundThreshold_t ScpChGetSafeGroundThreshold;
extern LibTiePieScpChSetSafeGroundThreshold_t ScpChSetSafeGroundThreshold;
extern LibTiePieScpChVerifySafeGroundThreshold_t ScpChVerifySafeGroundThreshold;
extern LibTiePieScpChHasTrigger_t ScpChHasTrigger;
extern LibTiePieScpChHasTriggerEx_t ScpChHasTriggerEx;
extern LibTiePieScpChTrIsAvailable_t ScpChTrIsAvailable;
extern LibTiePieScpChTrIsAvailableEx_t ScpChTrIsAvailableEx;
extern LibTiePieScpChTrIsTriggered_t ScpChTrIsTriggered;
extern LibTiePieScpChTrGetEnabled_t ScpChTrGetEnabled;
extern LibTiePieScpChTrSetEnabled_t ScpChTrSetEnabled;
extern LibTiePieScpChTrGetKinds_t ScpChTrGetKinds;
extern LibTiePieScpChTrGetKindsEx_t ScpChTrGetKindsEx;
extern LibTiePieScpChTrGetKind_t ScpChTrGetKind;
extern LibTiePieScpChTrSetKind_t ScpChTrSetKind;
extern LibTiePieScpChTrGetLevelModes_t ScpChTrGetLevelModes;
extern LibTiePieScpChTrGetLevelMode_t ScpChTrGetLevelMode;
extern LibTiePieScpChTrSetLevelMode_t ScpChTrSetLevelMode;
extern LibTiePieScpChTrGetLevelCount_t ScpChTrGetLevelCount;
extern LibTiePieScpChTrGetLevel_t ScpChTrGetLevel;
extern LibTiePieScpChTrSetLevel_t ScpChTrSetLevel;
extern LibTiePieScpChTrGetHysteresisCount_t ScpChTrGetHysteresisCount;
extern LibTiePieScpChTrGetHysteresis_t ScpChTrGetHysteresis;
extern LibTiePieScpChTrSetHysteresis_t ScpChTrSetHysteresis;
extern LibTiePieScpChTrGetConditions_t ScpChTrGetConditions;
extern LibTiePieScpChTrGetConditionsEx_t ScpChTrGetConditionsEx;
extern LibTiePieScpChTrGetCondition_t ScpChTrGetCondition;
extern LibTiePieScpChTrSetCondition_t ScpChTrSetCondition;
extern LibTiePieScpChTrGetTimeCount_t ScpChTrGetTimeCount;
extern LibTiePieScpChTrGetTime_t ScpChTrGetTime;
extern LibTiePieScpChTrSetTime_t ScpChTrSetTime;
extern LibTiePieScpChTrVerifyTime_t ScpChTrVerifyTime;
extern LibTiePieScpChTrVerifyTimeEx2_t ScpChTrVerifyTimeEx2;
extern LibTiePieScpGetData_t ScpGetData;
extern LibTiePieScpGetData1Ch_t ScpGetData1Ch;
extern LibTiePieScpGetData2Ch_t ScpGetData2Ch;
extern LibTiePieScpGetData3Ch_t ScpGetData3Ch;
extern LibTiePieScpGetData4Ch_t ScpGetData4Ch;
extern LibTiePieScpGetValidPreSampleCount_t ScpGetValidPreSampleCount;
extern LibTiePieScpChGetDataValueRange_t ScpChGetDataValueRange;
extern LibTiePieScpChGetDataValueMin_t ScpChGetDataValueMin;
extern LibTiePieScpChGetDataValueMax_t ScpChGetDataValueMax;
extern LibTiePieScpGetDataRaw_t ScpGetDataRaw;
extern LibTiePieScpGetDataRaw1Ch_t ScpGetDataRaw1Ch;
extern LibTiePieScpGetDataRaw2Ch_t ScpGetDataRaw2Ch;
extern LibTiePieScpGetDataRaw3Ch_t ScpGetDataRaw3Ch;
extern LibTiePieScpGetDataRaw4Ch_t ScpGetDataRaw4Ch;
extern LibTiePieScpChGetDataRawType_t ScpChGetDataRawType;
extern LibTiePieScpChGetDataRawValueRange_t ScpChGetDataRawValueRange;
extern LibTiePieScpChGetDataRawValueMin_t ScpChGetDataRawValueMin;
extern LibTiePieScpChGetDataRawValueZero_t ScpChGetDataRawValueZero;
extern LibTiePieScpChGetDataRawValueMax_t ScpChGetDataRawValueMax;
extern LibTiePieScpChIsRangeMaxReachable_t ScpChIsRangeMaxReachable;
extern LibTiePieScpIsGetDataAsyncCompleted_t ScpIsGetDataAsyncCompleted;
extern LibTiePieScpStartGetDataAsync_t ScpStartGetDataAsync;
extern LibTiePieScpStartGetDataAsyncRaw_t ScpStartGetDataAsyncRaw;
extern LibTiePieScpCancelGetDataAsync_t ScpCancelGetDataAsync;
extern LibTiePieScpSetCallbackDataReady_t ScpSetCallbackDataReady;
extern LibTiePieScpSetCallbackDataOverflow_t ScpSetCallbackDataOverflow;
extern LibTiePieScpSetCallbackConnectionTestCompleted_t ScpSetCallbackConnectionTestCompleted;
extern LibTiePieScpSetCallbackTriggered_t ScpSetCallbackTriggered;
#ifdef LIBTIEPIE_LINUX
extern LibTiePieScpSetEventDataReady_t ScpSetEventDataReady;
extern LibTiePieScpSetEventDataOverflow_t ScpSetEventDataOverflow;
extern LibTiePieScpSetEventConnectionTestCompleted_t ScpSetEventConnectionTestCompleted;
extern LibTiePieScpSetEventTriggered_t ScpSetEventTriggered;
#endif
#ifdef LIBTIEPIE_WINDOWS
extern LibTiePieScpSetEventDataReady_t ScpSetEventDataReady;
extern LibTiePieScpSetEventDataOverflow_t ScpSetEventDataOverflow;
extern LibTiePieScpSetEventConnectionTestCompleted_t ScpSetEventConnectionTestCompleted;
extern LibTiePieScpSetEventTriggered_t ScpSetEventTriggered;
extern LibTiePieScpSetMessageDataReady_t ScpSetMessageDataReady;
extern LibTiePieScpSetMessageDataOverflow_t ScpSetMessageDataOverflow;
extern LibTiePieScpSetMessageConnectionTestCompleted_t ScpSetMessageConnectionTestCompleted;
extern LibTiePieScpSetMessageTriggered_t ScpSetMessageTriggered;
#endif
extern LibTiePieScpStart_t ScpStart;
extern LibTiePieScpStop_t ScpStop;
extern LibTiePieScpForceTrigger_t ScpForceTrigger;
extern LibTiePieScpGetMeasureModes_t ScpGetMeasureModes;
extern LibTiePieScpGetMeasureMode_t ScpGetMeasureMode;
extern LibTiePieScpSetMeasureMode_t ScpSetMeasureMode;
extern LibTiePieScpIsRunning_t ScpIsRunning;
extern LibTiePieScpIsTriggered_t ScpIsTriggered;
extern LibTiePieScpIsTimeOutTriggered_t ScpIsTimeOutTriggered;
extern LibTiePieScpIsForceTriggered_t ScpIsForceTriggered;
extern LibTiePieScpIsDataReady_t ScpIsDataReady;
extern LibTiePieScpIsDataOverflow_t ScpIsDataOverflow;
extern LibTiePieScpGetAutoResolutionModes_t ScpGetAutoResolutionModes;
extern LibTiePieScpGetAutoResolutionMode_t ScpGetAutoResolutionMode;
extern LibTiePieScpSetAutoResolutionMode_t ScpSetAutoResolutionMode;
extern LibTiePieScpGetResolutions_t ScpGetResolutions;
extern LibTiePieScpGetResolution_t ScpGetResolution;
extern LibTiePieScpSetResolution_t ScpSetResolution;
extern LibTiePieScpIsResolutionEnhanced_t ScpIsResolutionEnhanced;
extern LibTiePieScpIsResolutionEnhancedEx_t ScpIsResolutionEnhancedEx;
extern LibTiePieScpGetClockSources_t ScpGetClockSources;
extern LibTiePieScpGetClockSource_t ScpGetClockSource;
extern LibTiePieScpSetClockSource_t ScpSetClockSource;
extern LibTiePieScpGetClockSourceFrequencies_t ScpGetClockSourceFrequencies;
extern LibTiePieScpGetClockSourceFrequenciesEx_t ScpGetClockSourceFrequenciesEx;
extern LibTiePieScpGetClockSourceFrequency_t ScpGetClockSourceFrequency;
extern LibTiePieScpSetClockSourceFrequency_t ScpSetClockSourceFrequency;
extern LibTiePieScpGetClockOutputs_t ScpGetClockOutputs;
extern LibTiePieScpGetClockOutput_t ScpGetClockOutput;
extern LibTiePieScpSetClockOutput_t ScpSetClockOutput;
extern LibTiePieScpGetClockOutputFrequencies_t ScpGetClockOutputFrequencies;
extern LibTiePieScpGetClockOutputFrequenciesEx_t ScpGetClockOutputFrequenciesEx;
extern LibTiePieScpGetClockOutputFrequency_t ScpGetClockOutputFrequency;
extern LibTiePieScpSetClockOutputFrequency_t ScpSetClockOutputFrequency;
extern LibTiePieScpGetSampleFrequencyMax_t ScpGetSampleFrequencyMax;
extern LibTiePieScpGetSampleFrequency_t ScpGetSampleFrequency;
extern LibTiePieScpSetSampleFrequency_t ScpSetSampleFrequency;
extern LibTiePieScpVerifySampleFrequency_t ScpVerifySampleFrequency;
extern LibTiePieScpVerifySampleFrequencyEx_t ScpVerifySampleFrequencyEx;
extern LibTiePieScpVerifySampleFrequenciesEx_t ScpVerifySampleFrequenciesEx;
extern LibTiePieScpGetRecordLengthMax_t ScpGetRecordLengthMax;
extern LibTiePieScpGetRecordLengthMaxEx_t ScpGetRecordLengthMaxEx;
extern LibTiePieScpGetRecordLength_t ScpGetRecordLength;
extern LibTiePieScpSetRecordLength_t ScpSetRecordLength;
extern LibTiePieScpVerifyRecordLength_t ScpVerifyRecordLength;
extern LibTiePieScpVerifyRecordLengthEx_t ScpVerifyRecordLengthEx;
extern LibTiePieScpGetPreSampleRatio_t ScpGetPreSampleRatio;
extern LibTiePieScpSetPreSampleRatio_t ScpSetPreSampleRatio;
extern LibTiePieScpGetSegmentCountMax_t ScpGetSegmentCountMax;
extern LibTiePieScpGetSegmentCountMaxEx_t ScpGetSegmentCountMaxEx;
extern LibTiePieScpGetSegmentCount_t ScpGetSegmentCount;
extern LibTiePieScpSetSegmentCount_t ScpSetSegmentCount;
extern LibTiePieScpVerifySegmentCount_t ScpVerifySegmentCount;
extern LibTiePieScpVerifySegmentCountEx2_t ScpVerifySegmentCountEx2;
extern LibTiePieScpHasTrigger_t ScpHasTrigger;
extern LibTiePieScpHasTriggerEx_t ScpHasTriggerEx;
extern LibTiePieScpGetTriggerTimeOut_t ScpGetTriggerTimeOut;
extern LibTiePieScpSetTriggerTimeOut_t ScpSetTriggerTimeOut;
extern LibTiePieScpVerifyTriggerTimeOut_t ScpVerifyTriggerTimeOut;
extern LibTiePieScpVerifyTriggerTimeOutEx_t ScpVerifyTriggerTimeOutEx;
extern LibTiePieScpHasTriggerDelay_t ScpHasTriggerDelay;
extern LibTiePieScpHasTriggerDelayEx_t ScpHasTriggerDelayEx;
extern LibTiePieScpGetTriggerDelayMax_t ScpGetTriggerDelayMax;
extern LibTiePieScpGetTriggerDelayMaxEx_t ScpGetTriggerDelayMaxEx;
extern LibTiePieScpGetTriggerDelay_t ScpGetTriggerDelay;
extern LibTiePieScpSetTriggerDelay_t ScpSetTriggerDelay;
extern LibTiePieScpVerifyTriggerDelay_t ScpVerifyTriggerDelay;
extern LibTiePieScpVerifyTriggerDelayEx_t ScpVerifyTriggerDelayEx;
extern LibTiePieScpHasTriggerHoldOff_t ScpHasTriggerHoldOff;
extern LibTiePieScpHasTriggerHoldOffEx_t ScpHasTriggerHoldOffEx;
extern LibTiePieScpGetTriggerHoldOffCountMax_t ScpGetTriggerHoldOffCountMax;
extern LibTiePieScpGetTriggerHoldOffCountMaxEx_t ScpGetTriggerHoldOffCountMaxEx;
extern LibTiePieScpGetTriggerHoldOffCount_t ScpGetTriggerHoldOffCount;
extern LibTiePieScpSetTriggerHoldOffCount_t ScpSetTriggerHoldOffCount;
extern LibTiePieScpHasConnectionTest_t ScpHasConnectionTest;
extern LibTiePieScpChHasConnectionTest_t ScpChHasConnectionTest;
extern LibTiePieScpStartConnectionTest_t ScpStartConnectionTest;
extern LibTiePieScpStartConnectionTestEx_t ScpStartConnectionTestEx;
extern LibTiePieScpIsConnectionTestCompleted_t ScpIsConnectionTestCompleted;
extern LibTiePieScpGetConnectionTestData_t ScpGetConnectionTestData;
extern LibTiePieGenGetConnectorType_t GenGetConnectorType;
extern LibTiePieGenIsDifferential_t GenIsDifferential;
extern LibTiePieGenGetImpedance_t GenGetImpedance;
extern LibTiePieGenGetResolution_t GenGetResolution;
extern LibTiePieGenGetOutputValueMin_t GenGetOutputValueMin;
extern LibTiePieGenGetOutputValueMax_t GenGetOutputValueMax;
extern LibTiePieGenGetOutputValueMinMax_t GenGetOutputValueMinMax;
extern LibTiePieGenIsControllable_t GenIsControllable;
extern LibTiePieGenIsRunning_t GenIsRunning;
extern LibTiePieGenGetStatus_t GenGetStatus;
extern LibTiePieGenGetOutputOn_t GenGetOutputOn;
extern LibTiePieGenSetOutputOn_t GenSetOutputOn;
extern LibTiePieGenHasOutputInvert_t GenHasOutputInvert;
extern LibTiePieGenGetOutputInvert_t GenGetOutputInvert;
extern LibTiePieGenSetOutputInvert_t GenSetOutputInvert;
extern LibTiePieGenStart_t GenStart;
extern LibTiePieGenStop_t GenStop;
extern LibTiePieGenGetSignalTypes_t GenGetSignalTypes;
extern LibTiePieGenGetSignalType_t GenGetSignalType;
extern LibTiePieGenSetSignalType_t GenSetSignalType;
extern LibTiePieGenHasAmplitude_t GenHasAmplitude;
extern LibTiePieGenHasAmplitudeEx_t GenHasAmplitudeEx;
extern LibTiePieGenGetAmplitudeMin_t GenGetAmplitudeMin;
extern LibTiePieGenGetAmplitudeMax_t GenGetAmplitudeMax;
extern LibTiePieGenGetAmplitudeMinMaxEx_t GenGetAmplitudeMinMaxEx;
extern LibTiePieGenGetAmplitude_t GenGetAmplitude;
extern LibTiePieGenSetAmplitude_t GenSetAmplitude;
extern LibTiePieGenVerifyAmplitude_t GenVerifyAmplitude;
extern LibTiePieGenVerifyAmplitudeEx_t GenVerifyAmplitudeEx;
extern LibTiePieGenGetAmplitudeRanges_t GenGetAmplitudeRanges;
extern LibTiePieGenGetAmplitudeRange_t GenGetAmplitudeRange;
extern LibTiePieGenSetAmplitudeRange_t GenSetAmplitudeRange;
extern LibTiePieGenGetAmplitudeAutoRanging_t GenGetAmplitudeAutoRanging;
extern LibTiePieGenSetAmplitudeAutoRanging_t GenSetAmplitudeAutoRanging;
extern LibTiePieGenHasOffset_t GenHasOffset;
extern LibTiePieGenHasOffsetEx_t GenHasOffsetEx;
extern LibTiePieGenGetOffsetMin_t GenGetOffsetMin;
extern LibTiePieGenGetOffsetMax_t GenGetOffsetMax;
extern LibTiePieGenGetOffsetMinMaxEx_t GenGetOffsetMinMaxEx;
extern LibTiePieGenGetOffset_t GenGetOffset;
extern LibTiePieGenSetOffset_t GenSetOffset;
extern LibTiePieGenVerifyOffset_t GenVerifyOffset;
extern LibTiePieGenVerifyOffsetEx_t GenVerifyOffsetEx;
extern LibTiePieGenGetFrequencyModes_t GenGetFrequencyModes;
extern LibTiePieGenGetFrequencyModesEx_t GenGetFrequencyModesEx;
extern LibTiePieGenGetFrequencyMode_t GenGetFrequencyMode;
extern LibTiePieGenSetFrequencyMode_t GenSetFrequencyMode;
extern LibTiePieGenHasFrequency_t GenHasFrequency;
extern LibTiePieGenHasFrequencyEx_t GenHasFrequencyEx;
extern LibTiePieGenGetFrequencyMin_t GenGetFrequencyMin;
extern LibTiePieGenGetFrequencyMax_t GenGetFrequencyMax;
extern LibTiePieGenGetFrequencyMinMax_t GenGetFrequencyMinMax;
extern LibTiePieGenGetFrequencyMinMaxEx_t GenGetFrequencyMinMaxEx;
extern LibTiePieGenGetFrequency_t GenGetFrequency;
extern LibTiePieGenSetFrequency_t GenSetFrequency;
extern LibTiePieGenVerifyFrequency_t GenVerifyFrequency;
extern LibTiePieGenVerifyFrequencyEx2_t GenVerifyFrequencyEx2;
extern LibTiePieGenHasPhase_t GenHasPhase;
extern LibTiePieGenHasPhaseEx_t GenHasPhaseEx;
extern LibTiePieGenGetPhaseMin_t GenGetPhaseMin;
extern LibTiePieGenGetPhaseMax_t GenGetPhaseMax;
extern LibTiePieGenGetPhaseMinMaxEx_t GenGetPhaseMinMaxEx;
extern LibTiePieGenGetPhase_t GenGetPhase;
extern LibTiePieGenSetPhase_t GenSetPhase;
extern LibTiePieGenVerifyPhase_t GenVerifyPhase;
extern LibTiePieGenVerifyPhaseEx_t GenVerifyPhaseEx;
extern LibTiePieGenHasSymmetry_t GenHasSymmetry;
extern LibTiePieGenHasSymmetryEx_t GenHasSymmetryEx;
extern LibTiePieGenGetSymmetryMin_t GenGetSymmetryMin;
extern LibTiePieGenGetSymmetryMax_t GenGetSymmetryMax;
extern LibTiePieGenGetSymmetryMinMaxEx_t GenGetSymmetryMinMaxEx;
extern LibTiePieGenGetSymmetry_t GenGetSymmetry;
extern LibTiePieGenSetSymmetry_t GenSetSymmetry;
extern LibTiePieGenVerifySymmetry_t GenVerifySymmetry;
extern LibTiePieGenVerifySymmetryEx_t GenVerifySymmetryEx;
extern LibTiePieGenHasWidth_t GenHasWidth;
extern LibTiePieGenHasWidthEx_t GenHasWidthEx;
extern LibTiePieGenGetWidthMin_t GenGetWidthMin;
extern LibTiePieGenGetWidthMax_t GenGetWidthMax;
extern LibTiePieGenGetWidthMinMaxEx_t GenGetWidthMinMaxEx;
extern LibTiePieGenGetWidth_t GenGetWidth;
extern LibTiePieGenSetWidth_t GenSetWidth;
extern LibTiePieGenVerifyWidth_t GenVerifyWidth;
extern LibTiePieGenVerifyWidthEx_t GenVerifyWidthEx;
extern LibTiePieGenHasEdgeTime_t GenHasEdgeTime;
extern LibTiePieGenHasEdgeTimeEx_t GenHasEdgeTimeEx;
extern LibTiePieGenGetLeadingEdgeTimeMin_t GenGetLeadingEdgeTimeMin;
extern LibTiePieGenGetLeadingEdgeTimeMax_t GenGetLeadingEdgeTimeMax;
extern LibTiePieGenGetLeadingEdgeTimeMinMaxEx_t GenGetLeadingEdgeTimeMinMaxEx;
extern LibTiePieGenGetLeadingEdgeTime_t GenGetLeadingEdgeTime;
extern LibTiePieGenSetLeadingEdgeTime_t GenSetLeadingEdgeTime;
extern LibTiePieGenVerifyLeadingEdgeTime_t GenVerifyLeadingEdgeTime;
extern LibTiePieGenVerifyLeadingEdgeTimeEx_t GenVerifyLeadingEdgeTimeEx;
extern LibTiePieGenGetTrailingEdgeTimeMin_t GenGetTrailingEdgeTimeMin;
extern LibTiePieGenGetTrailingEdgeTimeMax_t GenGetTrailingEdgeTimeMax;
extern LibTiePieGenGetTrailingEdgeTimeMinMaxEx_t GenGetTrailingEdgeTimeMinMaxEx;
extern LibTiePieGenGetTrailingEdgeTime_t GenGetTrailingEdgeTime;
extern LibTiePieGenSetTrailingEdgeTime_t GenSetTrailingEdgeTime;
extern LibTiePieGenVerifyTrailingEdgeTime_t GenVerifyTrailingEdgeTime;
extern LibTiePieGenVerifyTrailingEdgeTimeEx_t GenVerifyTrailingEdgeTimeEx;
extern LibTiePieGenHasData_t GenHasData;
extern LibTiePieGenHasDataEx_t GenHasDataEx;
extern LibTiePieGenGetDataLengthMin_t GenGetDataLengthMin;
extern LibTiePieGenGetDataLengthMax_t GenGetDataLengthMax;
extern LibTiePieGenGetDataLengthMinMaxEx_t GenGetDataLengthMinMaxEx;
extern LibTiePieGenGetDataLength_t GenGetDataLength;
extern LibTiePieGenVerifyDataLength_t GenVerifyDataLength;
extern LibTiePieGenVerifyDataLengthEx_t GenVerifyDataLengthEx;
extern LibTiePieGenSetData_t GenSetData;
extern LibTiePieGenSetDataEx_t GenSetDataEx;
extern LibTiePieGenGetDataRawType_t GenGetDataRawType;
extern LibTiePieGenGetDataRawValueRange_t GenGetDataRawValueRange;
extern LibTiePieGenGetDataRawValueMin_t GenGetDataRawValueMin;
extern LibTiePieGenGetDataRawValueZero_t GenGetDataRawValueZero;
extern LibTiePieGenGetDataRawValueMax_t GenGetDataRawValueMax;
extern LibTiePieGenSetDataRaw_t GenSetDataRaw;
extern LibTiePieGenSetDataRawEx_t GenSetDataRawEx;
extern LibTiePieGenGetModes_t GenGetModes;
extern LibTiePieGenGetModesEx_t GenGetModesEx;
extern LibTiePieGenGetModesNative_t GenGetModesNative;
extern LibTiePieGenGetMode_t GenGetMode;
extern LibTiePieGenSetMode_t GenSetMode;
extern LibTiePieGenIsBurstActive_t GenIsBurstActive;
extern LibTiePieGenGetBurstCountMin_t GenGetBurstCountMin;
extern LibTiePieGenGetBurstCountMax_t GenGetBurstCountMax;
extern LibTiePieGenGetBurstCountMinMaxEx_t GenGetBurstCountMinMaxEx;
extern LibTiePieGenGetBurstCount_t GenGetBurstCount;
extern LibTiePieGenSetBurstCount_t GenSetBurstCount;
extern LibTiePieGenGetBurstSampleCountMin_t GenGetBurstSampleCountMin;
extern LibTiePieGenGetBurstSampleCountMax_t GenGetBurstSampleCountMax;
extern LibTiePieGenGetBurstSampleCountMinMaxEx_t GenGetBurstSampleCountMinMaxEx;
extern LibTiePieGenGetBurstSampleCount_t GenGetBurstSampleCount;
extern LibTiePieGenSetBurstSampleCount_t GenSetBurstSampleCount;
extern LibTiePieGenGetBurstSegmentCountMin_t GenGetBurstSegmentCountMin;
extern LibTiePieGenGetBurstSegmentCountMax_t GenGetBurstSegmentCountMax;
extern LibTiePieGenGetBurstSegmentCountMinMaxEx_t GenGetBurstSegmentCountMinMaxEx;
extern LibTiePieGenGetBurstSegmentCount_t GenGetBurstSegmentCount;
extern LibTiePieGenSetBurstSegmentCount_t GenSetBurstSegmentCount;
extern LibTiePieGenVerifyBurstSegmentCount_t GenVerifyBurstSegmentCount;
extern LibTiePieGenVerifyBurstSegmentCountEx_t GenVerifyBurstSegmentCountEx;
extern LibTiePieGenSetCallbackBurstCompleted_t GenSetCallbackBurstCompleted;
#ifdef LIBTIEPIE_LINUX
extern LibTiePieGenSetEventBurstCompleted_t GenSetEventBurstCompleted;
#endif
#ifdef LIBTIEPIE_WINDOWS
extern LibTiePieGenSetEventBurstCompleted_t GenSetEventBurstCompleted;
extern LibTiePieGenSetMessageBurstCompleted_t GenSetMessageBurstCompleted;
#endif
extern LibTiePieGenSetCallbackControllableChanged_t GenSetCallbackControllableChanged;
#ifdef LIBTIEPIE_LINUX
extern LibTiePieGenSetEventControllableChanged_t GenSetEventControllableChanged;
#endif
#ifdef LIBTIEPIE_WINDOWS
extern LibTiePieGenSetEventControllableChanged_t GenSetEventControllableChanged;
extern LibTiePieGenSetMessageControllableChanged_t GenSetMessageControllableChanged;
#endif
extern LibTiePieI2CIsInternalAddress_t I2CIsInternalAddress;
extern LibTiePieI2CGetInternalAddresses_t I2CGetInternalAddresses;
extern LibTiePieI2CRead_t I2CRead;
extern LibTiePieI2CReadByte_t I2CReadByte;
extern LibTiePieI2CReadWord_t I2CReadWord;
extern LibTiePieI2CWrite_t I2CWrite;
extern LibTiePieI2CWriteByte_t I2CWriteByte;
extern LibTiePieI2CWriteByteByte_t I2CWriteByteByte;
extern LibTiePieI2CWriteByteWord_t I2CWriteByteWord;
extern LibTiePieI2CWriteWord_t I2CWriteWord;
extern LibTiePieI2CWriteRead_t I2CWriteRead;
extern LibTiePieI2CGetSpeedMax_t I2CGetSpeedMax;
extern LibTiePieI2CGetSpeed_t I2CGetSpeed;
extern LibTiePieI2CSetSpeed_t I2CSetSpeed;
extern LibTiePieI2CVerifySpeed_t I2CVerifySpeed;
extern LibTiePieSrvConnect_t SrvConnect;
extern LibTiePieSrvDisconnect_t SrvDisconnect;
extern LibTiePieSrvRemove_t SrvRemove;
extern LibTiePieSrvGetStatus_t SrvGetStatus;
extern LibTiePieSrvGetLastError_t SrvGetLastError;
extern LibTiePieSrvGetURL_t SrvGetURL;
extern LibTiePieSrvGetID_t SrvGetID;
extern LibTiePieSrvGetIPv4Address_t SrvGetIPv4Address;
extern LibTiePieSrvGetIPPort_t SrvGetIPPort;
extern LibTiePieSrvGetName_t SrvGetName;
extern LibTiePieSrvGetDescription_t SrvGetDescription;
extern LibTiePieSrvGetVersion_t SrvGetVersion;
extern LibTiePieSrvGetVersionExtra_t SrvGetVersionExtra;
extern LibTiePieHlpPointerArrayNew_t HlpPointerArrayNew;
extern LibTiePieHlpPointerArraySet_t HlpPointerArraySet;
extern LibTiePieHlpPointerArrayDelete_t HlpPointerArrayDelete;

LibTiePieStatus_t LibTiePieLoad( const char* pLibrary );
LibTiePieStatus_t LibTiePieUnload();

#endif
