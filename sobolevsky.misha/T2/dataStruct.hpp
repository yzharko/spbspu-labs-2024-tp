#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include "../common/helpStructs.hpp"

namespace sobolevsky
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & in, sobolevsky::DataStruct & value);
  std::ostream & operator<<(std::ostream & out, const sobolevsky::DataStruct & value);
  bool operator<(const DataStruct & first, const DataStruct & second);
}

#endif