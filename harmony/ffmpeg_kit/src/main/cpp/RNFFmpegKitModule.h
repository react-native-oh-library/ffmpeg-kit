
#pragma once

// This file was generated.

#include "RNOH/ArkTSTurboModule.h"
#include "FFmpegSession.h"
#include "Session.h"
#include "Statistics.h"
#include "rapidjson/document.h"



namespace rnoh {

class JSI_EXPORT RNFFmpegKitModule : public ArkTSTurboModule {
  public:

    bool logsEnabled = false;
    bool statisticsEnabled = false;

    RNFFmpegKitModule(const ArkTSTurboModule::Context ctx, const std::string name);
    facebook::jsi::Object statisticsToMap(facebook::jsi::Runtime &runtime, const std::shared_ptr<ffmpegkit::Statistics> &statistics);
    facebook::jsi::Object logToMap(facebook::jsi::Runtime &runtime, const std::shared_ptr<ffmpegkit::Log> &log);
    facebook::jsi::Object toMap(facebook::jsi::Runtime &runtime, std::shared_ptr<ffmpegkit::Session> session);
    facebook::jsi::Value medInfoToMap(facebook::jsi::Runtime &rt, const rapidjson::Value &jsonValue);
    void registerGlobalCallbacks(facebook::jsi::Runtime &rt);
    void globalLogCallback(facebook::jsi::Runtime &runtime,std::shared_ptr<ffmpegkit::Session> &session);
    void statisticsCallback(facebook::jsi::Runtime &runtime,std::shared_ptr<ffmpegkit::FFmpegSession> &session);
    void enableLogs();
    void disableLogs();
    void enableStatistics();
    void disableStatistics();
    ffmpegkit::SessionState toSessionState(const int value);
};

} // namespace rnoh
