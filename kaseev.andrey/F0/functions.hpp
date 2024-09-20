#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <vector>
#include <string>

namespace kaseev {

  using par = std::pair<std::string, std::vector<long long>>;

  void help();
  void multiply(const std::vector<par>& vec);
  void sum(const std::vector<par>& vec);

}

#endif
