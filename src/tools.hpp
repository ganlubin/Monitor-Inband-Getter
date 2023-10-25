#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <fstream>
#include <iostream>

int write_to_file(const std::string &str, const std::string &addr,
                  char writetype);

int check_file_exist_delete(const std::string &file);

#endif