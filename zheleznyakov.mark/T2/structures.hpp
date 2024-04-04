#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

namespace zheleznyakov
{
  using real = std::pair< long long, unsigned long long >;

  struct Data
  {
    double key1;
    real key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

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

  struct LabelIO
  {
    std::string exp;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, RealIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &dest);

  bool operator<(const Data& left, const Data& right);
  bool operator<(const real &leftReal, const real &rightReal);
}