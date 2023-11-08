#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
#include "Boost_process.hpp"
#include "Meminfo_Getter.hpp"
#include "Procps.hpp"
#include "jsonPackage.hpp"
#include "tools.hpp"
#include <fstream>

int main() {
  // return /proc/meminfo json
  json meminfo = meminfo_getter();
  std::string meminfo_str = meminfo.dump();

  // get boost_process include system and processes, create files:
  // Boost_process_info_process.txt and Boost_process_info_system.txt
  std::string boost_addr =
      "/home/sokee/Desktop/Monitor-Inband-Getter/src"; /* plz write addr here */
  boost_process(boost_addr);

  // get Procps.txt: describe processes' details
  std::string procps_addr = "/home/sokee/Desktop/Monitor-Inband-Getter/src/Procps.txt";
  procps(procps_addr);

  // json
  std::string process_json = create_info_json(boost_addr, procps_addr);
  
  

  return 0;
}