#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

json create_info_json() {
  // json j; // 首先创建一个空的json对象
  // j["pi"] = 3.141;
  // j["happy"] = true;
  // j["name"] = "Niels";
  // j["nothing"] = nullptr;
  // j["answer"]["everything"] = 42; // 初始化answer对象
  // j["list"] = {1, 0, 2}; // 使用列表初始化的方法对"list"数组初始化
  // j["object"] = {{"currency", "USD"}, {"value", 42.99}}; // 初始化object对象

  // std::cout << j << std::endl;

  // input Boost_process_info_process.txt, Boost_process_info_system.txt,
  // Procps.txt

  std::ifstream Boost_process_info_process("Boost_process_info_process.txt");
  std::ifstream Boost_process_info_system("Boost_process_info_system.txt");
  std::ifstream Procps("Procps.txt");

  if (!Boost_process_info_process) {
    std::cerr << "Miss file: Boost_process_info_process.txt" << std::endl;
    return -1;
  }

  if (!Boost_process_info_system) {
    std::cerr << "Miss file: Boost_process_info_system.txt" << std::endl;
    return -1;
  }

  if (!Procps) {
    std::cerr << "Miss file: Procps.txt" << std::endl;
    return -1;
  }

  nlohmann::json j;
  j["name"] = "John";
  j["age"] = 30;
  j["address"] = {{"street", "123 Main Street"}, {"city", "New York"}};

    return 0;
}