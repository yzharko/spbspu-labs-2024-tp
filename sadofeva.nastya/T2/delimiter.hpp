#ifndef DELIMITER_HPP
#define DELIMIER_HPP
#include <string>

namespace sadofeva
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
