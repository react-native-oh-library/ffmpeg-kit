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

#include "RNFFmpegKitModule.h"
#include "FFmpegKit.h"
#include "FFprobeKit.h"
#include "FFmpegKitConfig.h"
#include "FFmpegSession.h"
#include "Session.h"
#include "SessionState.h"
#include "Signal.h"
#include <cstddef>
#include <cstdint>
#include <hermes/hermes.h>

namespace rnoh {
using namespace facebook;

//=============================================== JSI对外接口 start ===============================================//

/**
 * ffmpegSessionExecute：同步执行命令
 *
 * @param rt
 * @param turboModule
 * @param args
 * @param count
 * @return
 */
jsi::Value ffmpegSessionExecute(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                const facebook::jsi::Value *args, size_t count) {

    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (args[0].isNull() || args[0].isUndefined()) {
                promise->reject("[ffmpegSessionExecute]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session->isFFmpeg()) {
                auto ffmpegSession = std::dynamic_pointer_cast<ffmpegkit::FFmpegSession>(session);
                ffmpegkit::FFmpegKitConfig::ffmpegExecute(ffmpegSession);

                promise->resolve(jsi::Value::null());
            } else {
                promise->reject("NOT_FFMPEG_SESSION: A session is found but it does not have the correct type.");
            }
        });
}

jsi::Value asyncFFmpegSessionExecute(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                     const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &count, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (count > 0 && !args[0].isNumber()) {
                promise->reject("[asyncFFmpegSessionExecute]INVALID_SESSION: Invalid session id.");
                return;
            }
            auto session = ffmpegkit::FFmpegKitConfig::getSession(args[0].getNumber());
            if (!session->isFFmpeg()) {
                promise->reject("NOT_FFMPEG_SESSION: A session is found but it does not have the correct type.");
                return;
            }

            auto ffmpegSession = std::dynamic_pointer_cast<ffmpegkit::FFmpegSession>(session);
            ffmpegkit::FFmpegKitConfig::asyncFFmpegExecute(ffmpegSession);
            promise->resolve(jsi::Value::null());
        });
}


/**
 * ffmpegSession： 创建 ffmpegSession
 *
 * @param rt
 * @param turboModule
 * @param args
 * @param count
 * @return
 */
jsi::Value ffmpegSession(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                         size_t count) {
    return facebook::react::createPromiseAsJSIValue(rt, [&turboModule,
                                                         args](jsi::Runtime &runtime,
                                                               std::shared_ptr<facebook::react::Promise> promise) {
        std::list<std::string> arguments;

        if (!args[0].isObject()) {
            promise->reject("Parameter exception.");
            return;
        }
        
        auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
        
        jsi::Array arrayArgument = args[0].asObject(runtime).getArray(runtime);
        std::string strTemp;
        for (int32_t i = 0; i < arrayArgument.size(runtime); i++) {
            jsi::Value value = args[0].asObject(runtime).getArray(runtime).getValueAtIndex(runtime, i);
            if (value.isString()) {
                strTemp = value.getString(runtime).utf8(runtime);
                arguments.push_back(strTemp);
            }
        }
        
        std::shared_ptr<ffmpegkit::FFmpegSession> fFmpegSession =
            ffmpegkit::FFmpegSession::create(arguments, nullptr, nullptr, nullptr,
                                             ffmpegkit::LogRedirectionStrategy::LogRedirectionStrategyNeverPrintLogs);
        
        std::shared_ptr<ffmpegkit::Session> session = std::static_pointer_cast<ffmpegkit::Session>(fFmpegSession);
        promise->resolve(jsi::Value(runtime,self->toMap(runtime, session)));
    });
}

jsi::Value ffprobeSession(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                         size_t count) {
    return facebook::react::createPromiseAsJSIValue(rt, [&turboModule,
                                                         args](jsi::Runtime &runtime,
                                                               std::shared_ptr<facebook::react::Promise> promise) {
        
        std::list<std::string> arguments;

        if (!args[0].isObject()) {
            promise->reject("Parameter exception.");
            return;
        }
        
        auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
        
        jsi::Array arrayArgument = args[0].asObject(runtime).getArray(runtime);
        std::string strTemp;
        for (int32_t i = 0; i < arrayArgument.size(runtime); i++) {
            jsi::Value value = args[0].asObject(runtime).getArray(runtime).getValueAtIndex(runtime, i);
            if (value.isString()) {
                strTemp = value.getString(runtime).utf8(runtime);
                arguments.push_back(strTemp);
            }
        }
        
        std::shared_ptr<ffmpegkit::FFprobeSession> fFprobeSession =
            ffmpegkit::FFprobeSession::create(arguments, nullptr, nullptr,
                                             ffmpegkit::LogRedirectionStrategy::LogRedirectionStrategyNeverPrintLogs);
        
        std::shared_ptr<ffmpegkit::Session> session = std::static_pointer_cast<ffmpegkit::Session>(fFprobeSession);
        if(session){
            promise->resolve(jsi::Value(runtime, self->toMap(runtime, session)));
        } else {
            promise->reject("FFprobeSession exception.");
        }
    });
}

jsi::Value ffprobeSessionExecute(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                const facebook::jsi::Value *args, size_t count) {

    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[ffprobeSessionExecute]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].getNumber());
            if (session->isFFprobe()) {
                ffmpegkit::FFmpegKitConfig::ffprobeExecute(std::dynamic_pointer_cast<ffmpegkit::FFprobeSession>(session));
                promise->resolve(jsi::Value::null());
            } else {
                promise->reject("NOT_FFPROBE_SESSION: A session is found but it does not have the correct type.");
            }
        });
}

jsi::Value asyncFFprobeSessionExecute(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                const facebook::jsi::Value *args, size_t count) {
    
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
        
            if (!args[0].isNumber()) {
                promise->reject("[asyncFFprobeSessionExecute]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session =
                ffmpegkit::FFmpegKitConfig::getSession(static_cast<long>(args[0].asNumber()));
        
            if(!session){
                promise->reject("SESSION_NOT_FOUND: Session not found.");
                return;
            }
            
            if (session->isFFprobe()) {
                auto ffprobeSession = std::dynamic_pointer_cast<ffmpegkit::FFprobeSession>(session);
                ffmpegkit::FFmpegKitConfig::asyncFFprobeExecute(ffprobeSession);
            
                promise->resolve(jsi::Value::null());
            } else {
                promise->reject("NOT_FFPROBE_SESSION: A session is found but it does not have the correct type.");
            }
        });
}

