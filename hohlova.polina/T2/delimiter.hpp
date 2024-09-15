#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iosfwd>
#include <string>

namespace hohlova
{
  struct DelimiterIO
  {
    char exp;
  };

  struct LabelIO
  {
    std::string exp;
  };

  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
