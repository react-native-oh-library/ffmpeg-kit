/**
 * GUN License
 *
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once
#include "RnohReactNativeHarmonyFFmpegKitPackage.h"
#include "RNOH/ArkTSTurboModule.h"
#include "RNFFmpegKitModule.h"
#include <glog/logging.h>

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
        facebook::react::TraceSection s("RNGH::FFmpegKitEventEmitRequestHandler::handleEvent");
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