jsi::Value mediaInformationSessionExecute(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                const facebook::jsi::Value *args, size_t count) {

    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[mediaInformationSessionExecute]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session =
                ffmpegkit::FFmpegKitConfig::getSession(static_cast<long>(args[0].getNumber()));
        
            if(!session){
                promise->reject("[mediaInformationSessionExecute]SESSION_NOT_FOUND: Session not found.");
                return;
            }
        
            if (!args[1].isNumber()) {
                promise->reject("[mediaInformationSessionExecute]The second parameter is invalid waitTimeout.");
                return;
            }
        
            if (session->isMediaInformation()) {
                int waitTimeout = static_cast<int>(args[1].getNumber());
                if (waitTimeout < 0) {
                    waitTimeout = ffmpegkit::AbstractSession::DefaultTimeoutForAsynchronousMessagesInTransmit;
                }
            
                auto mediaInformationSession = std::dynamic_pointer_cast<ffmpegkit::MediaInformationSession>(session);
                ffmpegkit::FFmpegKitConfig::getMediaInformationExecute(mediaInformationSession, waitTimeout);

                // 以下返回log处理
                ffmpegkit::MediaInformationSessionCompleteCallback completeCallback = mediaInformationSession->getCompleteCallback();
                if (completeCallback != nullptr) {
                    try {
                        // NOTIFY SESSION CALLBACK DEFINED
                        completeCallback(mediaInformationSession);
                    } catch(const std::exception& exception) {
                        std::cout << "Exception thrown inside session complete callback. " << exception.what() << std::endl;
                    }
                }
                ffmpegkit::MediaInformationSessionCompleteCallback globalMediaInformationSessionCompleteCallback = ffmpegkit::FFmpegKitConfig::getMediaInformationSessionCompleteCallback();
                if (globalMediaInformationSessionCompleteCallback != nullptr) {
                    try {
                        // NOTIFY SESSION CALLBACK DEFINED
                        globalMediaInformationSessionCompleteCallback(mediaInformationSession);
                    } catch(const std::exception& exception) {
                        std::cout << "Exception thrown inside global complete callback. " << exception.what() << std::endl;
                    }
                }
            
                promise->resolve(jsi::Value::null());
            } else {
                promise->reject("NOT_MEDIA_INFORMATION_SESSION: A session is found but it does not have the correct type.");
            }
        });
}

jsi::Value asyncMediaInformationSessionExecute(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                const facebook::jsi::Value *args, size_t count) {

    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[asyncMediaInformationSessionExecute]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session =
                ffmpegkit::FFmpegKitConfig::getSession(static_cast<long>(args[0].getNumber()));
        
            if(!session){
                promise->reject("SESSION_NOT_FOUND: Session not found.");
                return;
            }
        
            if (!args[1].isNumber()) {
                promise->reject("[asyncMediaInformationSessionExecute]The second parameter is invalid waitTimeout.");
                return;
            }
        
            if (session->isMediaInformation()) {
                int waitTimeout = static_cast<int>(args[1].getNumber());
                if (waitTimeout < 0) {
                    waitTimeout = ffmpegkit::AbstractSession::DefaultTimeoutForAsynchronousMessagesInTransmit;
                }
            
                auto mediaInformationSession =  std::dynamic_pointer_cast<ffmpegkit::MediaInformationSession>(session);
                ffmpegkit::FFmpegKitConfig::asyncGetMediaInformationExecute(mediaInformationSession,waitTimeout);
            
                promise->resolve(jsi::Value::null());
            } else {
                promise->reject("NOT_MEDIA_INFORMATION_SESSION: A session is found but it does not have the correct type.");
            }
        });
}

jsi::Value mediaInformationSession(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                         size_t count) {
    return facebook::react::createPromiseAsJSIValue(rt, [&turboModule,
                                                         args](jsi::Runtime &runtime,
                                                               std::shared_ptr<facebook::react::Promise> promise) {
        std::list<std::string> arguments;

        if (!args[0].isObject()) {
            promise->reject("Parameter exception.");
            return;
        }
        
        auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
        
        jsi::Array arrayArgument = args[0].asObject(runtime).getArray(runtime);
        std::string strTemp;
        for (int32_t i = 0; i < arrayArgument.size(runtime); i++) {
            jsi::Value value = args[0].asObject(runtime).getArray(runtime).getValueAtIndex(runtime, i);
            if (value.isString()) {
                strTemp = value.getString(runtime).utf8(runtime);
                arguments.push_back(strTemp);
            }
        }
        
        std::shared_ptr<ffmpegkit::MediaInformationSession> medInfoSession = ffmpegkit::MediaInformationSession::create(arguments, nullptr, nullptr);
        
        std::shared_ptr<ffmpegkit::Session> session = std::dynamic_pointer_cast<ffmpegkit::Session>(medInfoSession);
        promise->resolve(jsi::Value(runtime, self->toMap(runtime, session)));
    });
}

/**
 * getLogLevel 获取当前日志级别 (已完成)
 *
 * @param rt
 * @param turboModule
 * @param args
 * @param count
 * @return
 */
jsi::Value getLogLevel(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                       size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            int level = ffmpegkit::FFmpegKitConfig::getLogLevel();
            promise->resolve(jsi::Value(level));
        });
}

jsi::Value setLogLevel(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                       size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("INVALID_LEVEL: Invalid level value.");
                return;
            }
            ffmpegkit::Level lever = static_cast<ffmpegkit::Level>(args[0].getNumber());
            ffmpegkit::FFmpegKitConfig::setLogLevel(lever);
            promise->resolve(jsi::Value::null());
        });
}

/**
 * getPlatform 获取当前平台 (已完成)
 *
 * @param rt
 * @param turboModule
 * @param args
 * @param count
 * @return
 */
jsi::Value getPlatform(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                       size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            promise->resolve(jsi::String::createFromUtf8(runtime, "OHOS"));
        });
}

jsi::Value cancel(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                  size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            ffmpegkit::FFmpegKit::cancel();
            promise->resolve(jsi::Value().null());
        });
}

jsi::Value cancelSession(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                         size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &count](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (count <= 0 || !args[0].isNumber()) {
                promise->reject("[cancelSession]INVALID_SESSION: Invalid session id.");
                return;
            }

            if (count > 0 && args[0].isNumber()) {
                ffmpegkit::FFmpegKit::cancel(args[0].getNumber());
                promise->resolve(jsi::Value().null());
            }
        });
}

jsi::Value clearSessions(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                         size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            ffmpegkit::FFmpegKitConfig::clearSessions();
            promise->resolve(jsi::Value().null());
        });
}

jsi::Value ignoreSignal(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                        size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &count](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("INVALID_SIGNAL: Signal value not supported.");
                return;
            }
            if (args[0].getNumber() == static_cast<double>(ffmpegkit::Signal::SignalInt)) {
                ffmpegkit::FFmpegKitConfig::ignoreSignal(ffmpegkit::Signal::SignalInt);
            } else if (args[0].getNumber() == static_cast<double>(ffmpegkit::Signal::SignalQuit)) {
                ffmpegkit::FFmpegKitConfig::ignoreSignal(ffmpegkit::Signal::SignalQuit);
            } else if (args[0].getNumber() == static_cast<double>(ffmpegkit::Signal::SignalTerm)) {
                ffmpegkit::FFmpegKitConfig::ignoreSignal(ffmpegkit::Signal::SignalTerm);
            } else if (args[0].getNumber() == static_cast<double>(ffmpegkit::Signal::SignalXcpu)) {
                ffmpegkit::FFmpegKitConfig::ignoreSignal(ffmpegkit::Signal::SignalXcpu);
            } else if (args[0].getNumber() == static_cast<double>(ffmpegkit::Signal::SignalPipe)) {
                ffmpegkit::FFmpegKitConfig::ignoreSignal(ffmpegkit::Signal::SignalPipe);
            }
            promise->resolve(jsi::Value().null());
        });
}


jsi::Value getSession(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                      size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[getSession]INVALID_SESSION: Invalid session id.");
                return;
            }
            auto session = ffmpegkit::FFmpegKitConfig::getSession(args[0].getNumber());
            if (!session) {
                promise->reject("SESSION_NOT_FOUND: Session not found.");
            } else {
                auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
                promise->resolve(jsi::Value(runtime,self->toMap(runtime, session)));
            }
        });
}

