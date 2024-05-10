#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "workspace.hpp"
#include <functional>

namespace miheev
{
  namespace commands
  {
    std::ostream& node(std::ostream&, std::istream&, Workspace&);
    std::ostream& edge(std::ostream&, std::istream&, Workspace&);
    std::ostream& graph(std::ostream&, std::istream&, Workspace&);
    std::ostream& navigate(std::ostream&, std::istream&, const Workspace&);
    std::ostream& list(std::ostream&, std::istream&, const Workspace&);
    std::ostream& jump(std::ostream&, std::istream&, Workspace&);
    std::ostream& print(std::ostream&, std::istream&, const Workspace&);
    std::ostream& save(std::ostream&, std::istream&, const Workspace&);
    std::ostream& help(std::ostream&, std::istream&, const Workspace&);
    std::ostream& status(std::ostream&, std::istream&, const Workspace&);
  }
}

#endif
