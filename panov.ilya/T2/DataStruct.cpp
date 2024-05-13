#include "datastruct.hpp"
#include <sstream>
#include <algorithm>

bool is_number(const std::string& s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
DataStruct readDataStruct(const std::string& line) {
  DataStruct data;
  std::istringstream iss(line);
  char delimiter;
  std::string key, value;
  iss >> delimiter;
  while (iss >> key) {
    if (key.back() == ':')
      key.pop_back();
    std::getline(iss, value, ':');
    if (!value.empty() && value.front() == ' ')
      value = value.substr(2, value.size() - 3);
    if (key == "key1" || key == ":key1") {
      data.key1 = std::stoull(value, nullptr, 2);

      if (value.size() > 2 && (value[0] == '0' && (value[1] == 'b' || value[1] == 'B'))) {
        value = value.substr(2);
        if (is_number(value))
          data.key1 = std::stoull(value, nullptr, 2);
      }
      else { data.key1 = std::stoull(value); }
    }
    else if (key == "key2" || key == ":key2") {
      data.key2 = value.front();
    }
    else if (key == "key3" || key == ":key3") {
      data.key3 = value;
    }
  }
  return data;
}
void customSort(std::vector<DataStruct>& dataVector) {
  for (size_t i = 0; i < dataVector.size(); ++i) {
    for (size_t j = i + 1; j < dataVector.size(); ++j) {
      if (dataVector[i].key1 > dataVector[j].key1) {
        std::swap(dataVector[i], dataVector[j]);
        continue;
      }
      if (dataVector[i].key1 == dataVector[j].key1 && dataVector[i].key2 > dataVector[j].key2) {
        std::swap(dataVector[i], dataVector[j]);
        continue;
      }
      if (dataVector[i].key1 == dataVector[j].key1 && dataVector[i].key2 == dataVector[j].key2 && dataVector[i].key3.size() > dataVector[j].key3.size()) {
        std::swap(dataVector[i], dataVector[j]);
        continue;
      }
    }
  }
}
