#include "jsonPackage.hpp"
#include "json.hpp"
#include "tools.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

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
void process_info(std::ifstream &, std::ifstream &, json &);

void readProcess_boost(const std::string &, PROC_INFO &);
void write_process_t_json(const PROC_INFO &, json &);
void readProcess_procps(std::ifstream &, PROC_INFO &);

int create_info_json() {
  // clear cached file
  check_file_exist_delete(
      "/home/sokee/Desktop/Monitor-Inband-Getter/src/resources.json");

  std::ifstream Boost_process_info_process(
      "/home/sokee/Desktop/Monitor-Inband-Getter/src/"
      "Boost_process_info_process.txt");
  std::ifstream Boost_process_info_system(
      "/home/sokee/Desktop/Monitor-Inband-Getter/src/"
      "Boost_process_info_system.txt");
  std::ifstream Procps(
      "/home/sokee/Desktop/Monitor-Inband-Getter/src/Procps.txt");

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
  process_info(Boost_process_info_process, Procps, json_info);

  // output file
  r = output_json(json_info);
  if (!r) {
    printError("output json file failed.\n");
    return 0;
  }

  return 1;
}

void process_info(std::ifstream &Boost_process_info_process,
                  std::ifstream &Procps, json &json_info) {

  std::string key_boost = "";
  std::getline(Boost_process_info_process, key_boost);
  while (std::getline(Boost_process_info_process, key_boost)) {

    PROC_INFO proc_temp;

    // boost
    readProcess_boost(key_boost, proc_temp);

    // Procps
    readProcess_procps(Procps, proc_temp);

    // write to json file
    write_process_t_json(proc_temp, json_info);
  }

  // std::string key = "";
  // std::getline(Boost_process_info_process, key);

  // std::getline(Boost_process_info_process, key);
  // PROC_INFO proc_temp;
  // while (std::getline(Boost_process_info_process, key)) {
  //   readProcess(key, proc_temp, proc_vector);
  // }
}

