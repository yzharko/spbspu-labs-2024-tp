#ifndef TASKTYPES_HPP
#define TASKTYPES_HPP
#include <string>

namespace psarev
{
  struct intIO
  {
    int& ref;
  };

  std::istream& operator>>(std::istream& in, intIO&& dest);
}

#endif