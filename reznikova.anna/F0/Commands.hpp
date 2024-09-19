#ifndef Commands_hpp
#define Commands_hpp
#include <iosfwd>
#include <functional>
#include "Graph.hpp"
#include "WorkSpace.hpp"

namespace reznikova
{
  void getOutputMessage(std::ostream & out);
  void helpCommand(std::ostream & out);
  void createCommand(std::istream & is, std::ostream & out, GraphList & list);
  void switchCommand(std::istream & is, std::ostream & out, GraphList & list);
  void addCommand(std::istream & is, std::ostream & out, GraphList & list);
  void deleteCommand(std::istream & is, std::ostream & out, GraphList & list);
  void capacityCommand(std::istream & is, std::ostream & out, GraphList & list);
  void adjacentCommand(std::istream & is, std::ostream & out, GraphList & list);
  void listCommand(std::ostream & out, GraphList & list);
  void graphNameCommand(std::ostream & out, GraphList & list);
  void bfsCommand(std::istream & is, std::ostream & out, GraphList & list);
  void clearCommand(std::istream & is, std::ostream & out);
  void openCommand(std::istream & is, std::ostream & out, GraphList & list);
}

#endif
