#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP
#include <istream>

namespace tellez
{
  template < bool IgnoreCase >
  struct CharDelimiterI
  {
    char expected;
  };

  template < bool IgnoreCase >
  std::istream& operator>>(std::istream& in, const CharDelimiterI< IgnoreCase >& exp)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char ch{};
    in >> ch;
    if (((ch != exp.expected) && !IgnoreCase) || (std::tolower(ch) != std::tolower(exp.expected)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  using StrictCaseCharDelimiterI = CharDelimiterI< false >;
}

#endif
