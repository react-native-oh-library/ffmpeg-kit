# Changelog

## 鸿蒙化Log（br_rnoh0.72分支）
### 6.0.4-beta.3
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.0.4-beta.3

### 6.0.4-rc.3
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.0.4-rc.3

### 6.0.4-rc.2
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.0.4-rc.2
- fix: 多余的gitignore导致npm pack命令打包时缺少so

### 6.0.4-rc.1
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.0.4-rc.1
- docs: 适配RNcli工具

### 6.0.2-0.02-rc.2
- release: @react-native-ffmpeg-kit@6.0.2-0.02-rc.2
- fix: 修复底层库返回时间戳为负数的情况，导致上层无法正确解析时间

### 6.0.2-0.0.2-rc.1
- release: react-native-ffmpeg-kit@6.0.2-0.0.2-rc.1
- refactor: 修改readme文件

### 6.0.2-0.0.2-rc.0
- release: @react-native-oh-tpl/react-native-ffmpeg-kit@6.0.2-0.0.2-rc.0
- refactor: 新增三方库底层依赖库的编译指导文档以及所需依赖库的编译脚本
- refactor: 删除底层c库头文件依赖，需开发者自行编译所需依赖
- refactor: 添加LICENSE文件和版权头以及OAT扫描
- refactor: 删除引入多余的 C++ 库头文件
- feat: 完善 writeToPipe 接口的实现
- feat: 新增 getExternalLibraries 接口实现
- feat: 新增支持openh264、opus、speex、webp四个多媒体编解码能力
- feat: 新增音频指纹、添加滤镜、视频添加字幕、图片合成视频能力

### 鸿蒙化初始
- feat: OpenHarmony support