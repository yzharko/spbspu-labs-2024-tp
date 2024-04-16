#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <complex>

namespace redko
{
  struct DataStruct
  {
    long long key1;
    std::complex< double > key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & in, DataStruct & dest);
  std::ostream & operator<<(std::ostream & out, const DataStruct & dest);

  bool operator<(const DataStruct & lhs, const DataStruct & rhs);
}

#endif