jsi::Value getLastSession(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                      size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            
            auto session = ffmpegkit::FFmpegKitConfig::getLastSession();
            if (!session) {
                promise->reject("SESSION_NOT_FOUND: Session not found.");
            } else {
                auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
                
                promise->resolve(jsi::Value(runtime, self->toMap(runtime, session)));
            }
        });
}

jsi::Value getLastCompletedSession(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                      size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            
            auto session = ffmpegkit::FFmpegKitConfig::getLastCompletedSession();
            if (!session) {
                promise->reject("SESSION_NOT_FOUND: Session not found.");
            } else {
                auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
                
                promise->resolve(jsi::Value(runtime, self->toMap(runtime, session)));
            }
        });
}

jsi::Value getSessions(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                       size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::Session>>> listPtr =
                ffmpegkit::FFmpegKitConfig::getSessions();


            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            

            jsi::Array jsArray(runtime, listPtr->size());
            size_t index = 0;
            if (listPtr && !listPtr->empty()) {
                for (auto &sessionPtr : *listPtr) {
                    if (sessionPtr) {
                        jsArray.setValueAtIndex(runtime, index, jsi::Value(runtime, self->toMap(runtime, sessionPtr)));
                    }
                    ++index;
                }
            }
            promise->resolve(jsi::Value(runtime, jsArray));
        });
}

/**
 * getArch 获取 ABI 架构 (已完成)
 *
 * @param rt
 * @param turboModule
 * @param args
 * @param count
 * @return
 */
jsi::Value getArch(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                   size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            promise->resolve(jsi::String::createFromUtf8(runtime, "arm64-v8a"));
        });
}

/**
 * getPackageName (简易化已完成)
 *
 * @param rt
 * @param turboModule
 * @param args
 * @param count
 * @return
 */
jsi::Value getPackageName(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                          size_t count) {
    std::string packageName = "custom";
    return facebook::react::createPromiseAsJSIValue(
        rt, [packageName](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            promise->resolve(jsi::String::createFromUtf8(runtime, packageName));
        });
}

jsi::Value getExternalLibraries(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(rt, [](jsi::Runtime &runtime,
                                                           std::shared_ptr<facebook::react::Promise> promise) {
            std::string libs[] = {
                "dav1d",    "FFmpeg",   "lame",    "libogg",     "libvorbis",    "libvpx",     "openmp",   "rapidjson",
                "vid.stab", "x264",     "x265",    "xvidcore",   "libass",        "libunibreak", "freetype2", "brotli",
                "fribidi",  "harfbuzz", "libpng",  "fontconfig", "libxml2",       "xz",          "json-c",    "glib",
                "nettle",   "gmp",      "libidn2", "libtasn1",   "gnutls",        "chromaprint", "openh264",  "opus",
                "speex",    "libwebp",  "zstd",    "jbigkit",    "libjpeg-turbo", "libdeflate",  "tiff"};

            size_t length = std::size(libs);
            jsi::Array libArray(runtime, length);

            for (int i = 0; i < length; ++i) {
                libArray.setValueAtIndex(runtime, i, libs[i]);
            }

            promise->resolve(jsi::Value(runtime, libArray));
        });
}

/**
 * enableRedirection：开启日志和统计重定向 (已完成)
 *
 * @param rt
 * @param turboModule
 * @param args
 * @param count
 * @return
 */
jsi::Value enableRedirection(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            ffmpegkit::FFmpegKitConfig::enableRedirection();
            promise->resolve(jsi::Value::null());
        });
}

/**
 * isLTSBuild (已完成)
 *
 * @param rt
 * @param turboModule
 * @param args
 * @param count
 * @return
 */
jsi::Value isLTSBuild(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args,
                      size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            bool isLTSBuild = ffmpegkit::FFmpegKitConfig::isLTSBuild();
            promise->resolve(jsi::Value(isLTSBuild));
        });
}

jsi::Value ffmpegSessionGetAllStatistics(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                const facebook::jsi::Value *args, size_t count) {

    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[ffmpegSessionGetAllStatistics]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session =
                ffmpegkit::FFmpegKitConfig::getSession(static_cast<long>(args[0].getNumber()));
        
            if(!session){
                promise->reject("[ffmpegSessionGetAllStatistics]SESSION_NOT_FOUND: Session not found.");
                return;
            }
        
            if (!args[1].isNumber()) {
                promise->reject("[ffmpegSessionGetAllStatistics]The second parameter is invalid waitTimeout.");
                return;
            }
        
            if (session->isFFmpeg()) {
                int waitTimeout = static_cast<int>(args[1].getNumber());
                if (waitTimeout < 0) {
                    waitTimeout = ffmpegkit::AbstractSession::DefaultTimeoutForAsynchronousMessagesInTransmit;
                }
                
                std::shared_ptr<ffmpegkit::FFmpegSession> ffmpegSession = std::dynamic_pointer_cast<ffmpegkit::FFmpegSession>(session);
                std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::Statistics>>> listPtr = ffmpegSession->getAllStatisticsWithTimeout(waitTimeout);
            
                auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            
                jsi::Array statisticsArray(runtime, listPtr->size());
                size_t index = 0;
                if (listPtr && !listPtr->empty()) {
                    for (const auto& statPtr : *listPtr) {
                        if (statPtr) {
                            statisticsArray.setValueAtIndex(runtime, index, self->statisticsToMap(runtime, statPtr));
                        }
                        ++index;
                    }
                }
               promise->resolve(jsi::Value(runtime, statisticsArray));
            } else {
                promise->reject("NOT_FFMPEG_SESSION: A session is found but it does not have the correct type.");
            }
        });
}

jsi::Value ffmpegSessionGetStatistics(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                const facebook::jsi::Value *args, size_t count) {

    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[ffmpegSessionGetStatistics]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session =
                ffmpegkit::FFmpegKitConfig::getSession(static_cast<long>(args[0].getNumber()));
        
            if(!session){
                promise->reject("[ffmpegSessionGetStatistics]SESSION_NOT_FOUND: Session not found.");
                return;
            }
        
        
            if (session->isFFmpeg()) {
                std::shared_ptr<ffmpegkit::FFmpegSession> ffmpegSession = std::dynamic_pointer_cast<ffmpegkit::FFmpegSession>(session);
                std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::Statistics>>> listPtr = ffmpegSession->getStatistics();
            
                auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
                
            
                jsi::Array statisticsArray(runtime, listPtr->size());
                size_t index = 0;
                if (listPtr && !listPtr->empty()) {
                    for (const auto& statPtr : *listPtr) {
                        if (statPtr) {
                            statisticsArray.setValueAtIndex(runtime, index, self->statisticsToMap(runtime, statPtr));
                        }
                        ++index;
                    }
                }
                promise->resolve(jsi::Value(runtime,statisticsArray));
            } else {
                promise->reject("NOT_FFMPEG_SESSION: A session is found but it does not have the correct type.");
            }
        });
}

jsi::Value abstractSessionGetState(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                   const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (args[0].isNull() || args[0].isUndefined()) {
                promise->reject("[abstractSessionGetState]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session) {
                promise->resolve(jsi::Value(static_cast<int>(session->getState())));
            } else {
                promise->reject("[abstractSessionGetState]SESSION_NOT_FOUND: Session not found.");
                DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
            }
        });
}

