#ifndef DELAND_HPP
#define DELAND_HPP

#include <iosfwd>
#include <string>

namespace susidko
{
  struct DelimiterI
  {
    char expected;
  };

  struct LongLong_
  {
    long long &key1_;
  };

  struct UnsignedLLBin_
  {
    unsigned long long &key2_;
  };

  struct String_
  {
    std::string &key3_;
  };

  std::istream & operator>>(std::istream & in, DelimiterI && exp);
  std::istream & operator>>(std::istream & in, LongLong_ && exp);
  std::istream & operator>>(std::istream & in, UnsignedLLBin_ && exp);
  std::istream & operator>>(std::istream & in, String_ && exp);
}

#endif
