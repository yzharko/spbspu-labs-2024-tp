#ifndef PROCESSINGFUNCTIONS_HPP
#define PROCESSINGFUNCTIONS_HPP
#include <string>
#include <ostream>

namespace redko
{
  std::string cutName(std::string & str);
  void printMessage(std::ostream & out, const std::string & message);
}

#endif