jsi::Value abstractSessionGetReturnCode(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                        const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[abstractSessionGetReturnCode]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session) {
                std::shared_ptr<ffmpegkit::ReturnCode> returnCode = session->getReturnCode();
                if (returnCode) {
                    promise->resolve(jsi::Value(returnCode->getValue()));
                } else {
                    promise->resolve(jsi::Value::undefined());
                }
            } else {
                promise->reject("[abstractSessionGetReturnCode]SESSION_NOT_FOUND: Session not found.");
                DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
            }
        });
}

jsi::Value abstractSessionGetFailStackTrace(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                            const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (args[0].isNull() || args[0].isUndefined()) {
                promise->reject("[abstractSessionGetFailStackTrace]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session) {
                promise->resolve(jsi::String::createFromUtf8(runtime, session->getFailStackTrace()));
            } else {
                promise->reject("[abstractSessionGetFailStackTrace]SESSION_NOT_FOUND: Session not found.");
                DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
            }
        });
}

jsi::Value abstractSessionGetAllLogsAsString(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[abstractSessionGetAllLogsAsString]INVALID_SESSION: Invalid session id.");
                return;
            }

            if (!args[1].isNumber()) {
                promise->reject("[abstractSessionGetAllLogsAsString]The second parameter is invalid waitTimeout.");
                return;
            }

            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (!session) {
                promise->reject("[abstractSessionGetAllLogsAsString]SESSION_NOT_FOUND: Session not found.");
                DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
                return;
            }

            int waitTimeout = args[1].asNumber();
            if (waitTimeout < 0) {
                waitTimeout = ffmpegkit::AbstractSession::DefaultTimeoutForAsynchronousMessagesInTransmit;
            }
            
            promise->resolve(jsi::String::createFromUtf8(runtime, session->getAllLogsAsStringWithTimeout(waitTimeout)));
        });
}

jsi::Value abstractSessionGetAllLogs(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                     const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(rt, [&args, &turboModule](jsi::Runtime &runtime,
                                                                std::shared_ptr<facebook::react::Promise> promise) {
        if (!args[0].isNumber()) {
            promise->reject("[abstractSessionGetAllLogs]INVALID_SESSION: Invalid session id.");
            return;
        }

        if (!args[1].isNumber()) {
            promise->reject("[abstractSessionGetAllLogs]The second parameter is invalid waitTimeout.");
            return;
        }

        std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
        if (!session) {
            promise->reject("[abstractSessionGetAllLogs]SESSION_NOT_FOUND: Session not found.");
            DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
            return;
        }

        int waitTimeout = args[1].asNumber();
        if (waitTimeout < 0) {
            waitTimeout = ffmpegkit::AbstractSession::DefaultTimeoutForAsynchronousMessagesInTransmit;
        }

        std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::Log>>> listPtr = session->getAllLogsWithTimeout(waitTimeout);
        int32_t length = listPtr->size();
        
        auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
        
        
        jsi::Array jsArray(runtime, length);

        size_t index = 0;
        if (listPtr && !listPtr->empty()) {
            for (const auto &logPtr : *listPtr) {
                if (logPtr) {
                    jsArray.setValueAtIndex(runtime, index, jsi::Value(runtime, self->logToMap(runtime, logPtr)));
                }
                ++index;
            }
        }
        promise->resolve(jsi::Value(runtime, jsArray));
    });
}

jsi::Value abstractSessionGetLogs(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                  const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (args[0].isNull() || args[0].isUndefined() || !args[0].isNumber()) {
                promise->reject("[abstractSessionGetLogs]INVALID_SESSION: Invalid session id.");
                return;
            }

            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (!session) {
                promise->reject("[abstractSessionGetLogs]SESSION_NOT_FOUND: Session not found.");
                DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
                return;
            }

            std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::Log>>> listPtr = session->getLogs();
            int32_t length = listPtr->size();
        
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            
        
            jsi::Array jsArray(runtime, length);
        
            size_t index = 0;
            if (listPtr && !listPtr->empty()) {
                for (const auto &logPtr : *listPtr) {
                    if (logPtr) {
                        jsArray.setValueAtIndex(runtime, index, jsi::Value(runtime, self->logToMap(runtime, logPtr)));
                    }
                    ++index;
                }
            }
            promise->resolve(jsi::Value(runtime, jsArray));
        });
}

jsi::Value abstractSessionGetEndTime(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                     const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[abstractSessionGetEndTime]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session) {
                auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
                
                 promise->resolve(jsi::Value(runtime,static_cast<int>(session->getEndTime().time_since_epoch().count())));
            } else {
                promise->reject("[abstractSessionGetEndTime]SESSION_NOT_FOUND: Session not found.");
            }
        });
}

jsi::Value abstractSessionGetDuration(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                      const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[abstractSessionGetDuration]INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session) {
                promise->resolve(jsi::Value(static_cast<int>(session->getDuration())));
            } else {
                promise->reject("[abstractSessionGetDuration]SESSION_NOT_FOUND: Session not found.");
            }
        });
}

jsi::Value getFFmpegSessions(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::FFmpegSession>>> listPtr =
                ffmpegkit::FFmpegKit::listSessions();
            int32_t length = listPtr->size();
        
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            
        
            jsi::Array jsArray(runtime, length);
        
            size_t index = 0;
            if (listPtr && !listPtr->empty()) {
                for (auto &sessionPtr : *listPtr) {
                    if (sessionPtr) {
                        auto session = std::dynamic_pointer_cast<ffmpegkit::Session>(sessionPtr);
                        jsArray.setValueAtIndex(runtime, index, jsi::Value(runtime, self->toMap(runtime, session)));
                    }
                    ++index;
                }
            }
            promise->resolve(jsi::Value(runtime, jsArray));
        });
}

jsi::Value disableRedirection(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                              const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            ffmpegkit::FFmpegKitConfig::disableRedirection();
            promise->resolve(jsi::Value().null());
        });
}

jsi::Value setFontconfigConfigurationPath(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                          const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isString()) {
                promise->reject("Invalid path.");
                return;
            }
            int resultCode = ffmpegkit::FFmpegKitConfig::setFontconfigConfigurationPath(args[0].asString(runtime).utf8(runtime));
            if (resultCode == 0) {
                promise->resolve(jsi::String::createFromUtf8(runtime,"Path setting succeeded"));
            } else {
                promise->reject(&"Failed to set the path. The failure code is: " [resultCode]);
            }
        });
}

jsi::Value registerNewFFmpegPipe(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                          const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            std::shared_ptr<std::string> newFFmpegPipe = ffmpegkit::FFmpegKitConfig::registerNewFFmpegPipe();
            promise->resolve(jsi::Value(runtime,jsi::String::createFromUtf8(runtime, newFFmpegPipe->c_str()))); 
        });
}

jsi::Value closeFFmpegPipe(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                          const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isString()) {
                promise->reject("Invalid path.");
                return;
            }
            
            ffmpegkit::FFmpegKitConfig::closeFFmpegPipe(args[0].asString(runtime).utf8(runtime));
            promise->resolve(jsi::Value().null());
        });
}

jsi::Value getFFmpegVersion(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                          const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            std::string ffmpegVersion = ffmpegkit::FFmpegKitConfig::getFFmpegVersion();
            promise->resolve(jsi::String::createFromUtf8(runtime, ffmpegVersion.c_str()));
        });
}

