// This file was generated.

#include "RNFFmpegKitModule.h"
#include "FFmpegKitConfig.h"
#include "FFmpegSession.h"
#include <cstdint>

namespace rnoh {
using namespace facebook;

//=============================================== JSI对外接口 start ===============================================//


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

        if (args[0].isNull() || args[0].isUndefined()) {
            promise->reject("INVALID_SESSION: Invalid session id.");
            return;
        }
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

        jsi::Object resultInfo(runtime);
        resultInfo.setProperty(runtime, "sessionId", jsi::Value(static_cast<double>(fFmpegSession->getSessionId())));
        resultInfo.setProperty(
            runtime, "createTime",
            jsi::Value(static_cast<double>(fFmpegSession->getCreateTime().time_since_epoch().count())));
        resultInfo.setProperty(
            runtime, "startTime",
            jsi::Value(static_cast<double>(fFmpegSession->getStartTime().time_since_epoch().count())));
        resultInfo.setProperty(runtime, "command", fFmpegSession->getCommand());

        if (fFmpegSession->isFFmpeg()) {
            resultInfo.setProperty(runtime, "type", 1);
        } else if (fFmpegSession->isFFprobe()) {
            resultInfo.setProperty(runtime, "type", 2);
        } else if (fFmpegSession->isMediaInformation()) {
            resultInfo.setProperty(runtime, "type", 3);
            auto mediaInformationSession = std::dynamic_pointer_cast<ffmpegkit::MediaInformationSession>(fFmpegSession);
            std::shared_ptr<ffmpegkit::MediaInformation> mediaInformation =
                mediaInformationSession->getMediaInformation();
            if (mediaInformation) {
                // TODO: 待处理 自调用 类型问题
                // resultInfo.setProperty(runtime, "mediaInformation", toMap(rt,mediaInformation));
            }
        }

        promise->resolve(jsi::Value(runtime, resultInfo));

        // auto self = static_cast<RNFFmpegKitModule *>(&turboModule);
        // TODO 方法接收的参数是父类对象，这里是子类，类型问题，还有 map 和 object类型转换问题，待处理.
        // promise->resolve(jsi::Object(self->toMap(runtime, fFmpegSession)));
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
        rt, [](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
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
        rt, [args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (args[0].isNull() || args[0].isUndefined()) {
                promise->reject("INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session->isFFmpeg()) {
                // TODO android 平台在这里启动了线程并使用了线程管理工具，鸿蒙大概率也需要，c++ 线程池概念
                ffmpegkit::FFmpegKitConfig::ffmpegExecute(std::dynamic_pointer_cast<ffmpegkit::FFmpegSession>(session));
                promise->resolve(jsi::Value::null());
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
                promise->reject("INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session) {
                promise->resolve(jsi::Value(static_cast<int>(session->getState())));
            } else {
                promise->reject("SESSION_NOT_FOUND: Session not found.");
                DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
            }
        });
}

jsi::Value abstractSessionGetReturnCode(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                        const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (args[0].isNull() || args[0].isUndefined()) {
                promise->reject("INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session) {
                std::shared_ptr<ffmpegkit::ReturnCode> returnCode = session->getReturnCode();
                if (returnCode) {
                    promise->resolve(jsi::Value(returnCode->getValue()));
                } else {
                    promise->resolve(jsi::Value().null());
                }
            } else {
                promise->reject("SESSION_NOT_FOUND: Session not found.");
                DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
            }
        });
}

jsi::Value abstractSessionGetFailStackTrace(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                            const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (args[0].isNull() || args[0].isUndefined()) {
                promise->reject("INVALID_SESSION: Invalid session id.");
                return;
            }
            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (session) {
                promise->resolve(jsi::String::createFromUtf8(runtime, session->getFailStackTrace()));
            } else {
                promise->reject("SESSION_NOT_FOUND: Session not found.");
                DLOG(ERROR) << "SESSION_NOT_FOUND: Session not found.";
            }
        });
}

