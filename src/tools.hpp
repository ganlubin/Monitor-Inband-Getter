#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <fstream>
#include <iostream>
#define RESET   "\033[0m"
#define RED     "\033[31m"
int write_to_file(const std::string &str, const std::string &addr,
                  char writetype);

int check_file_exist_delete(const std::string &file);

void printError(const std::string &error);



#endif