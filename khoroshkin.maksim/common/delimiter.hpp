#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <string>

namespace khoroshkin
{
  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double & ref;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long & ref;
  };

  struct StringIO
  {
    std::string & ref;
  };
}

#endif
