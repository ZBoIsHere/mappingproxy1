# RoboMap Mapping Proxy

MappingProxy是一个ROS包，封装了对于原始数据以及地图的上传/下载等操作，并将原始数据/地图操作中的状态以ROS Topic的形式发布出来
其中MappingAdapter (https://github.com/roboartisan-term/mappingadapter) 封装了与MappingProxy的ROS Topic交互逻辑，方便开发者更快接入RoboMap平台

## 0. 版本

### 0.1 当前版本

v0.0.1

## 1. 安装依赖

运行MappingProxy之前，必须安装 ROS

### 1.1 ROS 环境安装

ROS 环境安装请参考 ROS 安装指南：

[ROS 安装指南](https://www.ros.org/install/)

&ensp;&ensp;&ensp;&ensp;***说明：***

&ensp;&ensp;&ensp;&ensp;（1）务必安装 ROS 完整版 (ros-distro-desktop-full)；

&ensp;&ensp;&ensp;&ensp;（2）国内安装 ROS 时，由于网络环境问题，有可能安装失败或者安装错误，请耐心查找错误原因，并解决问题；

&ensp;&ensp;&ensp;&ensp;（3）ROS 安装一共有 7 到 8 个步骤，请仔细阅读安装指南；

## 2. 获取并构建MappingProxy源代码包

1. 从MappingProxy GitHub 获取程序

   `git clone https://github.com/roboartisan-term/mappingproxy ws_robomap/src`

2. 参照如下命令，构建MappingProxy程序

   ```bash
   cd ws_robomap
   catkin_make
   ```

3. 使用如下命令更新当前 ROS 包环境

   `source ./devel/setup.sh`

## 3. 配置环境变量

### 3.1 配置原始数据位置
export RAWDATAFILE=/xxx/xxx/xxx.bag
### 3.2 配置地图保存位置
export CLOUD_MAP_PATH=/xxx/xxx/xxx/
### 3.2 配置地图文件名称
export CLOUD_MAP_NAME=xxx.pcd

## 4. 运行MappingProxy程序

### 4.1 使用 ROS launch 文件加载MappingProxy

   命令格式如下：

   `roslaunch  mappingproxy mappingproxy_rawdatacontroller.launch`
   `roslaunch  mappingproxy mappingproxy_mapcontroller.launch`

## 5. 支持

你可以通过以下方式获取 MappingProxy 的技术支持 :

* 发送邮件到 zhangbo253@huawei.com ，详细描述您遇到的问题和使用场景
* 提交此代码仓的 github issues
