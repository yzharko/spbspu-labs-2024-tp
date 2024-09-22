#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>

#include "DelAnd.hpp"

namespace susidko
{
  struct DataStruct
  {
    long long getKey1() const;
    std::string getKey2() const;
    std::string getKey3() const;

    //private:
    long long key1_;
    std::string key2_;
    std::string key3_;
  };

  std::istream & operator>>(std::istream & is, DataStruct & value);
  std::ostream & operator<<(std::ostream & out, const DataStruct & value);
  bool compareStructs(const DataStruct& first, const DataStruct& second);
}

#endif /* DATASTRUCT_H */
