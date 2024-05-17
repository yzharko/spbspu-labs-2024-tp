#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <vector>
#include "dataStruct.hpp"

namespace gorbunova
{
  void cmdArea(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is);
  void cmdMax(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is);
  void cmdMin(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is);
  void cmdCount(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is);
  void cmdPerms(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is);
  void cmdInframe(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is);
  void printMessage(std::ostream &out, const std::string &message);
}

#endif
