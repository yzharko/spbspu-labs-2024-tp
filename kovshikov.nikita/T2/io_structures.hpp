#ifndef IOSTRUCTURES_HPP
#define IOSTRUCTURES_HPP
#include <string>
#include <iosfwd>

namespace kovshikov
{
  struct DelimiterIO
  {
    char exp;
  };

  struct CharIO
  {
    char &ch;
  };

  struct PairIO
  {
    std::pair< long long, unsigned long long > pair;
  };

  struct StringIO
  {
    std::string &str;
  };

  struct SeparatorIO
  {
    std::string sep;
  };

  std::istream & operator>>(std::istream & is, DelimiterIO && value);
  std::istream & operator>>(std::istream & is, CharIO && value);
  std::istream & operator>>(std::istream & is, PairIO && value);
  std::istream & operator>>(std::istream & is, StringIO && value);
  std::istream & operator>>(std::istream & is, SeparatorIO && value);
  using Del = DelimiterIO;
  using Chr = CharIO;
  using Pair = PairIO;
  using Str = StringIO;
  using Sep = SeparatorIO;
}

#endif
