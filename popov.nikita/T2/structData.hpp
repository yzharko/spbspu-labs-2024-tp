#ifndef STRUCTDATA_HPP
#define STRUCTDATA_HPP

#include <iostream>

namespace popov
{
  struct DoubleIO
  {
    double & num;
  };
  struct UnsLongLongIO
  {
    unsigned long long & num;
  };
  struct StringIO
  {
    std::string & num;
  };
  std::istream & operator>>(std::istream & in, DoubleIO && number);
  std::istream & operator>>(std::istream & in, UnsLongLongIO && number);
  std::istream & operator>>(std::istream & in, StringIO && number);
}

#endif
