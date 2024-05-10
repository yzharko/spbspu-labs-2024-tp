#ifndef COMAND_HPP
#define COMAND_HPP

#include <vector>
#include "polygon.hpp"

namespace taskaev
{
  void AreaComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
}
#endif
