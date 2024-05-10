#include "commands.hpp"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <limits>
#include "inputFunctions.hpp"

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
  return out;
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
  return out;
}

void printPath(std::ostream& out, const miheev::Graph::Path& path)
{
  out << "Path is: ";
  std::copy(
    path.path.begin(),
    path.path.end(),
    std::ostream_iterator< int >(out, " ")
  );
  out << '\n' << "Path length is: " << path.lenght << '\n';
}

std::ostream& miheev::navigateCommand(std::ostream& out, std::istream& in, const miheev::Workspace& workspace)
{
  workspace.current.printNodes(out);
  int lnode = -1, rnode = -1;
  in >> lnode >> rnode;
  miheev::Graph::Path path = workspace.current.navigate(lnode, rnode);
  printPath(out, path);
  return out;
}

std::ostream& miheev::listCommand(std::ostream& out, std::istream&, const miheev::Workspace& workspace)
{
  std::vector< std::string > names;
  miheev::getGraphsNames(workspace, names);
  std::copy(
    names.begin(),
    names.end(),
    std::ostream_iterator< const std::string& >(out, "\n")
  );
  return out;
}

void updateGraph(miheev::Workspace& workspace, const miheev::Graph& graph)
{
  workspace.graphs.erase(graph.name);
  workspace.graphs.insert({graph.name, graph});
}

std::ostream& miheev::jumpCommand(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
{
  std::string name = "";
  std::getline(in >> std::ws, name);
  updateGraph(workspace, workspace.current);
  try
  {
    miheev::Graph newCurrent = workspace.graphs.at(name);
    workspace.current = newCurrent;
    workspace.current.printNodes(out);
    out << "succesfully jumped to graph \"" << newCurrent.name << "\"\n";
  }
  catch (const std::out_of_range& e)
  {
    out << "Jump error: graph with name \"" << name << "\" doesn't exist\n";
  }
  return out;
}

std::ostream& miheev::printCommand(std::ostream& out, std::istream& in, const miheev::Workspace& workspace)
{
  std::string arg = "";
  in >> arg;
  if (arg == "nodes")
  {
    workspace.current.printNodes(out);
  }
  else if (arg == "edges")
  {
    workspace.current.printAllEdges(out);
  }
  else
  {
    throw std::invalid_argument("Print error: commant takes only \"nodes\" and \"edges\" as parameters, while \"" + arg + "\" passed\n");
  };
  return out;
}

// std::ostream& miheev::saveCommand(std::ostream& out, std::istream& in, const miheev::Workspace&)
// {}

// std::ostream& miheev::helpCommand(std::ostream& out, std::istream& in, const miheev::Workspace&)
