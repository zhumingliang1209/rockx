## RockX命令行Demo使用指南

### Android环境

#### 编译准备

编译需要下载NDK[下载地址](https://developer.android.google.cn/ndk/downloads)

而后修改`demo/build-android-rk3399pro-v8a.sh`和`demo/build-android-rk3399pro-v7a.sh`中的`ANDROID_NDK_PATH`为自己的NDK路径

#### 编译程序

```
cd demo
./build-android-rk3399pro-v8a.sh
```

执行完之后会输出到`install/rockx_rk3399pro_android_arm64-v8a`目录

#### 部署到开发板

- 部署程序

```
adb push install/rockx_rk3399pro_android_arm64-v8a /data/
```

#### 运行

```
adb shell
cd /data/rockx_rk3399pro_android_arm64-v8a/rockx_face_landmark_demo
export LD_LIBRARY_PATH=../lib/
./rockx_face_landmark face4.jpg 68
```

执行成功之后会在当前目录生成`out_landmark.jpg`文件，可以将其pull出来查看


### Linux环境

#### 编译准备

编译需要下载aarch64交叉编译器[下载地址](https://releases.linaro.org/components/toolchain/binaries/6.3-2017.05/aarch64-linux-gnu/)

而后修改`demo/build-linux-rk3399pro.sh`中的`GCC_COMPILER_PATH`为自己的交叉编译器路径

#### 编译程序

```
cd demo
./build-linux-rk3399pro.sh
```
执行完之后会输出到`install/rockx_rk3399pro_android_arm64-v8a`目录

#### 部署到开发板

- 部署程序

```
adb push install/rockx_rk3399pro_linux_aarch64 /userdata/
```

#### 运行

```
adb shell
cd /userdata/rockx_rk3399pro_linux_aarch64/rockx_face_landmark_demo
./rockx_face_landmark face4.jpg 68
```

执行成功之后会在当前目录生成`out_landmark.jpg`文件

### RK1808计算棒

#### 安装通信代理服务

首次运行需要安装通信代理服务

```
./sdk/rockx-x86-64-Linux/bin/npu_transfer_proxy/install.sh
```

#### 编译准备

安装`gcc`和`g++`

#### 编译程序

```
./build-linux-x86.sh
```

#### 运行

```
cd install/rockx_linux_x86/rockx_face_landmark_demo
export LD_LIBRARY_PATH=../lib
./rockx_face_landmark face4.jpg 68
```

执行成功之后会在当前目录生成`out_landmark.jpg`文件