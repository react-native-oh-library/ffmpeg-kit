# HPKBUILD build script!
协助开发者, 为 OpenHarmony 系统快速编译、验证以及长期维护 c/c++ 开源库. 
## 使用
执行脚本 build.sh, 自动编译 main 目录下的相关开源库，并自动打包安装到 \$LYCIUM\_ROOT/usr/\$pkgname/\$ARCH 目录
```shell
    ./build.sh # 隐式编译：编译 main 目录下的所有库
```
```shell
    ./build.sh aaa bbb ccc ... # 显式编译：编译 main 目录下指定的 aaa bbb ccc ... 库, 以及相关的依赖库.
```
## 注意事项
**移植过程, 如果同时使用到了chromaprint和FFmpeg，这两个三方库会彼此依赖，按照下面的步骤编译：**
```
./build.sh chromaprint 先编译chromaprint

然后删除usr/hpk_build.csv里的
FFmpeg,n6.1.2,armeabi-v7a
FFmpeg,n6.1.2,arm64-v8a

修改main/FFmpeg/HPKBUILD里的PKG_CONFIG_PATH，添加${LYCIUM_ROOT}/usr/chromaprint/$ARCH/lib/pkgconfig:
在下方配置项里添加--enable-chromaprint

编译./build.sh ffmpeg-kit
```
## docker环境开发（推荐）
为了保证所有开发\测试人员在使用 lycium 的时候不在环境搭建上浪费时间。我们提供了针对lycium的docker搭建方案。详细说明[参见](./docker/README.md)。

### 1.编译环境准备（必读）
请仔细阅读 [Buildtools README](./Buildtools/README.md)。

### 2.HPKBUILD 编写说明 
请仔细阅读 [template README](./template/README.md) ,同时为了测试我们最好把测试用例一起编译出来。

### 3.CI环境准备
请仔细查阅 [lycium CItools](https://gitee.com/han_jin_fei/lycium-citools),搭建好测试环境后,就可以将我们编译的开源库copy到openharmony设备上，运行原生测试用例。

## 目录介绍
Buildtools: 存放编译环境所需的说明文档及工具

dockers：搭建lycium docker环境需要的资源

main: 存放开源库的移植脚本，每个目录对应一个开源库

script: 存放项目脚本

build.sh: 编译构建脚本
