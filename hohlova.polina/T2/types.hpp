#ifndef TYPES_HPP
#define TYPES_HPP
#include <iosfwd>
#include <utility>
#include <complex>

namespace hohlova
{
  using real = std::pair< long long, unsigned long long >;

  struct RealIO
  {
    real& ref;
  };

  struct ComplexIO
  {
    std::complex< double >& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, RealIO&& dest);
  std::istream& operator>>(sta::istream& in, ComplexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
