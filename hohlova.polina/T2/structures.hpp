#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

namespace hohlova
{
  using real = std::pair<long long, unsigned long long>;
  using sll = long long;
  using ull = unsigned long long;

  struct Data
  {
    sll key1;
    std::pair<sll, ull> key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string exp;
  };
  struct SLLLitIO
  {
    long long& ref;
  };
  struct ULLLitIO
  {
    unsigned long long& ref;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, Data& dest);
  std::istream& operator>>(std::istream& in, SLLLitIO&& dest);
  std::istream& operator>>(std::istream& in, ULLLitIO&& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);

  bool operator<(const Data& left, const Data& right);
}

#endif
