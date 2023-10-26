#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
#include "Boost_process.hpp"
#include "Procps.hpp"
#include "tools.hpp"
#include "jsonPackage.hpp"

int main() {
  create_info_json();
  // boost_process("/home/sokee/Desktop/Monitor-Inband-Getter/src");
  return 0;
}