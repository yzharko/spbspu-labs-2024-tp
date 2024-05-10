#include "commands.hpp"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <limits>
#include "inputFunctions.hpp"

// void miheev::commands::execute(const std::string& , miheev::Workspace&)
// {
//   std::map< std::string, miheev::commands::_t > commands;
//   {
//     using namespace std::placeholders;
//     // commands["node"] = std::bind(miheev::commands::node, _1, _2, workspace);
//     // commands["edge"] = std::bind(miheev::commands::edge, _1, _2, workspace);
//     // commands["navigate"] = std::bind(miheev::commands::navigate, _1, _2, workspace);
//     // commands["list"] = std::bind(miheev::commands::list, _1, _2, workspace);
//     // commands["jump"] = std::bind(miheev::commands::jump, _1, _2, workspace);
//     // commands["print"] = std::bind(miheev::commands::print, _1, _2, workspace);
//     commands["node"] = 
//   }
// }

// miheev::commands::Command::Command():
//   type(none)
// {}

// miheev::commands::Command::Command(miheev::commands::ModifyingFunction modifyingFunction)
// {
//   function.modifying = modifyingFunction;
//   type = modifying;
// }

// miheev::commands::Command::Command(miheev::commands::ConstFunction constantFunction)
// {
//   function.constant = constantFunction;
//   type = constant;
// }

// miheev::commands::Command& miheev::commands::Command::operator=(const Command& rhs)
// {
//   type = rhs.type;
//   if (type == constant)
//   {
//     function.constant = rhs.function.constant;
//   }
//   else if (type == modifying)
//   {
//     function.modifying = rhs.function.modifying;
//   }
//   return *this;
// }

// std::ostream& miheev::commands::Command::operator()(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
// {
//   if (type == constant)
//   {
//     return function.constant(out, in, workspace);
//   }
//   else if (type == modifying)
//   {
//     return function.modifying(out, in, workspace);
//   }
//   return out;
// }

std::ostream& miheev::commands::node(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
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

std::ostream& miheev::commands::edge(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
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

std::ostream& miheev::commands::navigate(std::ostream& out, std::istream& in, const miheev::Workspace& workspace)
{
  workspace.current.printNodes(out);
  int lnode = -1, rnode = -1;
  in >> lnode >> rnode;
  miheev::Graph::Path path = workspace.current.navigate(lnode, rnode);
  printPath(out, path);
  return out;
}

std::ostream& miheev::commands::list(std::ostream& out, std::istream&, const miheev::Workspace& workspace)
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

void updateGraph(miheev::Workspace& workspace, const miheev::Graph& graph) // TODO: вынести в функции графа
{
  std::cout << "DEBUG: simple graph before erase: ";
  workspace.graphs.at("simple").printAllEdges();

  workspace.graphs.erase(graph.name);

  std::cout << "DEBUG: simple graph after erase before insert: ";
  workspace.graphs.at("simple").printAllEdges();

  // workspace.graphs.insert({graph.name, graph});
  workspace.graphs.insert({graph.name, graph});

  std::cout << "DEBUG: simple graph after insert: ";
  miheev::Graph g = workspace.graphs.at("simple");
  g.printAllEdges();
  // std::cout << "DEBUG: after ";
  // workspace.graphs.at(graph.name).printAllEdges();
}

std::ostream& miheev::commands::jump(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
{
  // std::cout << "DEBUG: before update (simple): ";
  // workspace.graphs.at("simple").printAllEdges();
  std::string name = "";
  std::getline(in >> std::ws, name);
  updateGraph(workspace, workspace.current);
  // std::cout << "DEBUG: after update: ";
  // workspace.graphs.at(workspace.current.name).printAllEdges();
  // std::cout << "DEGUG: befor shit (simple): ";
  // workspace.graphs.at("simple").printAllEdges();
  // std::cout << "DEGUG: befor shit (complex): ";
  // workspace.graphs.at("complex").printAllEdges();
  try
  {

    // workspace.graphs[name].printAllEdges();
    miheev::Graph newCurrent = workspace.graphs.at(name);
    newCurrent.printAllEdges();
    // workspace.graphs.at(workspace.current.name).printAllEdges(out);

    workspace.current = newCurrent;
    out << "succesfully jumped to graph \"" << workspace.current.name << "\"\n";
  }
  catch (const std::out_of_range& e)
  {
    out << "Jump error: graph with name \"" << name << "\" doesn't exist\n";
  }
  return out;
}

std::ostream& miheev::commands::print(std::ostream& out, std::istream& in, const miheev::Workspace& workspace)
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

// std::ostream& miheev::commands::save(std::ostream& out, std::istream& in, const miheev::Workspace&)
// {}

// std::ostream& miheev::commands::help(std::ostream& out, std::istream& in, const miheev::Workspace&)
