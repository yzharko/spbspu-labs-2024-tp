#ifndef TASKTYPES_HPP
#define TASKTYPES_HPP
#include <string>

namespace psarev
{
  struct DoubleIO
  {
    double& ref;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif