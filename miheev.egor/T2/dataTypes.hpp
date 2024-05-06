#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <utility>
#include <string>

namespace miheev
{
  using real = std::pair<long long, unsigned long long>;

  struct LongLongIO
  {
    long long& ref;
  };
  struct RealIO
  {
    real& ref;
  };
  struct StringIO
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream &in, StringIO&&);
  std::istream& operator>>(std::istream &in, LongLongIO&&);
  std::istream& operator>>(std::istream &in, RealIO&&);
  std::ostream& operator<<(std::ostream& out, const real&);
  bool operator<(const miheev::real& lhs, const miheev::real& rhs);
}

#endif
