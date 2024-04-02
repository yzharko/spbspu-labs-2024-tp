#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP
#include <complex>

namespace redko
{
  struct DataStruct
  {
    long long key1;
    std::complex< double > key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char expected;
  };

  struct LongLongIO
  {
    long long & ref;
  };

  struct ComplexIO
  {
    std::complex< double > & ref;
  };

  struct StringIO
  {
    std::string & ref;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, LongLongIO && dest);
  std::istream & operator>>(std::istream & in, ComplexIO && dest);
  std::istream & operator>>(std::istream & in, StringIO && dest);
  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & dest);

  bool operator<(const DataStruct & lhs, const DataStruct & rhs);
}

#endif
