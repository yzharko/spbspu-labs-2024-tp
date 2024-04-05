#ifndef HELPSTRUCTS_HPP
#define HELPSTRUCTS_HPP

#include <iostream>
#include <string>

namespace sobolevsky
{
  struct Delimitr
  {
    char expected = 0;
  };

  struct Double_
  {
    double dbl;
  };

  struct Char_
  {
    char ch;
  };

  struct String_
  {
    std::string str;
  };

std::istream & operator>>(std::istream & in, sobolevsky::Delimitr && exp);
}

#endif
