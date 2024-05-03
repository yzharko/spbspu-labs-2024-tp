#ifndef TYPES_HPP
#define TYPES_HPP
#include <iosfwd>
#include <utility>
#include <complex>

namespace hohlova
{
  using real = std::pair< long long, unsigned long long >;

  struct DoubleIO
  {
    double& ref;
  };

  struct RealIO
  {
    real& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct ComplexIO
  {
    std::complex< double >& ref;
  }
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, RealIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, ComplexIO&& dest);
}

#endif
