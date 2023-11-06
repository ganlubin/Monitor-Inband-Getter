#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

void read(std::ifstream &file) {
  std::string res = "";
  std::getline(file, res);
  std::cout << res << std::endl;
}

int main() {

  std::ifstream file("/proc/swaps");
  std::string s = "";

  while (std::getline(file, s)) {
    std::cout << s << std::endl;
  }

  return 0;
}