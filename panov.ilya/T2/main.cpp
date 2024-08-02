#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "DataStruct.h"

int main() {
  using namespace Panov;

  std::vector<DataStruct> data;

  std::cout << "Введите данные (оставьте пустую строку для завершения ввода):\n";
  std::string line;
  bool supportedRecordFound = false;

  while (true) {
    std::getline(std::cin, line);
    if (line.empty()) {
      break;
    }
    std::istringstream input(line);
    DataStruct ds;
    if (input >> ds) {
      data.push_back(ds);
      supportedRecordFound = true;
    }
    else {
      std::cerr << "Ошибка в формате данных: " << line << '\n';
    }
  }

  if (supportedRecordFound) {
    std::cout << "Atleast one supported record type\n";
  }
  else {
    std::cout << "Looks like there is no supported record. Cannot determine input. Test skipped\n";
  }

  std::sort(data.begin(), data.end());

  std::cout << "Отсортированные данные:\n";
  for (const auto& item : data) {
    std::cout << item << '\n';
  }

  return 0;
}
