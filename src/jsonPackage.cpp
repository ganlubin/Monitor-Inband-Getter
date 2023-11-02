#include "json.hpp"
#include "tools.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <cmath>

using json = nlohmann::json;

int output_json(const json &);
std::pair<std::string, int> findFromFile_system_info(const std::string &,
                                                     const std::string &);
int system_info(const std::ifstream &, json &);
int running_minutes(const std::pair<std::string, int> &);
int system_users(const std::pair<std::string, int> &);
void setSystem_load_average(json &, const std::pair<std::string, int> &);
void system_tasks(json &, const std::pair<std::string, int> &);
void system_cpus(json &, const std::pair<std::string, int> &);
void system_memory(json &, const std::pair<std::string, int> &);
void system_swap(json &, const std::pair<std::string, int> &);
int process_info(std::ifstream &, json &);

typedef struct proc {
  std::string USER;
  int PID;
  float CPU;
  float MEM;
  int VSZ;
  int RSS;
  std::string TTY;
  std::string STAT;
  std::string START;
  std::string TIME;
  std::string COMMAND;
} PROC_INFO;



void readProcess(const std::string &, PROC_INFO &, json &);
void write_process_t_json(const PROC_INFO &, json &);

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

  // system_info write
  json_info["system"] = {};
  int r = system_info(Boost_process_info_system, json_info);
  if (!r) {
    printError("Get system_info Error.");
    return 0;
  }

  // process_info write
  r = process_info(Boost_process_info_process, json_info);
  if (!r) {
    printError("Get process_info Error.");
    return 0;
  }

  // output file
  r = output_json(json_info);
  if (!r) {
    printError("output json file failed.\n");
    return 0;
  }

  return 1;
}

int process_info(std::ifstream &Boost_process_info_process, json &json_info) {

  std::string key = "";
  std::ofstream outputFile("output.txt", std::ios_base::app);
  std::getline(Boost_process_info_process, key);
  int size = 0;
  while (std::getline(Boost_process_info_process, key)) {
    size++;
  }

  

  Boost_process_info_process.clear();                 // reset ifstream
  Boost_process_info_process.seekg(0, std::ios::beg); // reset ifstream

  std::getline(Boost_process_info_process, key);
  PROC_INFO proc_temp;
  while (std::getline(Boost_process_info_process, key)) {
    readProcess(key, proc_temp, json_info);
  }
  return 1;
}

