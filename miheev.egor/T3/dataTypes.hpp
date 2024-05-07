#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <ios>
namespace miheev
{
  struct IntIO
  {
    int& ref;
  };
  struct SizeTIO
  {
    size_t& ref;
  };
  std::istream& operator>>(std::istream& in, IntIO&&);
  std::istream& operator>>(std::istream& in, SizeTIO&&);
}

#endif
