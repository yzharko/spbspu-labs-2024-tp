#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include<string>
#include<iostream>
#include<iterator>

namespace doroshenko
{
  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double& ref;
  };

  struct CharIO
  {
    char& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  std::istream& operator>>(std::istream& input, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& input, DoubleIO&& dest);
  std::istream& operator>>(std::istream& input, CharIO&& dest);
  std::istream& operator>>(std::istream& input, StringIO&& dest);
  std::ostream& outDblSci(std::ostream& output, double number);
}

#endif
