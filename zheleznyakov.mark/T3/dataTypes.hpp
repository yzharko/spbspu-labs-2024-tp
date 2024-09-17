#ifndef DATATYPES_HPP
#define DATATYPES_HPP
#include <iomanip>
#include "separators.hpp"
namespace zheleznyakov
{
  struct IntIO
  {
    int &ref;
  };

  struct SizeTIO
  {
    size_t &ref;
  };

  std::istream & operator>>(std::istream & in, IntIO &&dest);
  std::istream & operator>>(std::istream & in, SizeTIO &&dest);
}
#endif
