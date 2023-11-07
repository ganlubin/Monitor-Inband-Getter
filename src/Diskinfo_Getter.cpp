#include "Diskinfo_Getter.hpp"

#include <iostream>
#include <fstream>

std::string diskinfo_getter() {
  std::ifstream diskinfo("/proc/diskstats");
  std::string res = "", temp = "";
  while (std::getline(diskinfo, temp)) {
    res += temp;
  }
  return res;
}