jsi::Value getBuildDate(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                          const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            std::string buildDate = ffmpegkit::FFmpegKitConfig::getBuildDate();
            promise->resolve(jsi::String::createFromUtf8(runtime, buildDate.c_str()));
        });
}

jsi::Value setEnvironmentVariable(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                          const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isString()) {
                promise->reject("Invalid variableName.");
                return;
            }

            if (!args[1].isString()) {
                promise->reject("Invalid variableValue.");
                return;
            }
            
            int resultCode = ffmpegkit::FFmpegKitConfig::setEnvironmentVariable(args[0].asString(runtime).utf8(runtime), args[1].asString(runtime).utf8(runtime));
            if (resultCode == 0) {
                promise->resolve(jsi::Value(runtime, jsi::String::createFromUtf8(runtime, "Environment setting succeeded")));
            } else {
                promise->reject(&"Failed to set the Environment. The failure code is: " [resultCode]);
            }
        });
}

jsi::Value getFFprobeSessions(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::FFprobeSession>>> listPtr =
                ffmpegkit::FFprobeKit::listFFprobeSessions();
            int32_t length = listPtr->size();
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            jsi::Array jsArray(runtime, length);
        
            size_t index = 0;
            if (listPtr && !listPtr->empty()) {
                for (auto &sessionPtr : *listPtr) {
                    if (sessionPtr) {
                        auto session = std::dynamic_pointer_cast<ffmpegkit::Session>(sessionPtr);
                        jsArray.setValueAtIndex(runtime, index, jsi::Value(runtime, self->toMap(runtime, session)));
                    }
                    ++index;
                }
            }
            promise->resolve(jsi::Value(runtime, jsArray));
        });
}

jsi::Value getMediaInformationSessions(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::MediaInformationSession>>> listPtr =
                ffmpegkit::FFprobeKit::listMediaInformationSessions();
        
            int32_t length = listPtr->size();
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            ;
            jsi::Array jsArray(runtime, length);
        
            size_t index = 0;
            if (listPtr && !listPtr->empty()) {
                    for (auto& sessionPtr : *listPtr) {
                        if (sessionPtr) {
                            auto session = std::dynamic_pointer_cast<ffmpegkit::Session>(sessionPtr);
                            jsArray.setValueAtIndex(runtime, index, jsi::Value(runtime, self->toMap(runtime, session)));
                        }
                        ++index;
                    }
                }
            promise->resolve(jsi::Value(runtime, jsArray));
        });
}

jsi::Value getSessionHistorySize(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            promise->resolve(jsi::Value(ffmpegkit::FFmpegKitConfig::getSessionHistorySize()));
        });
}

jsi::Value setSessionHistorySize(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("INVALID_SIZE: Invalid session history size value.");
                return;
            }
            ffmpegkit::FFmpegKitConfig::setSessionHistorySize(static_cast<int>(args[0].asNumber()));
            promise->resolve(jsi::Value().null());
        });
}

jsi::Value messagesInTransmit(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("[abstractSessionGetDuration]INVALID_SESSION: Invalid session id.");
                return;
            }
            promise->resolve(jsi::Value(ffmpegkit::FFmpegKitConfig::messagesInTransmit(static_cast<long>(args[0].asNumber()))));
        });
}

jsi::Value getSessionsByState(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("INVALID_SESSION_STATE: Invalid session state value.");
                return;
            }
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
        
            std::shared_ptr<std::list<std::shared_ptr<ffmpegkit::Session>>> listPtr =
                ffmpegkit::FFmpegKitConfig::getSessionsByState(
                    self->toSessionState(static_cast<int>(args[0].asNumber())));
        
            
            int32_t length = listPtr->size();
            jsi::Array jsArray(runtime, length);
        
            size_t index = 0;
            if (listPtr && !listPtr->empty()) {
                    for (auto& sessionPtr : *listPtr) {
                        if (sessionPtr) {
                            jsArray.setValueAtIndex(runtime, index, jsi::Value(runtime, self->toMap(runtime, sessionPtr)));
                        }
                        ++index;
                    }
                }
            promise->resolve(jsi::Value(runtime, jsArray));
        });
}

jsi::Value getMediaInformation(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("INVALID_SESSION: Session not found.");
                return;
            }
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(static_cast<long>(args[0].getNumber()));
        
            if (!session) {
                promise->reject("SESSION_NOT_FOUND: Session not found.");
                return;
            }

            if (session->isMediaInformation()) {
                auto medSession = std::dynamic_pointer_cast<ffmpegkit::MediaInformationSession>(session);
                auto mediaInformation = medSession->getMediaInformation();
                if (mediaInformation) {
                    std::shared_ptr<rapidjson::Value> allProperties = mediaInformation->getAllProperties();
                    promise->resolve(jsi::Value(runtime, self->medInfoToMap(runtime, *allProperties)));
                } else {
                    promise->resolve(jsi::Value().null());
                }
            } else {
                promise->reject("NOT_MEDIA_INFORMATION_SESSION: A session is found but it does not have the correct type.");
            }
        });
}

jsi::Value mediaInformationJsonParserFrom(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isString()) {
                promise->reject("INVALID_FFPROBEJSONOUTPUT: ffprobeJsonOutput not found.");
                return;
            }
            
            std::shared_ptr<ffmpegkit::MediaInformation> medinfo = ffmpegkit::MediaInformationJsonParser::fromWithError(args[0].asString(runtime).utf8(runtime));
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            std::shared_ptr<rapidjson::Value> allProperties = medinfo->getAllProperties();
            
            promise->resolve(jsi::Value(runtime, self->medInfoToMap(runtime, *allProperties)));
        });
}

jsi::Value setFontDirectory(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule, &count](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (count == 2 && !args[0].isString() && !args[1].isObject()) {
                promise->reject("Parameter exception");
                return;
            }
        
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            
            std::string fontDirectoryPath = args[0].getString(runtime).utf8(runtime);
            
            // 下面是解析 js 端传递进来的 map 数据
            std::map<std::string,std::string> map;
            // 1. 获取 map 所有的 key 数组，通过数组拿到 map 集合的大小
            size_t len = args[1].getObject(runtime).getPropertyNames(runtime).size(runtime);
            // 2. 遍历所有的 key 数组
            for (size_t i = 0; i < len; i++) {
                // 3. 通过索引拿到对应的 key 值
                std::string key = args[1]
                                      .getObject(runtime)
                                      .getPropertyNames(runtime)
                                      .getValueAtIndex(runtime, i)
                                      .asString(runtime)
                                      .utf8(runtime);
                // 4. 通过索引以及 key 值将数据对应赋值
                jsi::Value mapValue = args[1].getObject(runtime).getProperty(
                    runtime,
                    args[1].getObject(runtime).getPropertyNames(runtime).getValueAtIndex(runtime, i).asString(runtime));

                if (mapValue.isString()) {
                    map[key] = mapValue.asString(runtime).utf8(runtime);
                }
            }

            ffmpegkit::FFmpegKitConfig::setFontDirectory(fontDirectoryPath, map);
            promise->resolve(jsi::Value().null());
        });
}

