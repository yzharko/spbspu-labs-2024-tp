#ifndef POINT_HPP
#define POINT_HPP
#include <IOstructures.hpp>
#include <ScopeGuard.hpp>

namespace jirkov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& is, Point& value);
  std::ostream& operator<<(std::ostream& out, const Point& value);
}

#endif
