import { TurboModule, TurboModuleContext } from '@rnoh/react-native-openharmony/ts';
import { TM } from "./namespace/ts"

export class RNFFmpegKitModule extends TurboModule  implements TM.RNFFmpegKitModule.Spec{
  // 这里是arkts接口的具体实现文件，经过验证，纯jsi接口的项目，在arkts侧也需要构造一个对应的TurboModule。
  public addListener(eventName: string) {
    // this.logger.warn("DevSettings::addListener is not supported");
  }

  public removeListeners(count: number) {
    // this.logger.warn("DevSettings::removeListeners is not supported");
  }
}