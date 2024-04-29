#ifndef KEYSTRUCT_HPP
#define KEYSTRUCT_HPP
#include <string>
#include <iosfwd>
#include <iostream>

namespace sukacheva
{
  struct String
  {
    std::string& val;
  };

  struct SllLit
  {
    long long& val;
  };

  struct DblLit
  {
    double& val;
  };

  std::istream& operator>>(std::istream& is, String&& value);
  std::istream& operator>>(std::istream& is, SllLit&& value);
  std::istream& operator>>(std::istream& is, DblLit&& value);
}

#endif