jsi::Value setFontDirectoryList(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule, &count](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (count == 2 && !args[0].isObject() && !args[1].isObject()) {
                promise->reject("Parameter exception");
                return;
            }
        
            std::list<std::string> fontDirectoryList;
            
            for (size_t i = 0; i < args[0].getObject(runtime).getArray(runtime).size(runtime); i++) {
                fontDirectoryList.push_back(args[0]
                                                .getObject(runtime)
                                                .getArray(runtime)
                                                .getValueAtIndex(runtime, i)
                                                .asString(runtime)
                                                .utf8(runtime));
            }
        
            std::map<std::string,std::string> map;
            size_t len = args[1].getObject(runtime).getPropertyNames(runtime).size(runtime);
            for (size_t i = 0; i < len; i++) {
                std::string key = args[1]
                                      .getObject(runtime)
                                      .getPropertyNames(runtime)
                                      .getValueAtIndex(runtime, i)
                                      .asString(runtime)
                                      .utf8(runtime);
                jsi::Value mapValue = args[1].getObject(runtime).getProperty(
                    runtime,
                    args[1].getObject(runtime).getPropertyNames(runtime).getValueAtIndex(runtime, i).asString(runtime));

                if (mapValue.isString()) {
                    map[key] = mapValue.asString(runtime).utf8(runtime);
                }
            }
        
            setenv("HOME", "/data/storage/el2/base/haps/entry/cache", 1);
        
            ffmpegkit::FFmpegKitConfig::setFontDirectoryList(fontDirectoryList, map);
            promise->resolve(jsi::Value().null());
        });
}

jsi::Value abstractSessionThereAreAsynchronousMessagesInTransmit(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (!args[0].isNumber()) {
                promise->reject("INVALID_SESSION: Session not found.");
                return;
            }
            int count = ffmpegkit::FFmpegKitConfig::messagesInTransmit(static_cast<long>(args[0].getNumber()));
            if (count > 0) {
                promise->resolve(jsi::Value(true));
            } else {
                promise->resolve(jsi::Value(false));
            }
        });
}

int executeCommand(const std::string& command) {
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        DLOG(ERROR) << "ffmpeg-kit RNFFmpegKitModule writeToPipe popen failed to execute command.";
        throw std::runtime_error("popen failed to execute command");
    }
    int exitCode = pclose(pipe);
    if (exitCode == -1) {
        DLOG(ERROR) << "ffmpeg-kit RNFFmpegKitModule writeToPipe pclose failed.";
        throw std::runtime_error("pclose failed");
    }
    return WEXITSTATUS(exitCode); // Extract the actual exit code
}

bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

jsi::Value writeToPipe(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {

            if (!args[0].isString()) {
                promise->reject("INVALID_INPUTPATH: inputPath not found.");
                return;
            }

            if (!args[1].isString()) {
                promise->reject("INVALID_NAMEDPIPEPATH: namedPipePath not found.");
                return;
            }

            const std::string LIBRARY_NAME = "ffmpeg-kit-react-native";
            std::string inputPath = args[0].getString(runtime).utf8(runtime);
            std::string namedPipePath = args[1].getString(runtime).utf8(runtime);

            try {
                // Check if input file exists
                if (!fileExists(inputPath)) {
                    DLOG(ERROR) << "ffmpeg-kit RNFFmpegKitModule writeToPipe fileExists. Input file does not exist: " << inputPath;
                    throw std::runtime_error("Input file does not exist: " + inputPath);
                }
                // Check if named pipe exists
                if (!fileExists(namedPipePath)) {
                    DLOG(ERROR) << "ffmpeg-kit RNFFmpegKitModule writeToPipe fileExists. Named pipe does not exist: " << namedPipePath;
                    throw std::runtime_error("Named pipe does not exist: " + namedPipePath);
                }
                // Construct the shell command
                std::string asyncCommand = "cat " + inputPath + " > " + namedPipePath;
                // Record the start time
                auto startTime = std::chrono::high_resolution_clock::now();
                // Execute the command
                int rc = executeCommand(asyncCommand);
        
                // Record the end time
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = endTime - startTime;

                DLOG(INFO) << LIBRARY_NAME << " Copying " << inputPath << " to pipe " << namedPipePath
                           << " operation completed with rc " << std::to_string(rc) << " in "
                           << std::to_string(static_cast<int>(elapsed.count())) << " seconds.";
                promise->resolve(jsi::Value(rc));
            } catch (const std::exception& e) {
                DLOG(ERROR) << LIBRARY_NAME << " Copy " << inputPath << " to pipe " << namedPipePath << " failed with error."
                           << e.what() << std::endl;
                promise->reject("Copy failed: Copy " + inputPath + " to pipe " + namedPipePath + " failed with error.");
            }

        });
}

//=============================================== JSI对外接口 end ===================================================//


//=============================================== 定义回调函数 start =================================================//


jsi::Value registerGlobalCallbacks(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            self->registerGlobalCallbacks(runtime);
            promise->resolve(jsi::Value().null());
        });
}

jsi::Value enableLogs(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
        
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            
            self->enableLogs();

            promise->resolve(jsi::Value().null());
        });
}

jsi::Value disableLogs(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
        
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            
            self->disableLogs();

            promise->resolve(jsi::Value().null());
        });
}

jsi::Value enableStatistics(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
        
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            
            self->enableStatistics();

            promise->resolve(jsi::Value().null());
        });
}

jsi::Value disableStatistics(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args, &turboModule](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
        
            auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
            
            self->disableStatistics();

            promise->resolve(jsi::Value().null());
        });
}

//=============================================== 定义回调函数 end ====================================================//


