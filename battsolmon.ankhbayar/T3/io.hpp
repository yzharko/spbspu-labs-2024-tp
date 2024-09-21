#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include "figure.hpp"

namespace std
{
  std::istream& operator>>(std::istream& in, std::Point& poly);
  std::istream& operator>>(std::istream& in, std::Polygon& poly);
  std::ostream& operator<<(std::ostream& out, const std::Point& point);
  bool isPoint(std::string& str);
}
#endif
