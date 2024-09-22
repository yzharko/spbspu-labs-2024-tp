#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP
#include <complex>

namespace redko
{
  struct LongLongIO
  {
    long long & ref;
  };

  struct ComplexIO
  {
    std::complex< double > & ref;
  };

  struct StringIO
  {
    std::string & ref;
  };

  std::istream & operator>>(std::istream & in, LongLongIO && dest);
  std::istream & operator>>(std::istream & in, ComplexIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
}

#endif
