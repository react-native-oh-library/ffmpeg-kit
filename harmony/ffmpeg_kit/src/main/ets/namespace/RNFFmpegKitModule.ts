// This file was generated.

export namespace RNFFmpegKitModule {
  export const NAME = 'NativeRNFFmpegKitModule' as const

  export interface Spec {
    // 这里是定义arkts接口的文件，如果有需要，可在这里增加arkts接口
    addListener(eventName: string);
    removeListeners(count: number);
    FFmpegKitCompleteCallbackEvent(sessionId: number);
    FFmpegKitLogCallbackEvent(sessionId: number,level:number,message:String);
    FFmpegKitStatisticsCallbackEvent(sessionId: number,videoFrameNumber:number,videoFps:number,videoQuality:number,size:number,time:number,bitrate:number,speed:number);
  }
}