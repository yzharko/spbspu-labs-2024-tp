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

  struct //key2
  {
    //key2
  };

  struct StringIO
  {
    std::string &str;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && value);
  std::istream & operator>>(std::istream & in, UllLitIO && value);
  std::istream & operator>>(std::istream & in, /*key2*/ && value);
  std::istream & operator>>(std::istream & in, StringIO && value);

  using Del = DelimiterIO;
  using UllLit = UllLitIO;
  //key2
  using Str = StringIO;
}

#endif
