#include <iomanip>
#include "data-types.hpp"

namespace zheleznyakov
{
  struct Data
  {
    double key1;
    real key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &src);

  bool operator<(const Data& left, const Data& right);
}
