#ifndef LIST2_0_DELIMITERS_HPP
#define LIST2_0_DELIMITERS_HPP
#include <iostream>

namespace litsinger
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
