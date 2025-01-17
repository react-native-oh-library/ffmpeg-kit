import type { RNPackageContext, UITurboModule, UITurboModuleContext } from '@rnoh/react-native-openharmony/ts';
import { RNPackage, UITurboModuleFactory } from '@rnoh/react-native-openharmony/ts';
import { RNFFmpegKitModule } from './RNFFmpegKitModule';
import { TM } from "./namespace/ts"

class FFmpegKitPackageTurboModulesFactory extends UITurboModuleFactory {
  createTurboModule(name: string): UITurboModule | null {
    if (name === TM.RNFFmpegKitModule.NAME) {
      return new RNFFmpegKitModule(this.ctx);
    }
    return null;
  }

  hasTurboModule(name: string): boolean {
    return name === TM.RNFFmpegKitModule.NAME;
  }
}

export class FFmpegKitPackage extends RNPackage {
  createTurboModulesFactory(ctx: UITurboModuleContext): UITurboModuleFactory {
    return new FFmpegKitPackageTurboModulesFactory(ctx);
  }
}