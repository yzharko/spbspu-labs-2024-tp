#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <complex>
#include <string>

struct DataStruct
{
  unsigned long long key1;
  std::complex< double > key2;
  std::string key3;
};

std::istream& operator >> (std::istream& is, DataStruct& dest);
std::ostream& operator << (std::ostream& out, const DataStruct& dest);

#endif
