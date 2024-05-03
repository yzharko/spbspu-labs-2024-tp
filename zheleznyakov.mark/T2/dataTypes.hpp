#include <string>
#include <iomanip>

namespace zheleznyakov
{
  using real = std::pair<long long, unsigned long long>;

  struct DoubleIO
  {
    double &ref;
  };

  struct RealIO
  {
    real &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, RealIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);

  bool operator<(const real &leftReal, const real &rightReal);
}
