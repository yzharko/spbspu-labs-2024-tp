#ifndef TYPES_HPP
#define TYPES_HPP
#include <iosfwd>
#include <utility>
#include <complex>

namespace hohlova
{
  struct ULLIO
  {
    unsigned long long& ref;
  };

  struct ComplexIO
  {
    std::complex< double >& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, ULLIO&& dest);
  std::istream& operator>>(std::istream& in, ComplexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
