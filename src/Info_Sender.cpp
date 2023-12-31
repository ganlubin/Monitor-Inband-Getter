#include "Info_Sender.hpp"
#include "tools.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <zlib.h>

bool sendZlibByUDP(std::vector<Bytef>, uLong, const std::string &, unsigned int);
uint32_t convertIPv4ToUint32(const std::string &);

int send_To_BMC(const std::string &str, const std::string &__hostname,
                const unsigned int &port) {

  unsigned long sourceLen = str.length();
  unsigned long destLen = compressBound(sourceLen);
  std::vector<Bytef> compressedData(destLen);
  if (compress(&compressedData[0], &destLen, (const Bytef *)str.c_str(),
               sourceLen) != Z_OK) {
    printError("Compression failed");
    return -1;
  }

  std::cout << "Uncompressed datalen: " << sourceLen << std::endl;
  std::cout << "Compressed datalen: " << destLen << std::endl;

  int r = sendZlibByUDP(compressedData, destLen,
                        __hostname, port);

  if (!r) {
    printError("Transport failed!");
    return -1;
  }

  return 1;
}

bool sendZlibByUDP(std::vector<Bytef> compressedData, uLong destLen,
                   const std::string &hostname, unsigned int port) {
  // 设置接收端地址和端口号
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr(hostname.c_str());

  // 创建 UDP 套接字
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    return 0;
  }

  // 发送压缩后的数据
  ssize_t sentBytes =
      sendto(sock, compressedData.data(), destLen, 0,
             (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  if (sentBytes == -1) {
    std::cerr << "Failed to send data" << std::endl;
    close(sock);
    return 0;
  }

  close(sock);
  return 1;
}
