#include "Meminfo_Getter.hpp"
#include "json.hpp"
#include <fstream>
#include <iostream>

void addKeyToJson(nlohmann::json &, const std::string &);

nlohmann::json meminfo_getter() { // kB
  std::ifstream meminfo("/proc/meminfo");
  nlohmann::json json;
  std::string key = "";
  while (std::getline(meminfo, key)) {
    addKeyToJson(json, key);
  }
  return json;
}

void addKeyToJson(nlohmann::json &json, const std::string &key) {
  std::string first = "";
  std::string second = "";
  int idx = 0;
  for (; key[idx] != ':'; ++idx) {
    first += key[idx];
  }

  // jump over the space
  for (; !(key[idx] >= '0' && key[idx] <= '9'); ++idx) {
  }

  for (; key[idx] >= '0' && key[idx] <= '9' && idx < key.size(); ++idx) {
    second += key[idx];
  }
  json[first] = second;
}