void readProcess_procps(std::ifstream &Procps, PROC_INFO &proc_temp) {

  std::string key = "";

  // tid check
  std::getline(Procps, key);
  if (key.substr(0, 3) != "tid" ||
      key.find_first_not_of(' ') == std::string::npos) {
    return;
  }

  // ppid
  std::getline(Procps, key);
  proc_temp.ppid = atoi(key.substr(6).c_str());

  // maj_delta
  std::getline(Procps, key);
  proc_temp.maj_delta = std::stoul(key.substr(11).c_str());

  // min_delta
  std::getline(Procps, key);
  proc_temp.min_delta = std::stoul(key.substr(11).c_str());

  // pcpu
  std::getline(Procps, key);
  proc_temp.pcpu = static_cast<unsigned int>(std::stoul(key.substr(6).c_str()));

  // state
  std::getline(Procps, key);
  proc_temp.state = static_cast<char>(atoi(key.substr(7).c_str()));

  // utime
  std::getline(Procps, key);
  proc_temp.utime = std::stoull(key.substr(7).c_str());

  // stime
  std::getline(Procps, key);
  proc_temp.stime = std::stoull(key.substr(7).c_str());

  // cutime
  std::getline(Procps, key);
  proc_temp.cutime = std::stoull(key.substr(8).c_str());

  // cstime
  std::getline(Procps, key);
  proc_temp.cstime = std::stoull(key.substr(8).c_str());

  // start_time
  std::getline(Procps, key);
  proc_temp.start_time = std::stoull(key.substr(12).c_str());

  // start_code
  std::getline(Procps, key);
  proc_temp.start_code = std::stoul(key.substr(12).c_str());

  // end_code
  std::getline(Procps, key);
  proc_temp.end_code = std::stoul(key.substr(10));

  // start_stack
  std::getline(Procps, key);
  proc_temp.start_stack = std::stoul(key.substr(13));

  // kstk_esp
  std::getline(Procps, key);
  proc_temp.kstk_esp = std::stoul(key.substr(10));

  // kstk_eip
  std::getline(Procps, key);
  proc_temp.kstk_eip = std::stoul(key.substr(10));

  // wchan
  std::getline(Procps, key);
  proc_temp.wchan = std::stoul(key.substr(7));

  // priority
  std::getline(Procps, key);
  proc_temp.priority = std::atol(key.substr(10).c_str());

  // nice
  std::getline(Procps, key);
  proc_temp.nice = std::atol(key.substr(6).c_str());

  // rss
  std::getline(Procps, key);
  proc_temp.rss = std::atol(key.substr(5).c_str());

  // alarm
  std::getline(Procps, key);
  proc_temp.alarm = std::atol(key.substr(7).c_str());

  // size
  std::getline(Procps, key);
  proc_temp.size = std::atol(key.substr(6).c_str());

  // resident
  std::getline(Procps, key);
  proc_temp.resident = std::atol(key.substr(10).c_str());

  // share
  std::getline(Procps, key);
  proc_temp.share = std::atol(key.substr(7).c_str());

  // trs
  std::getline(Procps, key);
  proc_temp.trs = std::atol(key.substr(5).c_str());

  // lrs
  std::getline(Procps, key);
  proc_temp.lrs = std::atol(key.substr(5).c_str());

  // drs
  std::getline(Procps, key);
  proc_temp.drs = std::atol(key.substr(5).c_str());

  // dt
  std::getline(Procps, key);
  proc_temp.dt = std::atol(key.substr(4).c_str());

  // vm_size
  std::getline(Procps, key);
  proc_temp.vm_size = std::stoul(key.substr(9));

  // vm_lock
  std::getline(Procps, key);
  proc_temp.vm_lock = std::stoul(key.substr(9));

  // vm_rss
  std::getline(Procps, key);
  proc_temp.vm_rss = std::stoul(key.substr(8));

  // vm_rss_anon
  std::getline(Procps, key);
  proc_temp.vm_rss_anon = std::stoul(key.substr(13));

  // vm_rss_shared
  std::getline(Procps, key);
  proc_temp.vm_rss_shared = std::stoul(key.substr(15));

  // vm_data
  std::getline(Procps, key);
  proc_temp.vm_data = std::stoul(key.substr(9));

  // vm_stack
  std::getline(Procps, key);
  proc_temp.vm_stack = std::stoul(key.substr(10));

  // vm_swap
  std::getline(Procps, key);
  proc_temp.vm_swap = std::stoul(key.substr(9));

  // vm_exe
  std::getline(Procps, key);
  proc_temp.vm_exe = std::stoul(key.substr(8));

  // vm_lib
  std::getline(Procps, key);
  proc_temp.vm_lib = std::stoul(key.substr(8));

  // rtprio
  std::getline(Procps, key);
  proc_temp.rtprio = std::stoul(key.substr(8));

  // sched
  std::getline(Procps, key);
  proc_temp.sched = std::stoul(key.substr(7));

  // vsize
  std::getline(Procps, key);
  proc_temp.vsize = std::stoul(key.substr(7));

  // rss_rlim
  std::getline(Procps, key);
  proc_temp.rss_rlim = std::stoul(key.substr(10));

  // flags
  std::getline(Procps, key);
  proc_temp.flags = std::stoul(key.substr(7));

  // maj_flt
  std::getline(Procps, key);
  proc_temp.maj_flt = std::stoul(key.substr(9));

  // min_flt
  std::getline(Procps, key);
  proc_temp.min_flt = std::stoul(key.substr(9));

  // cmaj_flt
  std::getline(Procps, key);
  proc_temp.cmaj_flt = std::stoul(key.substr(10));

  // cmin_flt
  std::getline(Procps, key);
  proc_temp.cmin_flt = std::stoul(key.substr(10));

  // cmd
  std::getline(Procps, key);
  proc_temp.cmd = key.substr(5);

  // pgrp
  std::getline(Procps, key);
  proc_temp.pgrp = std::atoi(key.substr(6).c_str());

  // session
  std::getline(Procps, key);
  proc_temp.session = std::atoi(key.substr(9).c_str());

  // nlwp
  std::getline(Procps, key);
  proc_temp.nlwp = std::atoi(key.substr(6).c_str());

  // tgid
  std::getline(Procps, key);
  proc_temp.tgid = std::atoi(key.substr(6).c_str());

  // tty
  std::getline(Procps, key);
  proc_temp.tty = std::atoi(key.substr(5).c_str());

  // euid
  std::getline(Procps, key);
  proc_temp.euid = std::atoi(key.substr(6).c_str());

  // egid
  std::getline(Procps, key);
  proc_temp.egid = std::atoi(key.substr(6).c_str());

  // ruid
  std::getline(Procps, key);
  proc_temp.ruid = std::atoi(key.substr(6).c_str());

  // rgid
  std::getline(Procps, key);
  proc_temp.rgid = std::atoi(key.substr(6).c_str());

  // suid
  std::getline(Procps, key);
  proc_temp.suid = std::atoi(key.substr(6).c_str());

  // sgid
  std::getline(Procps, key);
  proc_temp.sgid = std::atoi(key.substr(6).c_str());

  // fuid
  std::getline(Procps, key);
  proc_temp.fuid = std::atoi(key.substr(6).c_str());

  // fgid
  std::getline(Procps, key);
  proc_temp.fgid = std::atoi(key.substr(6).c_str());

  // tpgid
  std::getline(Procps, key);
  proc_temp.tpgid = std::atoi(key.substr(7).c_str());

  // exit_signal
  std::getline(Procps, key);
  proc_temp.exit_signal = std::atoi(key.substr(13).c_str());

  // processor
  std::getline(Procps, key);
  proc_temp.processor = std::atoi(key.substr(11).c_str());

  // oom_score
  std::getline(Procps, key);
  proc_temp.oom_socre = std::atoi(key.substr(11).c_str());

  // oom_adj
  std::getline(Procps, key);
  proc_temp.oom_adj = std::atoi(key.substr(9).c_str());

  std::getline(Procps, key);
}

