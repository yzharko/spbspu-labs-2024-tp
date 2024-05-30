#include <iostream>
#include <vector>
#include <algorithm>
#include "DataStruct.hpp"

int main() {
  std::vector<DataStruct> dataVector;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty())
      continue;
    try {
      dataVector.push_back(readDataStruct(line));
    }
    catch (...) {
      continue;
    }
  }
  customSort(dataVector);
  for (const auto& data : dataVector) {
    std::cout << "(:key1 " << data.key1 << ":"
      << ":key2 '" << data.key2 << "':"
      << ":key3 \"" << data.key3 << "\":)" << std::endl;
  }
  return 0;
}
