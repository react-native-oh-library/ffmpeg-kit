
#pragma once

// This file was generated.

#include "RNOH/ArkTSTurboModule.h"
#include "Session.h"

namespace rnoh {


class JSI_EXPORT RNFFmpegKitModule : public ArkTSTurboModule {
  public:
    RNFFmpegKitModule(const ArkTSTurboModule::Context ctx, const std::string name);
    facebook::jsi::Object toMap(facebook::jsi::Runtime &rt, std::shared_ptr<ffmpegkit::Session> &session);
};

} // namespace rnoh