void readProcess(const std::string &key, PROC_INFO &proc_temp,
                 json &json_info) {
  int idx = 0;
  std::string temp = "";

  // USER
  for (; key[idx] != 0x20; idx++) {
    temp += key[idx];
  }
  proc_temp.USER = temp;
  temp = "";
  for (; !(key[idx] >= '0' && key[idx] <= '9'); idx++) {
  }

  // PID
  for (; key[idx] >= '0' && key[idx] <= '9'; idx++) {
    temp += key[idx];
  }
  proc_temp.PID = atoi(temp.c_str());
  temp = "";
  for (; !(key[idx] >= '0' && key[idx] <= '9'); idx++) {
  }

  // %CPU
  for (; key[idx] >= '0' && key[idx] <= '9' || key[idx] == '.'; idx++) {
    temp += key[idx];
  }
  float cpu_val = atof(temp.c_str());
  float cpu_rounded_val = std::round(cpu_val * 100.0) / 100.0;
  proc_temp.CPU = cpu_rounded_val;
  temp = "";
  for (; !(key[idx] >= '0' && key[idx] <= '9'); idx++) {
  }

  // %MEM
  for (; key[idx] >= '0' && key[idx] <= '9' || key[idx] == '.'; idx++) {
    temp += key[idx];
  }
  float mem_val = atof(temp.c_str());
  float mem_rounded_val = std::round(mem_val * 100.0) / 100.0;
  proc_temp.MEM = mem_rounded_val;
  temp = "";
  for (; !(key[idx] >= '0' && key[idx] <= '9'); idx++) {
  }

  // VSZ
  for (; key[idx] >= '0' && key[idx] <= '9'; idx++) {
    temp += key[idx];
  }
  proc_temp.VSZ = atoi(temp.c_str());
  temp = "";
  for (; !(key[idx] >= '0' && key[idx] <= '9'); idx++) {
  }

  // RSS
  for (; key[idx] >= '0' && key[idx] <= '9'; idx++) {
    temp += key[idx];
  }
  proc_temp.RSS = atoi(temp.c_str());
  temp = "";
  for (; key[idx] == 0x20; idx++) {
  }

  // TTY
  for (; key[idx] != 0x20; idx++) {
    temp += key[idx];
  }
  proc_temp.TTY = temp;
  temp = "";
  for (; key[idx] == 0x20; idx++) {
  }

  // STAT
  for (; key[idx] != 0x20; idx++) {
    temp += key[idx];
  }
  proc_temp.STAT = temp;
  temp = "";
  for (; !(key[idx] >= '0' && key[idx] <= '9'); idx++) {
  }

  // START
  for (; key[idx] >= '0' && key[idx] <= '9' || key[idx] == ':'; idx++) {
    temp += key[idx];
  }
  proc_temp.START = temp;
  temp = "";
  for (; key[idx] == 0x20; idx++) {
  }

  // TIME
  for (; key[idx] >= '0' && key[idx] <= '9' || key[idx] == ':'; idx++) {
    temp += key[idx];
  }
  proc_temp.TIME = temp;
  temp = "";
  for (; key[idx] == 0x20; idx++) {
  }

  // COMMAND
  for (; idx < key.size(); idx++) {
    temp += key[idx];
  }
  proc_temp.COMMAND = temp;



  // write to json file
  // write_process_t_json(proc_temp, json_info);
}

void write_process_t_json(const PROC_INFO &proc, json &json_info) {
  json process_entry;
  process_entry["USER"] = proc.USER;
  process_entry["PID"] = proc.PID;
  process_entry["%CPU"] = proc.CPU;
  process_entry["%MEM"] = proc.MEM;
  process_entry["VSZ"] = proc.VSZ;
  process_entry["RSS"] = proc.RSS;
  process_entry["TTY"] = proc.TTY;
  process_entry["STAT"] = proc.STAT;
  process_entry["START"] = proc.START;
  process_entry["TIME"] = proc.TIME;
  process_entry["COMMAND"] = proc.COMMAND;
  json_info["processes"].push_back(process_entry);
}

int system_info(const std::ifstream &Boost_process_info_system,
                json &json_info) {
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
  if (temp.second == -1) {
    printError("Could not find key string: load average");
    return 0;
  }
  setSystem_load_average(json_info, temp); // 1 5 15 minutes

  // system tasks
  key = "Tasks";
  temp = findFromFile_system_info(Boost_process_info_system_content, key);
  if (temp.second == -1) {
    printError("Could not find key string: Tasks");
    return 0;
  }
  system_tasks(json_info, temp);

  // system CPUs
  key = "Cpu(s):";
  temp = findFromFile_system_info(Boost_process_info_system_content, key);
  if (temp.second == -1) {
    printError("Could not find key string: Cpu(s)");
    return 0;
  }
  system_cpus(json_info, temp);

  // system Mem
  key = "MiB Mem :";
  temp = findFromFile_system_info(Boost_process_info_system_content, key);
  if (temp.second == -1) {
    printError("Could not find key string: MiB Mem");
    return 0;
  }
  system_memory(json_info, temp);

  // system Swap
  key = "MiB Swap:";
  temp = findFromFile_system_info(Boost_process_info_system_content, key);
  if (temp.second == -1) {
    printError("Could not find key string: MiB Swap");
    return 0;
  }
  system_swap(json_info, temp);

  return 1;
}

