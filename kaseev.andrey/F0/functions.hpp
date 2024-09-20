#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <vector>
#include <string>

namespace kaseev {

  using par = std::pair<std::string, std::vector<long long>>;

  void help();
  void multiply(const std::vector<par>& vec);
  void sum(const std::vector<par>& vec);
  void pop(std::vector<par>& lines, const std::string& name);
  void change(std::vector<par>& lines, const std::string& old_name, const std::string& new_value);
  void clear(std::vector<par>& vec);
  void readfile(std::vector<par>& vec);
}

#endif
