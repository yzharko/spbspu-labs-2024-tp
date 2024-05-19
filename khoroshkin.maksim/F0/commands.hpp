#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include "graph.hpp"

namespace khoroshkin
{
  void helpCmd(std::ostream & out);
  void openCmd(Graph< int > & graph, std::istream & is, std::ostream & out);
  void inputCmd(Graph< int > & graph, std::istream & is, std::ostream & out);
  void printCmd(Graph< int > & graph, std::istream & is, std::ostream & out);
  void edgeCmd(Graph< int > & graph, std::istream & is, std::ostream & out);
  void sortCmd(Graph< int > & graph, std::istream & is, std::ostream & out);
  void sortCmd(Graph< int > & graph, std::istream & is, std::ostream & out);
}

#endif
