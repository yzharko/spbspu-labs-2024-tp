#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

namespace khomichenko
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream & in, DataStruct & dataStr);
  std::ostream & operator<<(std::ostream & out, const DataStruct & dataStr);
}


#endif
