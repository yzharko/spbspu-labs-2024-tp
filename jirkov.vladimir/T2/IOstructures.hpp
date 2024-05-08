#ifndef IOSTRUCTURES_HPP
#define IOSTRUCTURES_HPP
#include <string>
#include <iosfwd>

namespace jirkov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct UllLitIO
  {
    unsigned long long &ref;
  };

  struct UllOctIO
  {
    unsigned long long &ref;
  };

  struct StringIO
  {
    std::string &str;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && value);
  std::istream & operator>>(std::istream & in, UllLitIO && value);
  std::istream & operator>>(std::istream & in, UllOctIO && value);
  std::istream & operator>>(std::istream & in, StringIO && value);

  using Del = DelimiterIO;
  using UllLit = UllLitIO;
  using UllOct = UllOctIO
  using Str = StringIO;
}

#endif
