#ifndef DELIMITERS_HPP
#define DELIMETERS_HPP

// #include <iostream>
#include <complex>
// #include <utility>
// #include <string>

namespace mihalchenko
{
  struct DelimiterIO
  {
    char expected;
  };

  struct UllBinIO
  {
    std::string &ref;
  };

  struct ComplexIO
  {
    std::complex<double> &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, UllBinIO &&dest);
  std::istream &operator>>(std::istream &in, ComplexIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
}

#endif
