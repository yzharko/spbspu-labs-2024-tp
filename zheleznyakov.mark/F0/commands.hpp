#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include <ios>
#include <functional>
#include "dict.hpp"

namespace zheleznyakov
{
  namespace commands
  {
    std::ostream & help(std::istream & in, std::ostream & out);
    std::ostream & list(strings_t & strings, std::istream & in, std::ostream & out);
    std::ostream & rm(strings_t & strings, std::istream & in, std::ostream & out);
  }
}
#endif
