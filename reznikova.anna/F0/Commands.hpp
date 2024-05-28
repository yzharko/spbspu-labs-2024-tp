#ifndef Commands_hpp
#define Commands_hpp
#include <iosfwd>
#include <functional>
#include "Graph.hpp"
#include "WorkSpace.hpp"

namespace reznikova
{
  void helpCommand(std::ostream & out);
  bool checkWrongNumParameters(std::istream & is);
  void createCommand(std::istream & is, std::ostream & out, GraphList & list);
  void switchCommand(std::istream & is, std::ostream & out, GraphList & list);
  void addVertex(std::istream & is, std::ostream & out, GraphList & list);
  void addEdge(std::istream & is, std::ostream & out, GraphList & list);
  void addCommand(std::istream & is, std::ostream & out, GraphList & list);
  void deleteVertex(std::istream & is, std::ostream & out, GraphList & list);
  void deleteEdge(std::istream & is, std::ostream & out, GraphList & list);
  void deleteCommand(std::istream & is, std::ostream & out, GraphList & list);
  void capacityCommand(std::istream & is, std::ostream & out, GraphList & list);
  void adjacentCommand(std::istream & is, std::ostream & out, GraphList & list);
  void listCommand(std::ostream & out, GraphList & list);
  void graphNameCommand(std::ostream & out, GraphList & list);
  void bfsCommand(std::istream & is, std::ostream & out, GraphList & list);
  void readMatrix(const std::string &filename, std::string &graphname, size_t &num, std::vector<size_t> &indices,
    std::vector<std::vector<size_t>> &matrix);
  void clearCommand(std::istream & is, std::ostream & out);
  void openFileToRead(std::istream & is, std::ostream & out, reznikova::GraphList & list);
  void openFileToWrite(std::istream & is, std::ostream & out, reznikova::GraphList & list);
  void openCommand(std::istream & is, std::ostream & out, GraphList & list);
  void getOutputMessage(std::ostream & out);
  bool checkExtraSymbols(std::istream & is);
}

#endif

