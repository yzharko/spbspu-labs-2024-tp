#include "inputHelper.hpp"

#include <iostream>
#include <inDelim.hpp>

bool anikanov::readCommand(std::istream &in, std::string &command)
{
  if (!(in >> DelimiterIO{'/'} >> command)) {
    return false;
  }
  return true;
}
