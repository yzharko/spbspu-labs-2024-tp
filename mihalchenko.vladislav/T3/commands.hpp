#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "functionsFormShapes.hpp"

namespace mihalchenko
{
  void printArea(const std::vector<Polygon> &polygons, std::istream &is, std::ostream &out);
  void printMax(const std::vector<Polygon> &polygons, std::istream &is, std::ostream &out);
  void printCount(const std::vector<Polygon> &polygons, std::istream &is, std::ostream &out);
  void printMin(const std::vector<Polygon> &polygons, std::istream &is, std::ostream &out);
  void printPerms(const std::vector<Polygon> &polygon, std::istream &is, std::ostream &out);
  void printCountRightShapes(const std::vector<Polygon> &polygons, std::istream &, std::ostream &out);
  std::ostream &printErrorMessage(const std::string &msg, std::ostream &out);
}

#endif
