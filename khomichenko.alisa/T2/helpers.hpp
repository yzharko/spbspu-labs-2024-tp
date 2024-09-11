#ifndef HELPERS_HPP
#define HELPERS_HPP

#iclude <string>

namespace khomichenko
{

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  struct CharIO
  {
    char& ref;
  };


  std::istream &operator>>(std::istream &in, DelimiterIO && dest);
  std::istream &operator>>(std::istream &in, DoubleIO && dest);
  std::istream &operator>>(std::istream &in, StringIO && dest);
  std::istream &operator>>(std::istream &in, CharIO && dest);

}

#endif
