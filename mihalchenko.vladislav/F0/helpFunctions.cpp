#include "helpFunctions.hpp"
#include <iostream>
#include <string>

std::string mihalchenko::getDictName(std::string &str)
{
  return str.substr(0, str.find(".txt"));
}
