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
    Context getContext()
    {
      return m_ctx;
    }

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
