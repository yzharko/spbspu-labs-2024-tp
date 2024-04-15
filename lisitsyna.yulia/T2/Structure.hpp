#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <string>

struct Delimiter
{
  char exp;
};
struct Label
{
  std::string exp;
};

std::istream& operator>>(std::istream& in, Delimiter&& dest);
std::istream& operator>>(std::istream& in, Label&& dest);
#endif
