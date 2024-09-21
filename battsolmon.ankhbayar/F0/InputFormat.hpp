#ifndef INPUT_FORMAT_HPP
#define INPUT_FORMAT_HPP

#include "Edge.hpp"

struct DelimiterIO {
  char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, Edge& edge);

#endif
