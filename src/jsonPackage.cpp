#include "json.hpp"
#include "tools.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

using json = nlohmann::json;

int output_json(const json &);
std::pair<std::string, int> findFromFile_system_info(const std::string &,
                                                     const std::string &);
int system_info(std::ifstream &, json &);
int running_minutes(const std::pair<std::string, int> &);
int system_users(const std::pair<std::string, int> &);

int create_info_json() {
  // clear cached file
  check_file_exist_delete("resources.json");

  std::ifstream Boost_process_info_process("Boost_process_info_process.txt");
  std::ifstream Boost_process_info_system("Boost_process_info_system.txt");
  std::ifstream Procps("Procps.txt");

  if (!Boost_process_info_process) {
    printError("Miss file: Boost_process_info_process.txt");
    return 0;
  }

  if (!Boost_process_info_system) {
    printError("Miss file: Boost_process_info_system.txt");
    return 0;
  }

  if (!Procps) {
    printError("Miss file: Procps.txt");
    return 0;
  }

  json json_info;
  json_info["system"] = {};

  int r = system_info(Boost_process_info_system, json_info);
  if (!r) {
    printError("Get system_info Error.\n");
    return 0;
  }

  r = output_json(json_info);
  if (!r) {
    printError("output json file failed.\n");
    return 0;
  }

  return 1;
}

int system_info(std::ifstream &Boost_process_info_system, json &json_info) {
  // explain the system_info
  std::string key;
  std::stringstream buffer;
  buffer << Boost_process_info_system.rdbuf();
  std::string Boost_process_info_system_content = buffer.str();
  // system time
  key = "top - ";
  std::pair<std::string, int> temp =
      findFromFile_system_info(Boost_process_info_system_content, key);
  if (temp.second == -1) {
    printError("Could not find key string: system time");
    return 0;
  }
  json_info["system"]["current time"] = temp.first.substr(temp.second, 8);

  // system_up time
  key = "up ";
  temp = findFromFile_system_info(Boost_process_info_system_content, key);
  if (temp.second == -1) {
    printError("Could not find key string: system_running_time");
    return 0;
  }
  json_info["system"]["system running time"] = running_minutes(temp);

  // system users number
  key = "user";
  temp = findFromFile_system_info(Boost_process_info_system_content, key);
  if (temp.second == -1) {
    printError("Could not find key string: system_users");
    return 0;
  }
  json_info["system"]["system users number"] = system_users(temp);

  // system load average
  key = "load average";
  temp = findFromFile_system_info(Boost_process_info_system_content, key);
  std::cout << temp.first[temp.second - 1] << std::endl;

  return 1;
}

std::pair<std::string, int> findFromFile_system_info(const std::string &source,
                                                     const std::string &key) {
  size_t pos = source.find(key);
  if (pos != std::string::npos) {
    return std::make_pair(source, static_cast<int>(pos) + key.size());
  }
  return std::make_pair("", -1);
}

int system_users(const std::pair<std::string, int> &temp) {
  std::string source = temp.first;
  int idx = temp.second - 1;
  std::string userstr = "";
  for (int i = idx; i >= 0; i--) {
    if (source[i] == ',') {
      for (int j = i + 1; source[j + 1] != 'u'; j++) {
        if (source[j] >= '0' && source[j] <= '9') {
          userstr += source[j];
        }
      }
      break;
    }
  }
  return atoi(userstr.c_str());
}

int running_minutes(const std::pair<std::string, int> &temp) {
  // temp.first = top - 14:53:47  1:06,  1 user, ......  temp.second = idx
  std::string source = temp.first;
  std::string minstr = "";
  int idx = temp.second;
  for (int i = idx; i < 10 + idx; i++) {
    if (source[i] == 'm' && source[i + 1] == 'i' && source[i + 2] == 'n') {
      for (int i = idx; i < 10 + idx; i++) {
        if (source[i] >= '0' && source[i] <= '9') {
          minstr += source[i];
        } else {
          break;
        }
      }
    }
  }
  if (strcmp(minstr.c_str(), "") == 0) { // ??:??
    int res = 0;
    std::string tt = "";
    int restart = 0;
    for (int i = idx; i < idx + 10; i++) {
      if (source[i] == ':') {
        restart = i + 1;
        break;
      }
      if (source[i] >= '0' && source[i] <= '9') {
        tt += source[i];
      }
    }
    res += atoi(tt.c_str()) * 60;
    tt = "";
    for (int i = restart; i < restart + 3; i++) {
      if (source[i] >= '0' && source[i] <= '9') {
        tt += source[i];
      }
    }
    res += atoi(tt.c_str());
    return res;
  }
  return atoi(minstr.c_str());
}

int output_json(const json &json_info) {
  std::ofstream file("resources.json");
  if (!file) {
    return 0;
  }
  file << json_info << std::endl;
  return 1;
}