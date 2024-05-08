#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "workspace.hpp"

namespace miheev
{
  // NOTE: аргументы принимаются уже внутри
  std::ostream& addCommand(std::ostream&, std::istream&, Workspace&);
  std::ostream& rmCommand(std::ostream&, std::istream&, Workspace&);
  std::ostream& navigateCommand(std::ostream&, std::istream&, const Workspace&);
  std::ostream& listCommand(std::ostream&, std::istream, const Workspace&);
  std::ostream& jumpCommand(std::ostream&, std::istream&, const Workspace&);
  std::ostream& printCommand(std::ostream&, std::istream&, const Workspace&);
  std::ostream& saveCommand(std::ostream&, std::istream&, const Workspace&);
  std::ostream& helpCommand(std::ostream&, std::istream&, const Workspace&);
}

#endif