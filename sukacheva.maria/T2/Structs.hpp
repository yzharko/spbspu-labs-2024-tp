#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <iosfwd>
#include <string>

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

  std::istream& operator>>(std::istream& is, LongLongLit&& val);
  std::istream& operator>>(std::istream& is, DoubleLit&& val);
  std::istream& operator>>(std::istream& is, String&& val);
}

#endif