void readProcess_boost(const std::string &key, PROC_INFO &proc_temp) {
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
  process_entry["ppid"] = proc.ppid;
  process_entry["maj_delta"] = proc.maj_delta;
  process_entry["min_delta"] = proc.min_delta;
  process_entry["pcpu"] = proc.pcpu;
  process_entry["state"] = proc.state;
  process_entry["utime"] = proc.utime;
  process_entry["stime"] = proc.stime;
  process_entry["cutime"] = proc.cutime;
  process_entry["cstime"] = proc.cstime;
  process_entry["start_time"] = proc.start_time;
  process_entry["start_code"] = proc.start_code;
  process_entry["end_code"] = proc.end_code;
  process_entry["start_stack"] = proc.start_stack;
  process_entry["kstk_esp"] = proc.kstk_esp;
  process_entry["kstk_eip"] = proc.kstk_eip;
  process_entry["wchan"] = proc.wchan;
  process_entry["priority"] = proc.priority;
  process_entry["nice"] = proc.nice;
  process_entry["rss"] = proc.rss;
  process_entry["alarm"] = proc.alarm;
  process_entry["size"] = proc.size;
  process_entry["resident"] = proc.resident;
  process_entry["share"] = proc.share;
  process_entry["trs"] = proc.trs;
  process_entry["lrs"] = proc.lrs;
  process_entry["drs"] = proc.drs;
  process_entry["dt"] = proc.dt;
  process_entry["vm_size"] = proc.vm_size;
  process_entry["vm_lock"] = proc.vm_lock;
  process_entry["vm_rss"] = proc.rss;
  process_entry["vm_rss_anon"] = proc.vm_rss_anon;
  process_entry["vm_rss_shared"] = proc.vm_rss_shared;
  process_entry["vm_data"] = proc.vm_data;
  process_entry["vm_stack"] = proc.vm_stack;
  process_entry["vm_swap"] = proc.vm_swap;
  process_entry["vm_exe"] = proc.vm_exe;
  process_entry["vm_lib"] = proc.vm_lib;
  process_entry["rtprio"] = proc.rtprio;
  process_entry["sched"] = proc.sched;
  process_entry["vsize"] = proc.vsize;
  process_entry["rss_rlim"] = proc.rss_rlim;
  process_entry["flags"] = proc.flags;
  process_entry["maj_flt"] = proc.maj_flt;
  process_entry["min_flt"] = proc.min_flt;
  process_entry["cmaj_flt"] = proc.cmaj_flt;
  process_entry["cmin_flt"] = proc.cmin_flt;
  process_entry["cmd"] = proc.cmd;
  process_entry["pgrp"] = proc.pgrp;
  process_entry["session"] = proc.session;
  process_entry["nlwp"] = proc.nlwp;
  process_entry["tgid"] = proc.tgid;
  process_entry["tty"] = proc.tty;
  process_entry["euid"] = proc.euid;
  process_entry["egid"] = proc.egid;
  process_entry["ruid"] = proc.ruid;
  process_entry["rgid"] = proc.rgid;
  process_entry["suid"] = proc.suid;
  process_entry["sgid"] = proc.sgid;
  process_entry["fuid"] = proc.fuid;
  process_entry["fgid"] = proc.fgid;
  process_entry["tpgid"] = proc.tpgid;
  process_entry["exit_signal"] = proc.exit_signal;
  process_entry["processor"] = proc.processor;
  process_entry["oom_score"] = proc.oom_socre;
  process_entry["oom_adj"] = proc.oom_adj;

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