#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <istream>

namespace lisitsyna
{
  struct Separator
  {
    char expected;
  };
  std::istream & operator>>(std::istream & in, Separator && exp);
}
#endif
