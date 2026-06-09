# Changelog

## 鸿蒙化Log（br_rnoh0.82 分支）
### v6.2.0-beta.2

- pre-release version v6.2.0-beta.2

### 6.2.0-rc.2 (2026-06-05)
- release: @react-native-ohos/react-native-ffmpeg-kit@6.2.0-rc.2
- fix: 将 popen(cat file > pipe) 替换为 C 文件 I/O，解决 popen 在部分平台不支持的问题

### 6.2.0-rc.1 (2026-04-28)
- release: @react-native-ohos/react-native-ffmpeg-kit@6.2.0-rc.1
- feat: 适配 `autolink`

### 6.1.0 (2026-03-21)
- release: @react-native-ohos/react-native-ffmpeg-kit@6.1.0

### 6.1.0-rc.4 (2026-03-10)
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.1.0-rc.4

### 6.1.0-rc.3 (2026-03-09)
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.1.0-rc.3
- fix: 修复 `registerNewFFmpegPipe` 接口返回空指针导致的崩溃

### 6.1.0-rc.2 (2025-11-27)
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.1.0-rc.2

### 6.1.0-rc.1 (2025-11-18)
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.1.0-rc.1

### 6.0.4-rc.3 (2026-05-29)
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.0.4-rc.3

### 6.0.4-rc.2 (2026-05-27)
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.0.4-rc.2
- fix: 多余的 `.gitignore` 导致 `npm pack` 打包时缺少 so 文件，已修复

### 6.0.4-rc.1 (2025-12-12)
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.0.4-rc.1
- docs: 适配 RN CLI 工具

### 6.0.3-rc.2 (2025-10-28)
- pre-release: @react-native-ohos/react-native-ffmpeg-kit@6.0.3-rc.2
- fix: 适配 RN0.77，更新 README，调整组织名为 `@react-native-ohos`

### 6.0.3-rc.1 (2025-11-13)
- pre-release: @react-native-oh-tpl/react-native-ffmpeg-kit@6.0.3-rc.1
- add: 新增 `CHANGELOG.md`

### 6.0.2-0.02-rc.2 (2025-05-21)
- release: @react-native-ffmpeg-kit@6.0.2-0.02-rc.2
- fix: 修复底层库返回时间戳为负数的问题，避免上层解析异常

### 6.0.2-0.0.2-rc.1 (2025-05-14)
- release: react-native-ffmpeg-kit@6.0.2-0.0.2-rc.1
- refactor: 修改 README

### 6.0.2-0.0.2-rc.0 (2025-04-08)
- release: @react-native-oh-tpl/react-native-ffmpeg-kit@6.0.2-0.0.2-rc.0
- refactor: 新增三方库底层依赖编译指导与脚本；去除底层 c 头文件依赖，改为由开发者编译所需依赖
- refactor: 添加 LICENSE/版权头与 OAT 扫描
- feat: 完善 `writeToPipe`、`getExternalLibraries` 等接口；新增 openh264/opus/speex/webp 等编解码能力

### 鸿蒙化初始
- feat: OpenHarmony support (起始提交)
