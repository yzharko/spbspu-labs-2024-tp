#ifndef STRUCTURESOFKEYS_HPP
#define STRUCTURESOFKEYS_HPP

#include <cstring>
#include <istream>

namespace ponomarev
{
  struct DoubleIO
  {
    double &ref;
  };

  struct LongLongIO
  {
    std::string &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, LongLongIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
}

#endif
