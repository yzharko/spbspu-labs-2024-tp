#ifndef DELIMITERS_HPP
#define DELIMITERS_HPP

#include <iostream>

namespace malanin
{
  struct DelimiterIO
  {
    char expected;
  };
  struct LabelIO
  {
    std::string exp;
  };
  struct KeyIO
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream& is, DelimiterIO&&);
  std::istream& operator>>(std::istream &in, LabelIO&&);
  std::istream& operator>>(std::istream &in, KeyIO&&);
}

#endif
