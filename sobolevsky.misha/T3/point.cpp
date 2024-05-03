#include "point.hpp"
#include "../common/helpStructs.hpp"
#include <algorithm>

std::istream& sobolevsky::operator>>(std::istream& in, sobolevsky::Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = sobolevsky::Delimitr_;
  in >> del{'('} >> point.x >> del{';'} >> point.y >> del{')'};
  return in;
}
