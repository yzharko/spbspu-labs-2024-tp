#include "polygon.hpp"
#include <iterator>
#include <algorithm>

std::istream& sobolevsky::operator>>(std::istream& in, sobolevsky::Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t vertexCount = 0;
  in >> vertexCount;
  if (vertexCount < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::cout << "penis\n";
  std::copy(std::istream_iterator< sobolevsky::Point >(in), std::istream_iterator< sobolevsky::Point >(), std::back_inserter(polygon.points));
  return in;
}
