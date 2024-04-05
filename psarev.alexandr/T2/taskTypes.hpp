#ifndef TASKTYPES_HPP
#define TASKTYPES_HPP
#include <string>

namespace psarev
{
  struct DoubleIO
  {
    double& ref;
  };

  struct UllHexIO
  {
    unsigned long long& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, UllHexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
