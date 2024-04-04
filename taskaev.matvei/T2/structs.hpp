#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <iostream>
#include <complex>
#include <string>

namespace taskaev
{
  struct unsignedLongLongI
  {
    unsigned long long& ref;
  };

  struct complexI
  {
    std::complex< double >& ref;
  };

  struct stringI
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& is, unsignedLongLongI&& dest);
  std::istream& operator>>(std::istream& is, complexI&& dest);
  std::istream& operator>>(std::istream& is, stringI&& dest);
}
#endif
