#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iostream>

namespace lisitsyna
{
  struct DelimeterIO
  {
    explicit DelimeterIO(char exp);
    char exp;
  };

  struct LabelIO
  {
    explicit LabelIO(std::string exp);
    std::string exp;
  };

  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}
#endif
