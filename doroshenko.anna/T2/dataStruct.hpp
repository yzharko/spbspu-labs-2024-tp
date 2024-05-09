#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>

namespace doroshenko
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& input, DataStruct& dest);
  std::ostream& operator<<(std::ostream& output, const DataStruct& src);
  std::ostream& outDblSci(std::ostream& output, double number);
  bool compareStructs(const DataStruct& firstStruct, const DataStruct& secondStruct);
}

#endif
