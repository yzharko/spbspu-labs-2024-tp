#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>

namespace maksimov
{
  void printError(std::ostream& output = std::cout);
  void printEmptyError(std::ostream& output = std::cout);
  void fixStream(std::istream& input);
  void handleError(std::istream& input = std::cin, std::ostream& output = std::cout);
}

#endif
