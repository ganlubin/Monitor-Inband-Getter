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

void sendInfo(const std::string &, const std::string &);

int main() {

  // return /proc/meminfo json
  json meminfo = meminfo_getter();
  std::string meminfo_str = meminfo.dump();

  // get boost_process include system and processes, create files:
  // Boost_process_info_process.txt and Boost_process_info_system.txt
  std::string boost_addr =
      "/home/Monitor-Inband-Getter/src"; /* plz write addr here */
  boost_process(boost_addr);

  // get Procps.txt: describe processes' details
  std::string procps_addr =
      "/home/Monitor-Inband-Getter/src/Procps.txt";
  procps(procps_addr);

  // json
  std::string process_json = create_info_json(boost_addr, procps_addr);

  sendInfo(meminfo_str, process_json);

  return 0;
}

// send the info
void sendInfo(const std::string &meminfo_str, const std::string &process_json) {
  while (1) {

    send_To_BMC(meminfo_str, "127.0.0.1", 12345);
    sleep(3);

    send_To_BMC(process_json, "127.0.0.1", 12345);

    sleep(10);
  }
}