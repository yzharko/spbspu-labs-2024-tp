#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <iostream>

namespace sukacheva {

  struct String
  {
    std::string & value;
  };

  struct DoubleLit
  {
    double & value;
  };

  struct LongLongLit
  {
    long long & value;
  };
}

#endif