#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
#include "Boost_process.hpp"
#include "Info_Sender.hpp"
#include "Meminfo_Getter.hpp"
#include "Procps.hpp"
#include "jsonPackage.hpp"
#include "tools.hpp"
#include <fstream>
#include <unistd.h>

#define LOCAL "127.0.0.1"
#define BMC_IP0 "192.168.0.134"
#define BMC_IP1 "192.168.1.134"
#define TEST_PORT 12345

void sendInfo(const std::string &, const std::string &, const int&);

int main(int argc, char *argv[]) {

  std::string hostname = argv[1];

  uint16_t port = std::stoi(argv[2]);
  while (1) {
    // return /proc/meminfo json
    json meminfo = meminfo_getter();
    std::string meminfo_str = meminfo.dump();

    // get boost_process include system and processes, create files:
    // Boost_process_info_process.txt and Boost_process_info_system.txt
    std::string boost_addr =
        "/home/sokee/workspace/Monitor-Inband-Getter/src"; /* plz write addr here */
    boost_process(boost_addr);

    // get Procps.txt: describe processes' details
    std::string procps_addr =
        "/home/sokee/workspace/Monitor-Inband-Getter/src/Procps.txt";
    procps(procps_addr);

    // json
    std::string process_json = create_info_json(boost_addr, procps_addr);

    json mem = json::parse(meminfo_str);
    json pro = json::parse(process_json);
    json mergedJson;
    mergedJson["meminfo"] = mem;
    mergedJson["process"] = pro;
    std::string temp = mergedJson.dump();

    sendInfo(temp, hostname, port);
    sleep(5);
  }
  return 0;
}

// send the info
void sendInfo(const std::string &info, const std::string &hostname, const int &port) {

  send_To_BMC(info, hostname, port);
  
}