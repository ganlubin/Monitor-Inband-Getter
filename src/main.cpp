#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
#include "Boost_process.hpp"
#include "Procps.hpp"
#include "tools.hpp"
#include "jsonPackage.hpp"
#include "Meminfo_Getter.hpp"
#include <fstream>

int main() {
  json meminfo = meminfo_getter();
  std::ofstream output("meminfo.json");
  output << meminfo;
  boost_process("/home/sokee/Desktop/Monitor-Inband-Getter/src");
  procps("/home/sokee/Desktop/Monitor-Inband-Getter/src/Procps.txt");
  create_info_json();
  return 0;
}