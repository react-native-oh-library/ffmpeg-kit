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