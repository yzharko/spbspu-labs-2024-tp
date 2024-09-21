#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

namespace kaseev {

  void help() {
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
    } else
    {
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
    } else
    {
      std::cout << "No entry found with name: " << old_name << std::endl;
    }
  }

  void clear(std::vector<par>& vec) {
    vec.clear();
    std::cout << "All entries cleared." << std::endl;
  }

  void readfile(std::vector<par>& vec) {
    size_t max_len = 0;
    for (const auto& pair : vec) {
      std::cout << pair.first << ' ';
      max_len = std::max(max_len, pair.second.size());
    }
    for (size_t i = 0; i < max_len; ++i) {
      for (size_t j = 0; j < vec.size(); ++j) {
        if (i < vec[j].second.size())
          std::cout << vec[j].second[i] << ' ';
      }
      std::cout << '\n';
    }
  }

  void input(std::vector<par>& vec) {
    std::string name;
    std::vector<long long> numbers;
    std::cout << "Enter a name: ";
    std::cin >> name;
    std::cout << "Enter numbers (end with non-number): ";
    long long num;
    while (std::cin >> num) {
      numbers.push_back(num);
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    vec.push_back({name, numbers});
    std::cout << "Added entry - Name: " << name << " Numbers: ";
    for (const auto& n : numbers) {
      std::cout << n << " ";
    }
    std::cout << std::endl;
  }

  void save(std::vector<par>& vec, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
      std::cerr << "Error: Could not open file " << filename << std::endl;
      return;
    }
    size_t max_len = 0;
    for (const auto& pair : vec) {
      file << pair.first << ' ';
      max_len = std::max(max_len, pair.second.size());
    }
    file << '\n';
    for (size_t i = 0; i < max_len; ++i) {
      for (size_t j = 0; j < vec.size(); ++j) {
        if (i < vec[j].second.size())
          file << vec[j].second[i] << ' ';
      }
      file << '\n';
    }
  }
}
