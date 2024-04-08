#ifndef HELPSTRUCTS_HPP
#define HELPSTRUCTS_HPP

#include <iosfwd>
#include <string>

namespace sobolevsky
{
  struct Delimitr_
  {
    char expected;
  };

  struct Double_
  {
    double &key1_;
  };

  struct Char_
  {
    char &key2_;
  };

  struct String_
  {
    std::string &key3_;
  };

  std::istream & operator>>(std::istream & in, Delimitr_ && exp);
  std::istream & operator>>(std::istream & in, Double_ && exp);
  std::istream & operator>>(std::istream & in, Char_ && exp);
  std::istream & operator>>(std::istream & in, String_ && exp);
}

#endif
