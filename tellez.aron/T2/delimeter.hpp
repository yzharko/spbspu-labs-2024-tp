#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <iosfwd>
#include <istream>

namespace tellez
{
  struct Delimeterchar
  {
    char expected;
  };

  struct Delimeterstring
  {
    const char* expected;
  };

  struct Delimeterpair
  {
    char expected;
  };

  std::istream& operator>>(std::istream& in, Delimeterchar&& exp);
  std::istream& operator>>(std::istream& in, Delimeterstring&& exp);
  std::istream& operator>>(std::istream& in, Delimeterpair&& exp);
}

#endif
