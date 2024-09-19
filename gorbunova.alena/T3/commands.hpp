#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iostream>
#include "polygon.hpp"

namespace gorbunova
{
  std::ostream &areaCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons);
  std::ostream &maxCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons);
  std::ostream &minCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons);
  std::ostream &countCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons);
  std::ostream &maxseqCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons);
  std::ostream &echoCommand(std::istream &input, std::ostream &output, std::vector< Polygon > &polygons);
}

#endif