RNFFmpegKitModule::RNFFmpegKitModule(const ArkTSTurboModule::Context ctx, const std::string name)
    : ArkTSTurboModule(ctx, name) {
    
    methodMap_ = {
        {"registerGlobalCallbacks", {0, rnoh::registerGlobalCallbacks}},
        {"enableLogs", {0, rnoh::enableLogs}},
        {"disableLogs", {0, rnoh::disableLogs}},
        {"enableStatistics", {0, rnoh::enableStatistics}},
        {"disableStatistics", {0, rnoh::disableStatistics}},
        {"enableRedirection", {0, rnoh::enableRedirection}},
        {"disableRedirection", {0, rnoh::disableRedirection}},
        {"ffprobeSession", {1, rnoh::ffprobeSession}},
        {"ffprobeSessionExecute", {1, rnoh::ffprobeSessionExecute}},
        {"asyncFFprobeSessionExecute", {1, rnoh::asyncFFprobeSessionExecute}},
        {"ffmpegSessionExecute", {1, rnoh::ffmpegSessionExecute}},
        {"asyncFFmpegSessionExecute", {1, rnoh::asyncFFmpegSessionExecute}},
        {"ffmpegSession", {1, rnoh::ffmpegSession}},
        {"mediaInformationSession", {1, rnoh::mediaInformationSession}},
        {"cancelSession", {1, rnoh::cancelSession}},
        {"cancel", {0, rnoh::cancel}},
        {"clearSessions", {0, rnoh::clearSessions}},
        {"ignoreSignal", {1, rnoh::ignoreSignal}},
        {"getSession", {1, rnoh::getSession}},
        {"getSessions", {0, rnoh::getSessions}},
        {"getLastSession", {0, rnoh::getLastSession}},
        {"getLastCompletedSession", {0, rnoh::getLastCompletedSession}},
        {"getLogLevel", {0, rnoh::getLogLevel}},
        {"setLogLevel", {1, rnoh::setLogLevel}},
        {"getPlatform", {0, rnoh::getPlatform}},
        {"getArch", {0, rnoh::getArch}},
        {"getPackageName", {0, rnoh::getPackageName}},
        {"getExternalLibraries", {0, rnoh::getExternalLibraries}},
        {"isLTSBuild", {0, rnoh::isLTSBuild}},
        {"mediaInformationSessionExecute", {2, rnoh::mediaInformationSessionExecute}},
        {"asyncMediaInformationSessionExecute", {2, rnoh::asyncMediaInformationSessionExecute}},
        {"ffmpegSessionGetAllStatistics", {2, rnoh::ffmpegSessionGetAllStatistics}},
        {"ffmpegSessionGetStatistics", {1, rnoh::ffmpegSessionGetStatistics}},
        {"abstractSessionGetState", {1, rnoh::abstractSessionGetState}},
        {"abstractSessionGetReturnCode", {1, rnoh::abstractSessionGetReturnCode}},
        {"abstractSessionGetFailStackTrace", {1, rnoh::abstractSessionGetFailStackTrace}},
        {"abstractSessionGetAllLogsAsString", {2, rnoh::abstractSessionGetAllLogsAsString}},
        {"abstractSessionGetEndTime", {1, rnoh::abstractSessionGetEndTime}},
        {"abstractSessionGetDuration", {1, rnoh::abstractSessionGetDuration}},
        {"abstractSessionGetAllLogs", {2, rnoh::abstractSessionGetAllLogs}},
        {"abstractSessionGetLogs", {1, rnoh::abstractSessionGetLogs}},
        {"getFFmpegSessions", {0, rnoh::getFFmpegSessions}},
        {"setFontconfigConfigurationPath", {1, rnoh::setFontconfigConfigurationPath}},
        {"registerNewFFmpegPipe", {0, rnoh::registerNewFFmpegPipe}},
        {"closeFFmpegPipe", {1, rnoh::closeFFmpegPipe}},
        {"getFFmpegVersion", {0, rnoh::getFFmpegVersion}},
        {"getBuildDate", {0, rnoh::getBuildDate}},
        {"setEnvironmentVariable", {2, rnoh::setEnvironmentVariable}},
        {"getFFprobeSessions", {0, rnoh::getFFprobeSessions}},
        {"getMediaInformationSessions", {0, rnoh::getMediaInformationSessions}},
        {"getSessionHistorySize", {0, rnoh::getSessionHistorySize}},
        {"setSessionHistorySize", {1, rnoh::setSessionHistorySize}},
        {"messagesInTransmit", {1, rnoh::messagesInTransmit}},
        {"getSessionsByState", {1, rnoh::getSessionsByState}},
        {"getMediaInformation", {1, rnoh::getMediaInformation}},
        {"mediaInformationJsonParserFrom", {1, rnoh::mediaInformationJsonParserFrom}},
        {"abstractSessionThereAreAsynchronousMessagesInTransmit", {1, rnoh::abstractSessionThereAreAsynchronousMessagesInTransmit}},
        {"setFontDirectory", {2, rnoh::setFontDirectory}},
        {"setFontDirectoryList", {2, rnoh::setFontDirectoryList}},
        {"writeToPipe", {2, rnoh::writeToPipe}},
        ARK_METHOD_METADATA(addListener, 1),
        ARK_METHOD_METADATA(removeListeners, 1),
    };
    std::thread::id this_id = std::this_thread::get_id();
    DLOG(INFO) << "CPP RNFFmpegKitModule 初始化成功，当前 JS 线程ID：" << this_id;
}

facebook::jsi::Object RNFFmpegKitModule::toMap(facebook::jsi::Runtime &runtime, std::shared_ptr<ffmpegkit::Session> session) {
    
    facebook::jsi::Object jsObj(runtime);
    
    jsObj.setProperty(runtime, "sessionId", jsi::Value(static_cast<int>(session->getSessionId())));
    jsObj.setProperty(runtime, "createTime", jsi::Value(atd::abs(static_cast<int>(session->getCreateTime().time_since_epoch().count()))));
    jsObj.setProperty(runtime, "startTime", jsi::Value(std::abs(static_cast<int>(session->getStartTime().time_since_epoch().count()))));
    jsObj.setProperty(runtime, "command", jsi::String::createFromUtf8(runtime, session->getCommand()));
    
    if (session->isFFmpeg()) {
        jsObj.setProperty(runtime, "type", jsi::Value(1));
    } else if (session->isFFprobe()) {
        jsObj.setProperty(runtime, "type", jsi::Value(2));
    } else if (session->isMediaInformation()) {
        jsObj.setProperty(runtime, "type", jsi::Value(3));
        auto mediaInformationSession = std::dynamic_pointer_cast<ffmpegkit::MediaInformationSession>(session);
        std::shared_ptr<ffmpegkit::MediaInformation> mediaInformation = mediaInformationSession->getMediaInformation();
        if (mediaInformation) {
            std::shared_ptr<rapidjson::Value> allProperties = mediaInformation->getAllProperties();
            jsObj.setProperty(runtime, "mediaInformation", jsi::Value(runtime,medInfoToMap(runtime,*allProperties)));
        }
    }
    
    return jsObj;
}

facebook::jsi::Object RNFFmpegKitModule::statisticsToMap(facebook::jsi::Runtime &runtime, const std::shared_ptr<ffmpegkit::Statistics> &statistics) {
    facebook::jsi::Object jsObj(runtime);
    
    jsObj.setProperty(runtime, "sessionId", jsi::Value(static_cast<int>(statistics->getSessionId())));
    jsObj.setProperty(runtime, "videoFrameNumber", jsi::Value(statistics->getVideoFrameNumber()));
    jsObj.setProperty(runtime, "videoFps", jsi::Value(static_cast<double>(statistics->getVideoFps())));
    jsObj.setProperty(runtime, "videoQuality", jsi::Value(static_cast<double>(statistics->getVideoQuality())));
    jsObj.setProperty(runtime, "size", jsi::Value(runtime, static_cast<int>(statistics->getSize())));
    jsObj.setProperty(runtime, "time", jsi::Value(runtime, statistics->getTime()));
    jsObj.setProperty(runtime, "bitrate", jsi::Value(runtime, statistics->getBitrate()));
    jsObj.setProperty(runtime, "speed", jsi::Value(runtime, statistics->getSpeed()));

    return jsObj;
}

facebook::jsi::Object RNFFmpegKitModule::logToMap(facebook::jsi::Runtime &runtime, const std::shared_ptr<ffmpegkit::Log> &log) {
    facebook::jsi::Object jsObj(runtime);
    
    jsObj.setProperty(runtime, "sessionId", jsi::Value(static_cast<int>(log->getSessionId())));
    jsObj.setProperty(runtime, "level", jsi::Value(static_cast<int>(log->getLevel())));
    jsObj.setProperty(runtime, "message", jsi::Value(runtime, jsi::String::createFromUtf8(runtime,log->getMessage())));

    return jsObj;
}

