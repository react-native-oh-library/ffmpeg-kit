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

import { TurboModule, TurboModuleContext } from '@rnoh/react-native-openharmony/ts';
import { TM } from "./namespace/ts"

export class RNFFmpegKitModule extends TurboModule  implements TM.RNFFmpegKitModule.Spec{

  // 这里是arkts接口的具体实现文件，经过验证，纯jsi接口的项目，在arkts侧也需要构造一个对应的TurboModule。
  addListener(eventName: string) {
    // this.logger.warn("DevSettings::addListener is not supported");
  }

  removeListeners(count: number) {
    // this.logger.warn("DevSettings::removeListeners is not supported");
  }
  FFmpegKitLogCallbackEvent(sessionId: number, level: number, message: String): void {
    this.ctx.rnInstance.emitDeviceEvent("FFmpegKitLogCallbackEvent",
      { "sessionId": sessionId, "level": level, "message": message });
  }

  FFmpegKitStatisticsCallbackEvent(sessionId: number, videoFrameNumber: number, videoFps: number, videoQuality: number,
    size: number, time: number, bitrate: number, speed: number): void {
    this.ctx.rnInstance.emitDeviceEvent("FFmpegKitStatisticsCallbackEvent", {
      "sessionId": sessionId,
      "videoFrameNumber": videoFrameNumber,
      "videoFps": videoFps,
      "videoQuality": videoQuality,
      "size": size,
      "time": time,
      "bitrate": bitrate,
      "speed": speed
    });
  }
  FFmpegKitCompleteCallbackEvent(sessionId: number): void {
    console.log("jk---------> CPP registerGlobalCallbacks [ArkTs] 以收到 [CPP] 发送的事件")
    this.ctx.rnInstance.emitDeviceEvent("FFmpegKitCompleteCallbackEvent",{"sessionId": sessionId});
  }

}