#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <iosfwd>

namespace sukacheva
{
  struct Delimeter
  {
    char del;
  };
  std::istream& operator>>(std::istream& is, Delimeter&& val);
}

#endif
