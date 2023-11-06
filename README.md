# Monitor-Inband-Getter

compile the project.

```bash
cd src
mkdir build
cd build
cmake ..
sudo make
```

### 2023-11-06 下一步工作安排

1. 查清楚proc的功能
2. 获取到proc中关于磁盘的资源信息
3. 改进方式，使用UDP传输json资源，而不是写入json文件
4. 结合以上将需要的信息发送至BMC端
5. 设计BMC的服务，用于接收发送端传过来的数据，记录保存
