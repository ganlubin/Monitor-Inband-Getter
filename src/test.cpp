#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

int main() {
  std::ifstream file("Boost_process_info_process.txt");
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string str = buffer.str();
  int idx = 0;
  for (;; idx++) {
    if (str[idx] == 0x0A) {
      std::cout << idx << std::endl;
      std::cout << str[idx + 1] << str[idx + 2] << str[idx + 3] << str[idx + 4]
                << std::endl;
      break;
    }
  }
  return 0;
}