#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <complex>
#include <string>
#include <utility>
#include <cmath>

namespace Panov {

  struct DataStruct {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;

    bool operator<(const DataStruct& other) const {
      if (std::abs(key1) != std::abs(other.key1)) return std::abs(key1) < std::abs(other.key1);
      if (key2 != other.key2) return key2 < other.key2;
      return key3 < other.key3;
    }
  };

  std::istream& operator>>(std::istream& in, std::complex<double>& c);
  std::ostream& operator<<(std::ostream& out, const std::complex<double>& c);

  std::istream& operator>>(std::istream& is, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);

}

#endif
