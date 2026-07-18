> 模板版本：v0.2.2

<p align="center">
  <h1 align="center"> <code>react-native-ffmpeg-kit</code> </h1>
</p>
<p align="center">
    <a href="https://github.com/arthenica/ffmpeg-kit/tree/main/react-native">
        <img src="https://img.shields.io/badge/platforms-android%20|%20ios%20|%20harmony%20-lightgrey.svg" alt="Supported platforms" />
    </a>
        <a href="https://github.com/arthenica/ffmpeg-kit/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/license-GNU-green.svg
" alt="License" />
    </a>
</p>


> [!tip] [Github 地址](https://github.com/react-native-oh-library/ffmpeg-kit)

## 安装与使用

请到三方库的 Releases 发布地址查看配套的版本信息：[@react-native-oh-tpl/ffmpeg-kit Releases](https://github.com/react-native-oh-library/ffmpeg-kit/releases)。对于未发布到npm的旧版本，请参考[安装指南](https://gitee.com/react-native-oh-library/usage-docs/blob/master/zh-cn/tgz-usage.md)安装tgz包。

进入到工程目录并输入以下命令：

#### **npm**

```bash
npm install @react-native-oh-tpl/react-native-ffmpeg-kit
```

#### **yarn**

```bash
yarn add @react-native-oh-tpl/react-native-ffmpeg-kit
```

下面的代码展示了这个库的基本使用场景：

> [!WARNING] 使用时 import 的库名不变。

```js
import React from 'react';
import {ScrollView, Text, TextInput, TouchableOpacity, View} from 'react-native';
import {
    FFmpegKit,
    FFmpegKitConfig,
    FFprobeSession,
    Level,
    LogRedirectionStrategy,
    SessionState
} from "ffmpeg-kit-react-native";

export default class CommandTab extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            commandText: '', outputText: ''
        };
    }

    componentDidMount() {
        this.props.navigation.addListener('focus', (_) => {
            this.clearOutput();
            this.setActive();
        });
    }

    setActive() {
        console.log("Command Tab Activated");
        FFmpegKitConfig.enableLogCallback(undefined);
        FFmpegKitConfig.enableStatisticsCallback(undefined);
    }

    appendOutput(logMessage) {
        this.setState({outputText: this.state.outputText + logMessage});
    };

    clearOutput() {
        this.setState({outputText: ''});
    }

    runFFmpeg = () => {
        this.clearOutput();

        let ffmpegCommand = this.state.commandText;

        FFmpegKit.execute(ffmpegCommand).then(async (session) => {
            const state = FFmpegKitConfig.sessionStateToString(await session.getState());
            const returnCode = await session.getReturnCode();
            const failStackTrace = await session.getFailStackTrace();
            const output = await session.getOutput();

            this.appendOutput(output);

            if (state === SessionState.FAILED || !returnCode.isValueSuccess()) {
                console.log("Command failed. Please check output for the details.");
            }
        });
    };

    runFFprobe = () => {
        this.clearOutput();

        let ffprobeCommand = this.state.commandText;-
        FFprobeSession.create(FFmpegKitConfig.parseArguments(ffprobeCommand), async (session) => {
            const state = FFmpegKitConfig.sessionStateToString(await session.getState());
            const returnCode = await session.getReturnCode();
            const failStackTrace = await session.getFailStackTrace();
            session.getOutput().then(output => this.appendOutput(output));


            if (state === SessionState.FAILED || !returnCode.isValueSuccess()) {
                console.log("Command failed. Please check output for the details.");
            }

        }, undefined, LogRedirectionStrategy.NEVER_PRINT_LOGS).then(session => {
            FFmpegKitConfig.asyncFFprobeExecute(session);
        });
    };

    render() {
        return (<View style={styles.screenStyle}>
            <View style={styles.headerViewStyle}>
                <Text style={styles.headerTextStyle}>
                    FFmpegKit ReactNative
                </Text>
            </View>
            <View style={styles.textInputViewStyle}>
                <TextInput
                    style={styles.textInputStyle}
                    autoCapitalize='none'
                    autoCorrect={false}
                    placeholder="Enter command"
                    underlineColorAndroid="transparent"
                    onChangeText={(commandText) => this.setState({commandText})}
                    value={this.state.commandText}
                />
            </View>
            <View style={styles.buttonViewStyle}>
                <TouchableOpacity
                    style={styles.buttonStyle}
                    onPress={this.runFFmpeg}>
                    <Text style={styles.buttonTextStyle}>RUN FFMPEG</Text>
                </TouchableOpacity>
            </View>
            <View style={styles.buttonViewStyle}>
                <TouchableOpacity
                    style={styles.buttonStyle}
                    onPress={this.runFFprobe}>
                    <Text style={styles.buttonTextStyle}>RUN FFPROBE</Text>
                </TouchableOpacity>
            </View>
            <View style={styles.outputViewStyle}>
                <ScrollView
                    ref={(view) => {
                        this.scrollViewReference = view;
                    }}
                    onContentSizeChange={(width, height) => this.scrollViewReference.scrollTo({y: height})}
                    style={styles.outputScrollViewStyle}>
                    <Text style={styles.outputTextStyle}>{this.state.outputText}</Text>
                </ScrollView>
            </View>
        </View>);
    };

}

const styles = StyleSheet.create({
    screenStyle: {
        flex: 1,
        justifyContent: 'flex-start',
        alignItems: 'stretch',
        marginTop: Platform.select({ios: 20, android: 0})
    },
    headerViewStyle: {
        paddingTop: 16,
        paddingBottom: 10,
        backgroundColor: '#F46842'
    },
    headerTextStyle: {
        alignSelf: 'center',
        height: 32,
        fontSize: 18,
        fontWeight: 'bold',
        color: '#fff',
        borderColor: 'lightgray',
        borderRadius: 5,
        borderWidth: 0
    },
    buttonViewStyle: {
        alignSelf: 'center',
        paddingBottom: 20
    },
    buttonStyle: {
        justifyContent: 'center',
        alignSelf: 'center',
        width: 120,
        height: 38,
        backgroundColor: '#2ecc71',
        borderColor: '#27AE60',
        borderRadius: 5,
        paddingLeft: 10,
        paddingRight: 10
    },
    cancelButtonStyle: {
        justifyContent: 'center',
        width: 100,
        height: 38,
        backgroundColor: '#c5c5c5',
        borderRadius: 5
    },
    buttonTextStyle: {
        textAlign: 'center',
        fontSize: 14,
        fontWeight: 'bold',
        color: '#fff'
    },
    videoPlayerViewStyle: {
        backgroundColor: '#ECF0F1',
        borderColor: '#B9C3C7',
        borderRadius: 5,
        borderWidth: 1,
        height: window.height - 310,
        width: window.width - 40,
        marginVertical: 20,
        marginHorizontal: 20
    },
    halfSizeVideoPlayerViewStyle: {
        backgroundColor: '#ECF0F1',
        borderColor: '#B9C3C7',
        borderRadius: 5,
        borderWidth: 1,
        height: (window.height - 250) / 2,
        width: window.width - 40,
        marginVertical: 20,
        marginHorizontal: 20
    },
    outputViewStyle: {
        padding: 20,
        flex: 1,
        justifyContent: 'flex-start',
        alignItems: 'stretch'
    },
    outputScrollViewStyle: {
        padding: 4,
        backgroundColor: '#f1c40f',
        borderColor: '#f39c12',
        borderRadius: 5,
        borderWidth: 1
    },
    outputTextStyle: {
        color: 'black'
    },
    textInputViewStyle: {
        paddingTop: 40,
        paddingBottom: 40,
        paddingRight: 20,
        paddingLeft: 20
    },
    textInputStyle: {
        height: 36,
        fontSize: 12,
        borderColor: '#3498db',
        borderRadius: 5,
        borderWidth: 1
    }
});

```

## Link

目前 HarmonyOS 暂不支持 AutoLink，所以 Link 步骤需要手动配置。

首先需要使用 DevEco Studio 打开项目里的 HarmonyOS 工程 `harmony`

### 1.在工程根目录的 `oh-package.json5` 添加 overrides 字段

```json
{
  ...
  "overrides": {
    "@rnoh/react-native-openharmony" : "./react_native_openharmony"
  }
}
```

### 2.引入原生端代码

目前有两种方法：

1. 通过 har 包引入（在 IDE 完善相关功能后该方法会被遗弃，目前首选此方法）；
2. 直接链接源码。

方法一：通过 har 包引入（推荐）

> [!TIP] har 包位于三方库安装路径的 `harmony` 文件夹下。

打开 `entry/oh-package.json5`，添加以下依赖

```json
"dependencies": {
    "@rnoh/react-native-openharmony": "file:../react_native_openharmony",

    "@react-native-oh-tpl/react-native-ffmpeg-kit": "file:../../node_modules/@react-native-oh-tpl/react-native-ffmpeg-kit/harmony/ffmpeg_kit.har",
  }
```

点击右上角的 `sync` 按钮

或者在终端执行：

```bash
cd entry
ohpm install
```

方法二：直接链接源码

> [!TIP] 如需使用直接链接源码，请参考[直接链接源码说明](/zh-cn/link-source-code.md)

### 3.配置 CMakeLists 和引入 GestureHandlerPackage

打开 `entry/src/main/cpp/CMakeLists.txt`，添加：

```diff
project(rnapp)
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(RNOH_APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
+ set(NODE_MODULES "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../node_modules")
+ set(OH_MODULES "${CMAKE_CURRENT_SOURCE_DIR}/../../../oh_modules")
set(RNOH_CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../react-native-harmony/harmony/cpp")
set(LOG_VERBOSITY_LEVEL 1)
set(CMAKE_ASM_FLAGS "-Wno-error=unused-command-line-argument -Qunused-arguments")
set(CMAKE_CXX_FLAGS "-fstack-protector-strong -Wl,-z,relro,-z,now,-z,noexecstack -s -fPIE -pie")
set(WITH_HITRACE_SYSTRACE 1) # for other CMakeLists.txt files to use
add_compile_definitions(WITH_HITRACE_SYSTRACE)

add_subdirectory("${RNOH_CPP_DIR}" ./rn)

# RNOH_BEGIN: manual_package_linking_1
add_subdirectory("../../../../sample_package/src/main/cpp" ./sample-package)
+ add_subdirectory("${OH_MODULES}/@react-native-oh-tpl/react-native-ffmpeg-kit/src/main/cpp" ./ffmpeg-kit)
# RNOH_END: manual_package_linking_1

file(GLOB GENERATED_CPP_FILES "./generated/*.cpp")

add_library(rnoh_app SHARED
    ${GENERATED_CPP_FILES}
    "./PackageProvider.cpp"
    "${RNOH_CPP_DIR}/RNOHAppNapiBridge.cpp"
)
target_link_libraries(rnoh_app PUBLIC rnoh)

# RNOH_BEGIN: manual_package_linking_2
target_link_libraries(rnoh_app PUBLIC rnoh_sample_package)
+ target_link_libraries(rnoh_app PUBLIC rnoh_ffmpeg_kit)
# RNOH_END: manual_package_linking_2
```

打开 `entry/src/main/cpp/PackageProvider.cpp`，添加：

```diff
#include "RNOH/PackageProvider.h"
#include "SamplePackage.h"
+ #include "FFmpegKitPackage.h"

using namespace rnoh;

std::vector<std::shared_ptr<Package>> PackageProvider::getPackages(Package::Context ctx) {
    return {
      std::make_shared<SamplePackage>(ctx),
+     std::make_shared<FFmpegKitPackage>(ctx)
    };
}
```

### 4.在 ArkTs 侧引入 Gesture Handler Package

打开 `entry/src/main/ets/RNPackagesFactory.ts`，添加：

```diff
+ import { FFmpegKitPackage } from '@react-native-oh-tpl/react-native-ffmpeg-kit/ts';

export function createRNPackages(ctx: RNPackageContext): RNPackage[] {
  return [
    new SamplePackage(ctx),
+   new FFmpegKitPackage(ctx),
  ];
}
```

### 5.运行

点击右上角的 `sync` 按钮

或者在终端执行：

```bash
cd entry
ohpm install
```

然后编译、运行即可。

## 约束与限制

### 兼容性

要使用此库，需要使用正确的 React-Native 和 RNOH 版本。另外，还需要使用配套的 DevEco Studio 和 手机 ROM。

请到三方库相应的 Releases 发布地址查看 Release 配套的版本信息：[@react-native-oh-tpl/ffmpeg-kit Releases](https://github.com/react-native-oh-library/ffmpeg-kit/releases)


##  API


> [!tip] "Platform"列表示该属性在原三方库上支持的平台。

> [!tip] "HarmonyOS Support"列为 yes 表示 HarmonyOS 平台支持该属性；no 则表示不支持；partially 表示部分支持。使用方法跨平台一致，效果对标 iOS 或 Android 的效果。

#### FFmpegKit

| Name   | Description                                                                                  | Type                             | Required | Platform | HarmonyOS Support |
| ---------- | ------------------------------------------------------------------------------------------------ | ------------------------------------ | -------- | -------- | -------- |
| execute    | Synchronously executes FFmpeg command provided. Space character is used to split the command into arguments. You can use single or double quote characters to specify arguments inside your command.                                     | Promise | yes      | All      | yes      |
| executeAsync    | Starts an asynchronous FFmpeg execution for the given command. Space character is used to split the command into arguments. You can use single or double quote characters to specify arguments inside your command.                                     | Promise | yes      | All      | yes      |
| cancel    | Cancels the session specified with <code>sessionId</code>. | Promise | yes      | All      | yes      |
| listSessions    | Lists all FFmpeg sessions in the session history. | Promise | yes      | All      | yes      |

#### FFmpegKitConfig

| Name   | Description                                                                                  | Type                             | Required | Platform | HarmonyOS Support |
| :--------- | ------------------------------------------------------------------------------------------------ | ------------------------------------ | -------- | -------- | -------- |
| enableLogCallback    | Sets a global callback to redirect FFmpeg/FFprobe logs.                                     | Promise | yes      | All      | yes      |
| enableStatisticsCallback    | Sets a global callback to redirect FFmpeg statistics.                                     | Promise | yes      | All      | yes      |
| enableLogs    | Enables logs. | Promise | yes      | All      | yes      |
| sessionStateToString    | Returns the string representation of the SessionState provided. | void | yes      | All      | yes      |
| parseArguments    | Parses the given command into arguments. Uses space character to split the arguments.Supports single and double quote characters. | void | yes      | All      | yes      |
| asyncFFprobeExecute    | Starts an asynchronous FFprobe execution for the given session. | Promise | yes      | All      | yes      |
| getLogLevel    | Returns the current log level. | void | yes      | All      | yes      |
| clearSessions    | Clears all, including ongoing, sessions in the session history. | Promise | yes      | All      | yes      |
| setSessionHistorySize    | Sets the session history size. | Promise | yes      | All      | yes      |
| init    | Initializes the library asynchronously. | Promise | yes      | All      | yes      |
| ignoreSignal    | Registers a new ignored signal. Ignored signals are not handled by <code>FFmpegKit</code>library | Promise      | yes      | All      |yes|
| setLogLevel    | Sets the log level. | Promise | yes      | All      | yes      |
| getPlatform    | Returns the platform name the library is loaded on. | Promise | yes      | All      | yes      |
| getFFmpegVersion    | Returns the version of FFmpeg bundled within <code>FFmpegKit</code> library. | Promise | yes      | All      | yes      |
| getSessions    | Returns all sessions in the session history. | Promise | yes      | All      | yes      |
| setFontDirectoryList    | Registers the fonts inside the given list of font directories, so they become available to use in FFmpeg filters. | Promise | yes      | All      | yes      |
| setEnvironmentVariable    | Sets an environment variable. | Promise | yes      | All      | yes      |

#### FFprobeSession

| Name   | Description                                                                                  | Type                             | Required | Platform | HarmonyOS Support |
| :--------- | ------------------------------------------------------------------------------------------------ | ------------------------------------ | -------- | -------- | -------- |
| create    | Creates a new FFprobe session.                                     | Promise | yes      | All      | yes      |

#### ReturnCode

| Name   | Description                                                                                  | Type                             | Required | Platform | HarmonyOS Support |
| :--------- | ------------------------------------------------------------------------------------------------ | ------------------------------------ | -------- | -------- | -------- |
| isSuccess    | Success or not.                                     | boolean | yes      | All      | yes      |
| isCancel    | Cancel or not.                                     | boolean | yes      | All      | yes      |

#### FFprobeKit

| Name   | Description                                                                                  | Type                             | Required | Platform | HarmonyOS Support |
| :--------- | ------------------------------------------------------------------------------------------------ | ------------------------------------ | -------- | -------- | -------- |
| getMediaInformation    | Extracts media information for the file specified with path.                                     | Promise | yes      | All      | yes      |
| listFFprobeSessions    | Lists all FFprobe sessions in the session history.                                     | Promise | yes      | All      | yes      |

#### Packages

| Name   | Description                                                                                  | Type                             | Required | Platform | HarmonyOS Support |
| :--------- | ------------------------------------------------------------------------------------------------ | ------------------------------------ | -------- | -------- | -------- |
| getPackageName    | Returns the FFmpegKit ReactNative binary package name.                                     | Promise | yes      | All      | yes      |

## 遗留问题

## 其他

## 开源协议

本项目基于 [The GNU License (GNU)](https://github.com/arthenica/ffmpeg-kit/blob/main/LICENSE) ，请自由地享受和参与开源。
