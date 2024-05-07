#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <ios>
#include "geometry.hpp"

namespace miheev
{
  std::ostream& areaCommand(std::istream&, std::ostream&, const std::vector< Polygon >&);
  std::ostream& maxCommand(std::istream&, std::ostream&, const std::vector< Polygon >&);
  std::ostream& minCommand(std::istream&, std::ostream&, const std::vector< Polygon >&);
  std::ostream& countCommand(std::istream&, std::ostream&, const std::vector< Polygon >&);
  std::ostream& maxseqCommand(std::istream&, std::ostream&, const std::vector< Polygon >&);
  std::ostream& rightshapesCommand(std::istream&, std::ostream&, const std::vector< Polygon >&);
  std::ostream& sendMessage(std::ostream&, const std::string& message);
  std::ostream& sendMessage(std::ostream&, double message);
}

#endif
