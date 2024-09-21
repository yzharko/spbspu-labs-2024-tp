#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iosfwd>
#include <string>

namespace khomichenko
{

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct SllIO
  {
    long long &ref;
  };


  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, SllIO &&dest);
  std::ostream &sciDouble (std::ostream &out, double num);
}

#endif
