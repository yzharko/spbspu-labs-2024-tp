#ifndef Delimeter_hpp
#define Delimeter_hpp
#include <iostream>

namespace reznikova
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & is, reznikova::Delimiter && exp);
}

#endif
