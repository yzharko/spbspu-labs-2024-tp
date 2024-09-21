#ifndef USERCOMMANDS_HPP
#define USERCOMMANDS_HPP
#include <iostream>
#include <string>
#include <map>
#include "HuffmanCode.hpp"
namespace redko
{
  void help(const std::string & descr);
  void code(const std::string & descr);
  void decode(const std::string & descr);
  void recode(const std::string & descr);
  void print(const std::string & command, HuffmanCode obj);
  void save(const std::string & command, const std::string & descr, HuffmanCode obj);
  void compare(const std::string & descr);
}

#endif
