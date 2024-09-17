#ifndef STRUCTURESOFKEYS_HPP
#define STRUCTURESOFKEYS_HPP

#include <cstring>
#include <istream>

namespace malanin
{
  struct DoubleIO
  {
    std::string &ref;
  };

  struct LongLongIO
  {
    std::string &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct PairIO
  {
    std::pair< long long, unsigned long long > &ref;
  };

  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, LongLongIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, PairIO &&dest);
}

#endif
