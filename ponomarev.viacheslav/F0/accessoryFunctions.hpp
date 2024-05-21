#ifndef ACCESSORY_FUNCTIONS_HPP
#define ACCESSORY_FUNCTIONS_HPP

#include <string>
#include <ostream>

namespace ponomarev
{
  std::string cutType(std::string & line);

  std::ostream & printInvalidCommandMessage(std::ostream & out);
}

#endif
