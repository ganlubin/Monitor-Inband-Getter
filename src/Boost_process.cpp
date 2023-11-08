#include <boost/process.hpp>
namespace bp = boost::process;
#include "Boost_process.hpp"
#include "tools.hpp"
#include <filesystem>
#include <iostream>
int boost_process(const std::string &addr) {

  std::string process_addr = addr + "/Boost_process_info_process.txt";
  std::string system_addr = addr + "/Boost_process_info_system.txt";

  // check if files exist
  int r = check_file_exist_delete(process_addr);
  r = check_file_exist_delete(system_addr);

  // system'info
  bp::ipstream system_info_stream;
  bp::child system_info_child("top -b -n 1", bp::std_out > system_info_stream);
  std::string system_info;
  while (std::getline(system_info_stream, system_info) &&
         !system_info.empty()) {
    write_to_file(system_info + '\n', system_addr, 'a');
  }

  // processes'info
  bp::ipstream process_info_stream;
  bp::child process_info_child("ps aux", bp::std_out > process_info_stream);
  std::string process_info;
  while (std::getline(process_info_stream, process_info) &&
         !process_info.empty()) {
    write_to_file(process_info + '\n', process_addr, 'a');
  }

  return 0;
}
