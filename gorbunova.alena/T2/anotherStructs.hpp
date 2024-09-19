#ifndef ANOTHERSTRUCTS_HPP
#define ANOTHERSTRUCTS_HPP
#include <complex>
#include <string>
#include <utility>

namespace gorbunova
{
  struct Complexx
  {
    std::complex< double > &ref;
  };

  struct Ratio
  {
    std::pair< long long, unsigned long long > &ref;
  };

  struct Str
  {
    std::string &ref;
  };

  struct Ull
  {
    unsigned long long &ref;
  };
}
#endif
