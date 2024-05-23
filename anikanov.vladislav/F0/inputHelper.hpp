#ifndef INPUTHELPER_HPP
#define INPUTHELPER_HPP

#include <iosfwd>

namespace anikanov {
  bool readCommand(std::istream &in, std::string &command);
}

#endif