void system_swap(json &json_info, const std::pair<std::string, int> &temp) {
  std::string source = temp.first;
  int idx = temp.second;
  std::string res = "";

  // total
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  json_info["system"]["Swap(MiB)"]["total"] = atof(res.c_str());
  res = "", idx++;

  // free
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  json_info["system"]["Swap(MiB)"]["free"] = atof(res.c_str());
  res = "", idx++;

  // used
  for (; source[idx] != 'u'; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  json_info["system"]["Swap(MiB)"]["used"] = atof(res.c_str());
  res = "", idx += 5;

  // avail
  for (; source[idx] != 'a'; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  json_info["system"]["Swap(MiB)"]["avail"] = atof(res.c_str());
  return;
}

void system_memory(json &json_info, const std::pair<std::string, int> &temp) {
  std::string source = temp.first;
  int idx = temp.second;
  std::string res = "";

  // total
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  json_info["system"]["physical memory(MiB)"]["total"] = atof(res.c_str());
  idx++, res = "";

  // free
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  json_info["system"]["physical memory(MiB)"]["free"] = atof(res.c_str());
  idx++, res = "";

  // used
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  json_info["system"]["physical memory(MiB)"]["used"] = atof(res.c_str());
  idx++, res = "";

  // buff/cache
  for (; source[idx] != 'b'; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  json_info["system"]["physical memory(MiB)"]["buff/cache"] = atof(res.c_str());
  return;
}

void system_cpus(json &json_info, const std::pair<std::string, int> &temp) {
  std::string source = temp.first;
  int idx = temp.second;
  std::string res = "";

  // user
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Cpu(s)"]["user"] = atof(res.c_str());
  res = "";

  // system
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Cpu(s)"]["system"] = atof(res.c_str());
  res = "";

  // niced
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Cpu(s)"]["nice"] = atof(res.c_str());
  res = "";

  // idle
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Cpu(s)"]["idle"] = atof(res.c_str());
  res = "";

  // IO wait
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Cpu(s)"]["IO wait"] = atof(res.c_str());
  res = "";

  // hardware IRQ usage
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Cpu(s)"]["hardware IRQ"] = atof(res.c_str());
  res = "";

  // software IRQ
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Cpu(s)"]["software IRQ"] = atof(res.c_str());
  res = "";

  // hpyervisor
  for (; source[idx] != 's'; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Cpu(s)"]["hpyervisor"] = atof(res.c_str());
}

void system_tasks(json &json_info, const std::pair<std::string, int> &temp) {
  std::string source = temp.first;
  int idx = temp.second + 1;
  std::string res = "";

  // total
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Tasks"]["total"] = atoi(res.c_str());
  res = "";

  // running
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Tasks"]["running"] = atoi(res.c_str());
  res = "";

  // sleeping
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Tasks"]["sleeping"] = atoi(res.c_str());
  res = "";

  // stopped
  for (; source[idx] != ','; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9') {
      res += source[idx];
    }
  }
  idx++;
  json_info["system"]["Tasks"]["stopped"] = atoi(res.c_str());
  res = "";

  // zombie
  for (; source[idx] != 'z'; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9') {
      res += source[idx];
    }
  }
  json_info["system"]["Tasks"]["zombie"] = atoi(res.c_str());
}

void setSystem_load_average(json &json_info,
                            const std::pair<std::string, int> &temp) {
  std::string source = temp.first;
  int idx = temp.second + 1;
  std::string res = "";
  for (;; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
    if (source[idx] == ',') {
      idx++;
      break;
    }
  }
  json_info["system"]["1 min load average"] = atof(res.c_str());
  res = "";

  for (;; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    }
    if (source[idx] == ',') {
      idx += 2;
      break;
    }
  }
  json_info["system"]["5 min load average"] = atof(res.c_str());
  res = "";

  for (;; idx++) {
    if (source[idx] >= '0' && source[idx] <= '9' || source[idx] == '.') {
      res += source[idx];
    } else {
      json_info["system"]["15 min load average"] = atof(res.c_str());
      return;
    }
  }
  return;
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