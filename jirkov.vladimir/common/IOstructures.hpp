#ifndef IOSTRUCTURES_HPP
#define IOSTRUCTURES_HPP
#include <string>
#include <iosfwd>
#include "DelimiterIO.hpp"
namespace jirkov
{
  std::istream & operator>>(std::istream & in, DelimiterIO && value);

  using Del = DelimiterIO;
}

#endif
