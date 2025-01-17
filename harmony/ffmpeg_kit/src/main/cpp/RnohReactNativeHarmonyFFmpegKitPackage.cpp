#pragma once
#include "RnohReactNativeHarmonyFFmpegKitPackage.h"
#include "RNOH/ArkTSTurboModule.h"
#include "RNFFmpegKitModule.h"
#include <glog/logging.h>
#include <react/renderer/debug/SystraceSection.h>

using namespace rnoh;
using namespace facebook;

class FFmpegKitTurboModuleFactoryDelegate : public TurboModuleFactoryDelegate {
public:
    SharedTurboModule createTurboModule(Context ctx, const std::string &name) const override {
        if (name == "NativeRNFFmpegKitModule") {
            return std::make_shared<RNFFmpegKitModule>(ctx, name);
        }
        return nullptr;
    };
};

std::unique_ptr<TurboModuleFactoryDelegate> RnohReactNativeHarmonyFFmpegKitPackage::createTurboModuleFactoryDelegate() {
    return std::make_unique<FFmpegKitTurboModuleFactoryDelegate>();
}


class FFmpegKitEventEmitRequestHandler : public EventEmitRequestHandler {
    void handleEvent(EventEmitRequestHandler::Context const &ctx) override {
        facebook::react::SystraceSection s("RNGH::FFmpegKitEventEmitRequestHandler::handleEvent");
        auto eventEmitter = ctx.shadowViewRegistry->getEventEmitter<facebook::react::ViewEventEmitter>(ctx.tag);
        if (eventEmitter == nullptr) {
            return;
        }
    }
};

EventEmitRequestHandlers RnohReactNativeHarmonyFFmpegKitPackage::createEventEmitRequestHandlers() {
    return {
        std::make_shared<FFmpegKitEventEmitRequestHandler>(),
    };
}