#include "tools.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#define RESET "\033[0m"
#define RED "\033[31m"
/**
 * write string str to addr.
 * writetype: {
 *      a: add
 *      o: overwrite
 *    }
 */
int write_to_file(const std::string &str, const std::string &addr,
                  char writetype) {
  std::ofstream file;
  if (writetype == 'a') {
    file.open(addr, std::ios::out | std::ios::app);
  } else if (writetype == 'o') {
    file.open(addr, std::ios::out | std::ios::trunc);
  } else {
    std::cerr << "Invalid write type!" << std::endl;
    return -1;
  }

  if (!file.is_open()) {
    std::cerr << "Failed to open file!" << std::endl;
    return -1;
  }

  file << str;
  file.close();
  return 0;
}

/**
 * check_file_exist_delete
 * To check if the addr has cached file, if yeap, delete it.
 */
int check_file_exist_delete(const std::string &file) {

  if (std::filesystem::exists(file)) {
    std::cout << "Delete cached file: " << file << std::endl;
    std::error_code ec;                // 用于存储错误代码
    std::filesystem::remove(file, ec); // 删除文件
    if (ec) {
      std::cerr << "Error occurred while deleting the file: " << ec.message()
                << std::endl;
      return -1;
    } else {
      std::cout << "File deleted successfully." << std::endl;
    }
  }

  return 1;
}

void printError(const std::string &error) {
  std::cerr << RED << error << RESET << std::endl;
}