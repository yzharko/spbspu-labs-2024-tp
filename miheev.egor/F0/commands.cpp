#include "commands.hpp"
#include <iterator>
#include <iostream>

std::ostream& miheev::nodeCommand(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
{
  std::string action = "";
  int node = -1;
  in >> action >> node;
  if (node < 0)
  {
    throw std::invalid_argument("Node error: nodes can't be negative\n");
  }
  if (action == "add")
  {
    workspace.current.addNode(node);
  }
  else if (action == "rm")
  {
    workspace.current.rmNode(node);
  }
  else
  {
    throw std::invalid_argument("command node don't have such parameters");
  }
}

std::ostream& miheev::edgeCommand(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
{
  std::string action = "";
  int lnode = -1, rnode = -1;
  in >> action >> lnode >> rnode;
  if (action == "add")
  {
    size_t weight = 1; // Добавить возможность сделать вес опциональным параметром
    in >> weight;
    workspace.current.addEdge(lnode, rnode, weight);
  }
  else if (action == "rm")
  {
    workspace.current.rmEdge(lnode, rnode);
  }
  else
  {
    throw std::invalid_argument("command node don't have such parameters");
  }
}

void printPath(std::ostream& out, const miheev::Graph::Path& path)
{
  std::copy(
    path.path.begin(),
    path.path.end(),
    std::ostream_iterator< int >(out, "+")
  );
  out << "Path length is\n";
}

std::ostream& navigateCommand(std::ostream& out, std::istream& in, const miheev::Workspace& workspace)
{
  int lnode = -1, rnode = -1;
  in >> lnode >> rnode;
  miheev::Graph::Path path = workspace.current.navigate(lnode, rnode);
  printPath(out, path);
}

std::ostream& listCommand(std::ostream& out, std::istream& in, const miheev::Workspace&)
{}

std::ostream& jumpCommand(std::ostream& out, std::istream& in, const miheev::Workspace&)
{}

std::ostream& printCommand(std::ostream& out, std::istream& in, const miheev::Workspace&)
{}

std::ostream& saveCommand(std::ostream& out, std::istream& in, const miheev::Workspace&)
{}

std::ostream& helpCommand(std::ostream& out, std::istream& in, const miheev::Workspace&)
{}
