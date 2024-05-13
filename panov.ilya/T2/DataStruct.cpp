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
void customSort(std::vector<DataStruct>& data) {
  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = i + 1; j < data.size(); ++j) {
      if (data[i].key1 > data[j].key1) {
        std::swap(data[i], data[j]);
        continue;
      }
      if (data[i].key1 == data[j].key1 && data[i].key2 > data[j].key2) {
        std::swap(data[i], data[j]);
        continue;
      }
      if (data[i].key1 == data[j].key1 && data[i].key2 == data[j].key2 && data[i].key3.size() > data[j].key3.size()) {
        std::swap(data[i], data[j]);
        continue;
      }
    }
  }
}
