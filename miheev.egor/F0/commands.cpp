#include "commands.hpp"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include "IOFunctions.hpp"

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

void updateGraph(miheev::Workspace& workspace, const miheev::Graph& graph) // TODO: вынести в функции графа
{
  workspace.graphs.erase(graph.name);
  workspace.graphs.insert({graph.name, graph});
}

void makeCastling(std::ostream& out, std::string nameOfNew, miheev::Workspace& workspace)
{
  updateGraph(workspace, workspace.current);
  try
  {
    miheev::Graph newCurrent = workspace.graphs.at(nameOfNew);
    workspace.current = newCurrent;
  }
  catch (const std::out_of_range& e)
  {
    out << "Jump error: graph with name \"" << nameOfNew << "\" doesn't exist\n";
  }
}

void createGraphFromFile(std::istream& in, std::ostream& out, miheev::Workspace& workspace)
{
  std::string filename;
  in >> filename;
  miheev::Graph temp;
  miheev::readGraph(filename, temp);
  updateGraph(workspace, temp);
  makeCastling(out, temp.name, workspace);
  miheev::sendMessage(out, "[INFO] graph \"" + temp.name + "\" initialised succesfully");
}

void readGraphFromInput(std::istream& in, miheev::Graph& container)
{
  in.clear();
  std::string input;
  std::getline(in >> std::ws, input, '\n');
  std::stringstream ss(input);
  ss >> container;
}

void createGraphFrominput(std::istream& in, std::ostream& out, const std::string& name, miheev::Workspace& workspace)
{
  miheev::Graph temp;
  temp.name = name;
  out << "(" << name << "): ";

  readGraphFromInput(in, temp);

  updateGraph(workspace, temp);
  makeCastling(out, name, workspace);
  miheev::sendMessage(out, "[INFO] graph \"" + temp.name + "\" initialised succesfully\n");
}

void closeGraphWithoutSaving(std::istream& in, std::ostream& out, miheev::Workspace& workspace)
{
  std::string arg = "";
  in >> arg;
  workspace.graphs.erase(arg);
  if (workspace.current.name == arg)
  {
    miheev::Graph substitution = workspace.graphs.begin()->second;
    workspace.current = substitution;
  }
  miheev::sendMessage(out, "[INFO] graph \"" + arg + "\" was deleted");
}

std::ostream& miheev::commands::graph(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
{
  std::string arg = "";
  in >> arg;
  if (arg == "add")
  {
    in >> arg;
    if (arg == "-f")
    {
      createGraphFromFile(in, out, workspace);
    }
    else
    {
      createGraphFrominput(in, out, arg, workspace);
    }
  }
  else if (arg == "close")
  {
    closeGraphWithoutSaving(in, out, workspace);
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

std::ostream& miheev::commands::jump(std::ostream& out, std::istream& in, miheev::Workspace& workspace)
{
  std::string name = "";
  std::getline(in >> std::ws, name);
  updateGraph(workspace, workspace.current);
  makeCastling(out, name, workspace);
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

std::ostream& miheev::commands::save(std::ostream& out, std::istream& in, const miheev::Workspace& workspace)
{
  std::string arg = "";
  in >> arg;
  if (arg == "-f")
  {
    std::string filename = workspace.current.filename;
    std::ofstream output(filename);
    output << workspace.current.name << '\n';
    workspace.current.printAllEdges(output);
  }
  else
  {
    std::ofstream output(arg);
    output << workspace.current.name << '\n';
    workspace.current.printAllEdges(output);
  }
  return out;
}

// std::ostream& miheev::commands::help(std::ostream& out, std::istream& in, const miheev::Workspace&)
