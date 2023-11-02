#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
#include "Boost_process.hpp"
#include "Procps.hpp"
#include "tools.hpp"
#include "jsonPackage.hpp"

int main() {
  boost_process("/home/sokee/Desktop/Monitor-Inband-Getter/src");
  procps("/home/sokee/Desktop/Monitor-Inband-Getter/src/Procps.txt");
  create_info_json();
  return 0;
}