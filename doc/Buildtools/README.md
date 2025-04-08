## 下载ohos sdk
[参考OHOS_SDK-Usage](../doc/ohos_use_sdk/OHOS_SDK-Usage.md)

## 配置环境变量
```shell
                    # 此处是我的ohos sdk解压目录, 使用者需自行配置自己的目录
    export OHOS_SDK=/home/ohos/tools/OH_SDK/ohos-sdk/linux
```

## 拷贝编译工具(支持windows/linux)
```
    cd lycium/Buildtools
    # 校验压缩包
    sha512sum -c SHA512SUM
    # 输出 toolchain.tar.gz: OK
    # 解压toolchain.tar.gz
    tar -zxvf toolchain.tar.gz
    # 将 toolchain 中的文件 copy 到 ${OHOS_SDK}/native/llvm/bin
    cp toolchain/* ${OHOS_SDK}/native/llvm/bin
    cd ${OLDPWD}
```

## 设置编译机cmake识别OHOS系统
由于 OpenHarmony SDK 中的 cmake 版本过低, 导致很多开源库在 cmake 阶段报错. 这个时候就需要用户在编译机上安装一个高版本的 cmake (推荐使用3.26版本). 但是官方版本的 cmake 是不支持 OHOS 的. 
解决方案如下: 将 SDK 中, 关于 OHOS Platform 的描述文件拷贝到系统 cmake 中.
```
cp $OHOS_SDK/native/build-tools/cmake/share/cmake-3.16/Modules/Platform/OHOS.cmake xxx(代表你编译机安装的 cmake 的路径)/cmake-3.26.3-linux-x86_64/share/cmake-3.26/Modules/Platform
```