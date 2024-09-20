#include "functions.hpp"
#include <iostream>
#include <algorithm>

namespace kaseev {

  void help()
  {
    std::cout << "help - shows a list of commands\n"
                 "multiply - multiplies numbers by column\n"
                 "sum - sums numbers in a column\n"
                 "pop - Removes a line from the list by name\n"
                 "change - changes a line from a list by name\n"
                 "clear - deletes the entire list\n"
                 "readfile - displays the entire list on the screen\n"
                 "input - adds a row to the list\n"
                 "save - saves the list to a file\n"
                 "exit - stop program";
  }

  void multiply(const std::vector<par>& vec) {
    if (vec.empty()) {
      std::cout << "Vector is empty." << std::endl;
      return;
    }
    size_t max_size = 0;
    for (const auto& pair : vec) {
      if (pair.second.size() > max_size) {
        max_size = pair.second.size();
      }
    }
    std::vector<long long> result(max_size, 1);
    for (const auto& pair : vec) {
      for (size_t i = 0; i < pair.second.size(); ++i) {
        result[i] *= pair.second[i];
      }
    }
    std::cout << "Result of multiplying vectors by positions: ";
    for (const auto& val : result) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }

  void sum(const std::vector<par>& vec) {
    if (vec.empty()) {
      std::cout << "Vector is empty." << std::endl;
      return;
    }
    size_t max_size = 0;
    for (const auto& pair : vec) {
      if (pair.second.size() > max_size) {
        max_size = pair.second.size();
      }
    }
    std::vector<long long> result(max_size, 0);
    for (const auto& pair : vec) {
      for (size_t i = 0; i < pair.second.size(); ++i) {
        result[i] += pair.second[i];
      }
    }
    std::cout << "Result of summing vectors by positions: ";
    for (const auto& val : result) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }

  void pop(std::vector<par>& lines, const std::string& name) {
    auto it = std::remove_if(lines.begin(), lines.end(), [&name](const par& pair) {
      return pair.first == name;
    });
    if (it != lines.end()) {
      lines.erase(it, lines.end());
      std::cout << name << " removed successfully." << std::endl;
    } else {
      std::cout << "No entry found with name: " << name << std::endl;
    }
  }

  void change(std::vector<par>& lines, const std::string& old_name, const std::string& new_value) {
    auto it = std::find_if(lines.begin(), lines.end(), [&old_name](const par& pair) {
      return pair.first == old_name;
    });
    if (it != lines.end()) {
      it->first = new_value;
      std::cout << old_name << " changed to " << new_value << " successfully." << std::endl;
    } else {
      std::cout << "No entry found with name: " << old_name << std::endl;
    }
  }

}