jsi::Value abstractSessionGetAllLogsAsString(facebook::jsi::Runtime &rt, react::TurboModule &turboModule,
                                             const facebook::jsi::Value *args, size_t count) {
    return facebook::react::createPromiseAsJSIValue(
        rt, [&args](jsi::Runtime &runtime, std::shared_ptr<facebook::react::Promise> promise) {
            if (args[0].isNull() || args[0].isUndefined() || !args[0].isNumber()) {
                promise->reject("INVALID_SESSION: Invalid session id.");
                return;
            }

            if (args[1].isNull() || args[1].isUndefined() || !args[1].isNumber() || args[1].asNumber() < 0) {
                promise->reject("The second parameter is invalid waitTimeout.");
                return;
            }

            std::shared_ptr<ffmpegkit::Session> session = ffmpegkit::FFmpegKitConfig::getSession(args[0].asNumber());
            if (!session) {
                promise->reject("SESSION_NOT_FOUND: Session not found.");
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

//=============================================== JSI对外接口 end ===================================================//


RNFFmpegKitModule::RNFFmpegKitModule(const ArkTSTurboModule::Context ctx, const std::string name)
    : ArkTSTurboModule(ctx, name) {
    methodMap_ = {
        {"ffmpegSession", {1, rnoh::ffmpegSession}},
        {"getLogLevel", {0, rnoh::getLogLevel}},
        {"getPlatform", {0, rnoh::getPlatform}},
        {"getArch", {0, rnoh::getArch}},
        {"getPackageName", {0, rnoh::getPackageName}},
        {"enableRedirection", {0, rnoh::enableRedirection}},
        {"isLTSBuild", {0, rnoh::isLTSBuild}},
        {"ffmpegSessionExecute", {1, rnoh::ffmpegSessionExecute}},
        {"abstractSessionGetState", {1, rnoh::abstractSessionGetState}},
        {"abstractSessionGetReturnCode", {1, rnoh::abstractSessionGetReturnCode}},
        {"abstractSessionGetFailStackTrace", {1, rnoh::abstractSessionGetFailStackTrace}},
        {"abstractSessionGetAllLogsAsString", {2, rnoh::abstractSessionGetAllLogsAsString}},
        ARK_METHOD_METADATA(addListener, 1),
        ARK_METHOD_METADATA(removeListeners, 1),
    };
    DLOG(INFO) << "jk------------->CPP RNFFmpegKitModule 初始化成功";
}

jsi::Object RNFFmpegKitModule::toMap(facebook::jsi::Runtime &runtime, std::shared_ptr<ffmpegkit::Session> &session) {
    jsi::Object resultInfo(runtime);
    resultInfo.setProperty(runtime, "sessionId", jsi::Value(static_cast<double>(session->getSessionId())));
    resultInfo.setProperty(runtime, "createTime",
                           jsi::Value(static_cast<double>(session->getCreateTime().time_since_epoch().count())));
    resultInfo.setProperty(runtime, "startTime",
                           jsi::Value(static_cast<double>(session->getStartTime().time_since_epoch().count())));
    resultInfo.setProperty(runtime, "command", session->getCommand());

    if (session->isFFmpeg()) {
        resultInfo.setProperty(runtime, "type", 1);
    } else if (session->isFFprobe()) {
        resultInfo.setProperty(runtime, "type", 2);
    } else if (session->isMediaInformation()) {
        resultInfo.setProperty(runtime, "type", 3);
        auto mediaInformationSession = std::dynamic_pointer_cast<ffmpegkit::MediaInformationSession>(session);
        std::shared_ptr<ffmpegkit::MediaInformation> mediaInformation = mediaInformationSession->getMediaInformation();
        if (mediaInformation) {
            // TODO: 待处理 自调用 类型问题
            // resultInfo.setProperty(runtime, "mediaInformation", toMap(rt,mediaInformation));
        }
    }

    return resultInfo;
}

} // namespace rnoh
