#ifndef DELIMITER_HPP
#define DELIMITER_HPP

namespace lisitsyna
{
  struct Delimiter
  {
    explicit Delimiter(char exp);
    char exp;
  };

  std::istream& operator>>(std::istream& in, Delimiter&& dest);
}
#endif
