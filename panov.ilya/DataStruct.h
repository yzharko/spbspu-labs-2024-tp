#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <utility>

namespace panov
{
  struct DataStruct
  {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;

    friend std::istream& operator>>(std::istream& is, DataStruct& data);
    friend std::ostream& operator<<(std::ostream& os, const DataStruct& data);
  };
  std::complex<double> parseComplex(const std::string& str);
  std::pair<long long, unsigned long long> parseRational(const std::string& str);
}
#endif
