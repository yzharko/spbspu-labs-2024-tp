#ifndef KEYS_HPP
#define KEYS_HPP
#include <string>
#include <complex>
#include <iostream>

namespace reznikova
{
  struct ULLOCT
  {
    unsigned long long int & num;
  };

  struct CMPLSP
  {
    std::complex< double > & num;
  };

  struct STR
  {
    std::string & num;
  };

  std::istream & operator>>(std::istream & is, ULLOCT && value);
  std::istream & operator>>(std::istream & is, CMPLSP && value);
  std::istream & operator>>(std::istream & is, STR && value);
}
#endif
