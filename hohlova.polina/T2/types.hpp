#ifndef TYPES_HPP
#define TYPES_HPP
#include <iosfwd>
#include <utility>

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

  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, RealIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
