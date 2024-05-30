#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <vector>
#include <string>

struct DataStruct {
  unsigned long long key1;
  char key2;
  std::string key3;
};
DataStruct readDataStruct(const std::string& line);
void customSort(std::vector<DataStruct>& dataVector);
#endif
