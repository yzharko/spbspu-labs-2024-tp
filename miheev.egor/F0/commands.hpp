#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "workspace.hpp"
#include <functional>

namespace miheev
{
  // void execute(const std::string& command, Workspace&);

  namespace commands
  {
    // enum type_t
    // {
    //   constant,
    //   modifying,
    //   none
    // };

    // using ConstFunction = std::function< std::ostream&(std::ostream&, std::istream&, const Workspace&) >;
    // using ModifyingFunction = std::function< std::ostream&(std::ostream&, std::istream&, Workspace&) >;

    // struct Command
    // {
    //   Command();
    //   Command(ModifyingFunction);
    //   Command(ConstFunction);

    //   Command& operator=(const Command&);

    //   std::ostream& operator()(std::ostream&, std::istream&, Workspace&);
    //   union command_t
    //   {
    //     command_t() {}
    //     ~command_t() {}
    //     ModifyingFunction modifying;
    //     ConstFunction constant;
    //   };
    //   command_t function;
    //   type_t type;
    // };

    std::ostream& node(std::ostream&, std::istream&, Workspace&);
    std::ostream& edge(std::ostream&, std::istream&, Workspace&);
    std::ostream& navigate(std::ostream&, std::istream&, const Workspace&);
    std::ostream& list(std::ostream&, std::istream&, const Workspace&);
    std::ostream& jump(std::ostream&, std::istream&, Workspace&);
    std::ostream& print(std::ostream&, std::istream&, const Workspace&);
    std::ostream& save(std::ostream&, std::istream&, const Workspace&);
    std::ostream& help(std::ostream&, std::istream&, const Workspace&);
  }
  // NOTE: аргументы принимаются уже внутри
  // std::ostream& nodeCommand(std::ostream&, std::istream&, Workspace&);
  // std::ostream& edgeCommand(std::ostream&, std::istream&, Workspace&);
  // std::ostream& navigateCommand(std::ostream&, std::istream&, const Workspace&);
  // std::ostream& listCommand(std::ostream&, std::istream&, const Workspace&);
  // std::ostream& jumpCommand(std::ostream&, std::istream&, Workspace&);
  // std::ostream& printCommand(std::ostream&, std::istream&, const Workspace&);
  // std::ostream& saveCommand(std::ostream&, std::istream&, const Workspace&);
  // std::ostream& helpCommand(std::ostream&, std::istream&, const Workspace&);
}

#endif
