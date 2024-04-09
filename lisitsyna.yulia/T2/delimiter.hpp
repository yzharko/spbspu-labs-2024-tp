#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <istream>
#include <string>

namespace lisitsyna
{
  struct Separator
  {
    char exp;
  };
  std::istream & operator>>(std::istream & in, Separator && dest);
}
#endif
