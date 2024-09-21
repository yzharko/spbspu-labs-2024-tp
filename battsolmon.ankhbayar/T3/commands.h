#ifndef COMMANDS_H
#define COMMANDS_H
#include <functional>
#include <iostream>
#include <limits>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include "figures.h"
#include "io.h"
namespace std
{
  void area(const std::vector< std::Polygon >& vector, std::istream& in, std::ostream& out);
  void max(const std::vector< std::Polygon >& vector, std::istream& in, std::ostream& out);
  bool isUnsignedInt(const std::string& str);
  void min(const std::vector< std::Polygon >& vector, std::istream& in, std::ostream& out);
  void count(const std::vector< std::Polygon >& vector, std::istream& in, std::ostream& out);
  void inRects(const std::vector< std::Polygon >& vector, std::istream& in, std::ostream& out);
  void rmecho(std::vector< std::Polygon >& vector, std::istream& in, std::ostream& out);
}
#endif
