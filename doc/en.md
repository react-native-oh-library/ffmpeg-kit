> Template Version: v0.2.2

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


> [!tip] [Github Address](https://github.com/react-native-oh-library/ffmpeg-kit)

## Installation & Usage

Please refer to the Releases page of the third-party library for the corresponding version information

| Third-party Library Version | Release Information       | Supported RN Version |
|-----------------------------| ------------------------------------------------------------ | ---------- |
| <= 6.0.3@deprecated | [@react-native-oh-tpl/react-native-ffmpeg-kit Releases(deprecated)](https://github.com/react-native-oh-library/ffmpeg-kit/releases) | 0.72       |
| 6.0.4               | [@react-native-ohos/react-native-ffmpeg-kit Releases](https://github.com/react-native-oh-library/ffmpeg-kit/releases)              | 0.72       |
| 6.1.0               | [@react-native-ohos/react-native-ffmpeg-kit Releases](https://github.com/react-native-oh-library/ffmpeg-kit/releases)              | 0.77       |

For older versions that are not published to npm, please refer to the [installation guide](/en/tgz-usage-en.md) to install the tgz package.

Go to the project directory and execute the following instruction:

<!-- tabs:start -->

#### **npm**

```bash
npm install @react-native-ohos/react-native-ffmpeg-kit
```

#### **yarn**

```bash
yarn add @react-native-ohos/react-native-ffmpeg-kit
```

The following code demonstrates basic usage scenarios of this library:

> [!WARNING] The import library name remains unchanged when using.

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

|                     | Is supported autolink  | Supported RN Version |
|---------------------|-----------------------|----------------------|
| ~6.1.0              |  No                   |  0.77                |
| ~6.0.4              |  Yes                  |  0.72                |
| <= 6.0.3@deprecated |  No                   |  0.72                |

Using AutoLink need to be configured according to this document, Autolink Framework Guide Documentation: https://gitcode.com/openharmony-sig/ohos_react_native/blob/master/docs/zh-cn/Autolinking.md

If the version you use supports Autolink and the project has been connected to Autolink, skip the ManualLink configuration.
<details>
  <summary>ManualLink: this step is a guide to manually configure native dependencies.</summary>

First, use DevEco Studio to open the HarmonyOS project `harmony` in the project directory.

### 1. Add the overrides field to `oh-package.json5` in the project root directory

```json
{
  ...
  "overrides": {
    "@rnoh/react-native-openharmony" : "./react_native_openharmony"
  }
}
```

### 2. Import native code

There are currently two methods:

1. Import via har package (this method will be deprecated after IDE improves related functionality, currently this is the preferred method);
2. Directly link source code.

Method 1: Import via har package (Recommended)

> [!TIP] The har package is located in the `harmony` folder of the third-party library installation path.

Open `entry/oh-package.json5` and add the following dependencies:

```json
"dependencies": {
    "@rnoh/react-native-openharmony": "file:../react_native_openharmony",
    "@react-native-ohos/react-native-ffmpeg-kit": "file:../../node_modules/@react-native-ohos/react-native-ffmpeg-kit/harmony/ffmpeg_kit.har",
  }
```

Click the `sync` button in the upper right corner.

Or execute in the terminal:

```bash
cd entry
ohpm install
```

Method 2: Directly link source code

> [!TIP] If you need to use direct source code linking, please refer to [Direct Link Source Code Instructions](/en/link-source-code.md)

### 3. Configure CMakeLists and import FFmpegKitPackage

> If you are using version <= 6.0.3, please skip this chapter.

Open `entry/src/main/cpp/CMakeLists.txt` and add:

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

+ add_subdirectory("${OH_MODULES}/@react-native-ohos/react-native-ffmpeg-kit/src/main/cpp" ./ffmpeg-kit)
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

Open `entry/src/main/cpp/PackageProvider.cpp` and add:

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

### 4. Import FFmpegKitPackage on ArkTs side

Open `entry/src/main/ets/RNPackagesFactory.ts` and add:

```diff
+ import { FFmpegKitPackage } from '@react-native-ohos/react-native-ffmpeg-kit/ts';

export function createRNPackages(ctx: RNPackageContext): RNPackage[] {
  return [
    new SamplePackage(ctx),
+   new FFmpegKitPackage(ctx),
  ];
}
```

</details>

## Running

Click the `sync` button in the upper right corner.

Or execute in the terminal:

```bash
cd entry
ohpm install
```

Then compile and run.

## Constraints & Limitations

### Compatibility

To use this library, you need to use the correct React-Native and RNOH versions. Additionally, you need to use the matching DevEco Studio and phone ROM.

Verified with the following versions:

1. RNOH: 0.72.38; SDK: HarmonyOS-5.0.0(API12); ROM: 5.0.0.107;
2. RNOH: 0.77.18; SDK: HarmonyOS 6.0.0 Release SDK; IDE: DevEco Studio 6.0.0.868; ROM: 6.0.0.112;
3. This third-party library is not compatible with API levels below 13;

## API

> [!tip] The "Platform" column indicates the platforms supported by the original third-party library for this property.

> [!tip] A value of "yes" in the "HarmonyOS Support" column indicates that the property is supported on the HarmonyOS platform; "no" indicates it is not supported; "partially" indicates partial support. The usage method is cross-platform consistent, with effects benchmarked against iOS or Android effects.

#### FFmpegKit

| Name | Description | Type | Required | Platform | HarmonyOS Support |
|------|-------------|------|----------|----------|-------------------|
| execute | Synchronously executes FFmpeg command provided. Space character is used to split the command into arguments. You can use single or double quote characters to specify arguments inside your command. | Promise | yes | All | yes |
| executeAsync | Starts an asynchronous FFmpeg execution for the given command. Space character is used to split the command into arguments. You can use single or double quote characters to specify arguments inside your command. | Promise | yes | All | yes |
| cancel | Cancels the session specified with `sessionId`. | Promise | yes | All | yes |
| listSessions | Lists all FFmpeg sessions in the session history. | Promise | yes | All | yes |

#### FFmpegKitConfig

| Name | Description | Type | Required | Platform | HarmonyOS Support |
|------|-------------|------|----------|----------|-------------------|
| enableLogCallback | Sets a global callback to redirect FFmpeg/FFprobe logs. | Promise | yes | All | yes |
| enableStatisticsCallback | Sets a global callback to redirect FFmpeg statistics. | Promise | yes | All | yes |
| enableLogs | Enables logs. | Promise | yes | All | yes |
| sessionStateToString | Returns the string representation of the SessionState provided. | void | yes | All | yes |
| parseArguments | Parses the given command into arguments. Uses space character to split the arguments. Supports single and double quote characters. | void | yes | All | yes |
| asyncFFprobeExecute | Starts an asynchronous FFprobe execution for the given session. | Promise | yes | All | yes |
| getLogLevel | Returns the current log level. | void | yes | All | yes |
| clearSessions | Clears all, including ongoing, sessions in the session history. | Promise | yes | All | yes |
| setSessionHistorySize | Sets the session history size. | Promise | yes | All | yes |
| init | Initializes the library asynchronously. | Promise | yes | All | yes |
| ignoreSignal | Registers a new ignored signal. Ignored signals are not handled by `FFmpegKit` library. | Promise | yes | All | yes |
| setLogLevel | Sets the log level. | Promise | yes | All | yes |
| getPlatform | Returns the platform name the library is loaded on. | Promise | yes | All | yes |
| getFFmpegVersion | Returns the version of FFmpeg bundled within `FFmpegKit` library. | Promise | yes | All | yes |
| getSessions | Returns all sessions in the session history. | Promise | yes | All | yes |
| setFontDirectoryList | Registers the fonts inside the given list of font directories, so they become available to use in FFmpeg filters. | Promise | yes | All | yes |
| setEnvironmentVariable | Sets an environment variable. | Promise | yes | All | yes |

#### FFprobeSession

| Name | Description | Type | Required | Platform | HarmonyOS Support |
|------|-------------|------|----------|----------|-------------------|
| create | Creates a new FFprobe session. | Promise | yes | All | yes |

#### ReturnCode

| Name | Description | Type | Required | Platform | HarmonyOS Support |
|------|-------------|------|----------|----------|-------------------|
| isSuccess | Success or not. | boolean | yes | All | yes |
| isCancel | Cancel or not. | boolean | yes | All | yes |

#### FFprobeKit

| Name | Description | Type | Required | Platform | HarmonyOS Support |
|------|-------------|------|----------|----------|-------------------|
| getMediaInformation | Extracts media information for the file specified with path. | Promise | yes | All | yes |
| listFFprobeSessions | Lists all FFprobe sessions in the session history. | Promise | yes | All | yes |

#### Packages

| Name | Description | Type | Required | Platform | HarmonyOS Support |
|------|-------------|------|----------|----------|-------------------|
| getPackageName | Returns the FFmpegKit ReactNative binary package name. | | | | | | Promise | yes | All | yes |

## Known Issues

## Others

## Open Source License

This project is based on [The GNU License (GNU)](https://github.com/arthenica/ffmpeg-kit/blob/main/LICENSE), please feel free to enjoy and participate in open source.