facebook::jsi::Value RNFFmpegKitModule::medInfoToMap(facebook::jsi::Runtime &runtime, const rapidjson::Value &jsonValue) {
    switch(jsonValue.GetType()){
        case rapidjson::kNullType:
            return jsi::Value().null();
        case rapidjson::kFalseType:
            return jsi::Value(false);
        case rapidjson::kTrueType:
            return jsi::Value(true);
        case rapidjson::kStringType:
            return jsi::String::createFromUtf8(runtime, jsonValue.GetString());
        case rapidjson::kNumberType:
            if(jsonValue.IsInt()){
                return  jsi::Value(jsonValue.GetInt());
            } else if(jsonValue.IsInt64()){
                return  jsi::Value(static_cast<double>(jsonValue.GetInt64()));
            } else if(jsonValue.IsUint()){
                return  jsi::Value(static_cast<double>(jsonValue.GetUint()));
            } else if(jsonValue.IsUint64()){
                return  jsi::Value(static_cast<double>(jsonValue.GetUint64()));
            } else if(jsonValue.IsFloat() || jsonValue.IsDouble()){
                return  jsi::Value(jsonValue.GetDouble());
            }
        case rapidjson::kObjectType: {
            facebook::jsi::Object jsObj(runtime);
            for (rapidjson::Value::ConstMemberIterator itr = jsonValue.MemberBegin(); itr != jsonValue.MemberEnd(); ++itr) {
                auto jsValue = medInfoToMap(runtime, itr->value);
                if (!jsValue.isNull()) {
                    jsObj.setProperty(runtime, itr->name.GetString(), jsValue);
                }
            }
            return jsObj;
        }
        case rapidjson::kArrayType: {
            int len = jsonValue.Size();
            jsi::Array jsArray(runtime, len);
            for (rapidjson::SizeType i = 0; i < len; ++i) {
                auto jsValue = medInfoToMap(runtime, jsonValue[i]);
                if (!jsValue.isNull()) {
                    jsArray.setValueAtIndex(runtime, i, jsValue);
                }
            }
            return jsArray;
        }
        default:
            DLOG(INFO) << "CPP medInfoToMap 解析时遇到类型不匹配的情况.";
            break;
            
    }
    return jsi::Value().null();
}

ffmpegkit::SessionState RNFFmpegKitModule::toSessionState(const int value) {
    ffmpegkit::SessionState state;
    switch (value) { 
        case 0:
          state = ffmpegkit::SessionState::SessionStateCreated;
        case 1:
          state = ffmpegkit::SessionState::SessionStateRunning;  
        case 2:
          state = ffmpegkit::SessionState::SessionStateFailed;
        case 3:
          state = ffmpegkit::SessionState::SessionStateCompleted;
    }
    return state;
}
    
void RNFFmpegKitModule::registerGlobalCallbacks(facebook::jsi::Runtime &runtime) {
    
    ffmpegkit::FFmpegKitConfig::enableFFprobeSessionCompleteCallback(
        [&runtime, this](const std::shared_ptr<ffmpegkit::FFprobeSession> session) {
            this->getContext().taskExecutor->runTask(TaskThread::JS, [this, &runtime, session]() {
                auto ffmpegkit_session = std::dynamic_pointer_cast<ffmpegkit::Session>(session);
                jsi::Value sessionInfo[1];
                sessionInfo[0] = jsi::Value(static_cast<int>(ffmpegkit_session->getSessionId()));
                this->call(runtime, "FFmpegKitCompleteCallbackEvent", sessionInfo, 1);
            });
        });

    ffmpegkit::FFmpegKitConfig::enableFFmpegSessionCompleteCallback(
        [&runtime, this](const std::shared_ptr<ffmpegkit::FFmpegSession> session) {
            this->getContext().taskExecutor->runTask(TaskThread::JS, [this, &runtime, session]() {
                auto ffmpegkit_session = std::dynamic_pointer_cast<ffmpegkit::Session>(session);
                jsi::Value sessionInfo[1];
                sessionInfo[0] = jsi::Value(static_cast<int>(ffmpegkit_session->getSessionId()));
                this->call(runtime, "FFmpegKitCompleteCallbackEvent", sessionInfo, 1);
            });
        });

    ffmpegkit::FFmpegKitConfig::enableMediaInformationSessionCompleteCallback([&runtime,
                                                                               this](const std::shared_ptr<
                                                                                     ffmpegkit::MediaInformationSession>
                                                                                         session) {
        if (this->getContext().taskExecutor->isOnTaskThread(TaskThread::JS)) {
            auto ffmpegkit_session = std::dynamic_pointer_cast<ffmpegkit::Session>(session);
            jsi::Value sessionInfo[1];
            sessionInfo[0] = jsi::Value(this->toMap(runtime, ffmpegkit_session).getProperty(runtime, "sessionId"));
            this->call(runtime, "FFmpegKitCompleteCallbackEvent", sessionInfo, 1);
        } else {
            this->getContext().taskExecutor->runTask(TaskThread::JS, [this, &runtime, session]() {
                auto ffmpegkit_session = std::dynamic_pointer_cast<ffmpegkit::Session>(session);
                jsi::Value sessionInfo[1];
                sessionInfo[0] = jsi::Value(this->toMap(runtime, ffmpegkit_session).getProperty(runtime, "sessionId"));
                this->call(runtime, "FFmpegKitCompleteCallbackEvent", sessionInfo, 1);
            });
        }
        });

    ffmpegkit::FFmpegKitConfig::enableLogCallback([&runtime, this](const std::shared_ptr<ffmpegkit::Log> log) {
        this->getContext().taskExecutor->runTask(TaskThread::JS, [this, &runtime, log]() {
            if (logsEnabled) {
                jsi::Value logInfo[3];
                logInfo[0] = jsi::Value(static_cast<int>(log->getSessionId()));
                logInfo[1] = jsi::Value(static_cast<int>(log->getLevel()));
                logInfo[2] = jsi::Value(runtime, jsi::String::createFromUtf8(runtime, log->getMessage()));
                this->call(runtime, "FFmpegKitLogCallbackEvent", logInfo, 3);
            }
        });
    });

    ffmpegkit::FFmpegKitConfig::enableStatisticsCallback([&runtime, this](const std::shared_ptr<ffmpegkit::Statistics> statistics) {
        this->getContext().taskExecutor->runTask(TaskThread::JS, [this, &runtime, statistics]() {
            if (logsEnabled) {
                jsi::Value statisticsInfo[8];
                statisticsInfo[0] = jsi::Value(static_cast<int>(statistics->getSessionId()));
                statisticsInfo[1] = jsi::Value(statistics->getVideoFrameNumber());
                statisticsInfo[2] = jsi::Value(static_cast<double>(statistics->getVideoFps()));
                statisticsInfo[3] = jsi::Value(static_cast<double>(statistics->getVideoQuality()));
                statisticsInfo[4] = jsi::Value(static_cast<int>(statistics->getSize()));
                statisticsInfo[5] = jsi::Value(statistics->getTime());
                statisticsInfo[6] = jsi::Value(statistics->getBitrate());
                statisticsInfo[7] = jsi::Value(statistics->getSpeed());
                this->call(runtime, "FFmpegKitStatisticsCallbackEvent", statisticsInfo, 8);
            }
        });
    });
}

void RNFFmpegKitModule::enableLogs() {
    logsEnabled = true;
}

void RNFFmpegKitModule::disableLogs() {
    logsEnabled = false;
}

void RNFFmpegKitModule::enableStatistics() {
    logsEnabled = true;
}

void RNFFmpegKitModule::disableStatistics() {
    logsEnabled = false;
}

} // namespace rnoh
