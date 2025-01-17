#pragma once
#include "RNOH/Package.h"

namespace rnoh {
class RnohReactNativeHarmonyFFmpegKitPackage : public Package {
public:
    RnohReactNativeHarmonyFFmpegKitPackage(Package::Context ctx) : Package(ctx) {}
    
    std::unique_ptr<TurboModuleFactoryDelegate> createTurboModuleFactoryDelegate() override;
    
    EventEmitRequestHandlers createEventEmitRequestHandlers() override;
};
} // namespace rnoh
