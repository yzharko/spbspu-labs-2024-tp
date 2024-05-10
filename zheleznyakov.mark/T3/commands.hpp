#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ios>
#include "geometry.hpp"
namespace zheleznyakov
{
  namespace commands
  {
    std::ostream & area(const std::vector < Polygon > &, std::istream &, std::ostream &);
  }
}
#endif
