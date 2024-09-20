#ifndef DICTS_HPP
#define DICTS_HPP
#include <map>
#include <vector>
#include <string>

namespace panov
{
  using word_t = std::pair< std::string, std::string >;
  using dict_t = std::vector< word_t >;
  using dicts_t = std::map< std::string, dict_t >;
}
#endif
