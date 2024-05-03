#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace sobolevsky
{
  void area(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
  void max(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
  void min(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
  void count(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
}

#endif