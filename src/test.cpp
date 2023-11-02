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

  std::ifstream file("Procps.txt");

  std::string rr = "";
  std::string str = "Hello, world!";
                  // 0123456789
  std::string substr1 = str.substr(7); // 从位置7开始截取到结尾
  std::string substr2 = str.substr(7, 5); // 从位置7开始截取长度为5的子串

  std::cout << "Substring 1: " << substr1 << std::endl;
  std::cout << "Substring 2: " << substr2 << std::endl;

  return 0;
}