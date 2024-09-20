#include "commands.hpp"
#include "scopeguard.hpp"
#include "IOFunction.hpp"
#include <iterator>
#include <algorithm>
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>

std::ostream& malanin::commands::node(std::ostream& out, std::istream& in, malanin::Workspace& workspace)
{
  std::string action = "";
  int node = -1;
  in >> action >> node;
  if (node < 0)
  {
    throw std::invalid_argument("[ERROR]: nodes can't be negative");
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

std::ostream& malanin::commands::edge(std::ostream& out, std::istream& in, malanin::Workspace& workspace)
{
  std::string action = "";
  int lnode = -1, rnode = -1;
  in >> action >> lnode >> rnode;
  if (action == "add")
  {
    size_t weight = 1;
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

void updateGraph(malanin::Workspace& workspace, const malanin::Graph& graph)
{
  workspace.graphs.erase(graph.name);
  workspace.graphs.insert({graph.name, graph});
}

void makeCastling(std::ostream& out, std::string nameOfNew, malanin::Workspace& workspace)
{
  updateGraph(workspace, workspace.current);
  try
  {
    malanin::Graph newCurrent = workspace.graphs.at(nameOfNew);
    workspace.current = newCurrent;
  }
  catch (const std::out_of_range& e)
  {
    malanin::sendMessage(out, "[ERROR]: graph with name \"" + nameOfNew + "\" doesn't exist\n");
  }
}

void createGraphFromFile(std::istream& in, std::ostream& out, malanin::Workspace& workspace)
{
  std::string filename;
  in >> filename;
  malanin::Graph temp;
  malanin::readGraph(filename, temp);
  updateGraph(workspace, temp);
  makeCastling(out, temp.name, workspace);
  malanin::sendMessage(out, "[INFO] graph \"" + temp.name + "\" initialised succesfully");
}

void readGraphFromInput(std::istream& in, malanin::Graph& container)
{
  in.clear();
  std::string input;
  std::getline(in >> std::ws, input, '\n');
  std::stringstream ss(input);
  ss >> container;
}

void createGraphFrominput(std::istream& in, std::ostream& out, const std::string& name, malanin::Workspace& workspace)
{
  malanin::Graph temp;
  temp.name = name;
  out << "(" << name << "): ";

  readGraphFromInput(in, temp);

  updateGraph(workspace, temp);
  makeCastling(out, name, workspace);
  malanin::sendMessage(out, "[INFO] graph \"" + temp.name + "\" initialised succesfully\n");
}

void closeGraphWithoutSaving(std::istream& in, std::ostream& out, malanin::Workspace& workspace)
{
  std::string arg = "";
  in >> arg;
  workspace.graphs.erase(arg);
  if (workspace.current.name == arg)
  {
    malanin::Graph substitution = workspace.graphs.begin()->second;
    workspace.current = substitution;
  }
  malanin::sendMessage(out, "[INFO] graph \"" + arg + "\" was deleted");
}

std::ostream& malanin::commands::graph(std::ostream& out, std::istream& in, malanin::Workspace& workspace)
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

void printPath(std::ostream& out, const malanin::Graph::Path& path)
{
  out << "Path is: ";
  std::copy(
    path.path.begin(),
    path.path.end(),
    std::ostream_iterator< int >(out, " ")
  );
  out << '\n' << "Path length is: " << path.lenght << '\n';
}

std::ostream& malanin::commands::path(std::ostream& out, std::istream& in, const malanin::Workspace& workspace)
{
  // примет словом: all, any, count, exists
  std::string arg;
  int begin, end;
  in >> arg >> begin >> end;
  if (arg == "all")
  {
    workspace.current.printAllPaths(begin, end, out);
  }
  else if (arg == "any")
  {
    workspace.current.printAnyPath(begin, end, out);
  }
  else if (arg == "count")
  {
    size_t count = workspace.current.countPaths(begin, end);
    out << "amount of paths: " << count << '\n';
  }
  else if (arg == "exists")
  {
    bool doExists = workspace.current.pathExists(begin, end);
    std::string verdict = doExists? "exists" : "doesn't exist";
    out << "path between nodes \"" << begin << "\" and \"" << end << "\" " << verdict << '\n';
  }
  else
  {
    throw std::invalid_argument("[ERROR]: path command takes only `all`, `any`, `exists` or `count` arguments, but \"" + arg + "\" given");
  }

  return out;
}

std::ostream& malanin::commands::list(std::ostream& out, std::istream&, const malanin::Workspace& workspace)
{
  std::vector< std::string > names;
  malanin::getGraphsNames(workspace, names);
  std::copy(
    names.begin(),
    names.end(),
    std::ostream_iterator< const std::string& >(out, "\n")
  );
  return out;
}

std::ostream& malanin::commands::jump(std::ostream& out, std::istream& in, malanin::Workspace& workspace)
{
  std::string name = "";
  std::getline(in >> std::ws, name);
  updateGraph(workspace, workspace.current);
  makeCastling(out, name, workspace);
  return out;
}

std::ostream& malanin::commands::print(std::ostream& out, std::istream& in, const malanin::Workspace& workspace)
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
    throw std::invalid_argument("[ERROR]: commant takes only \"nodes\" and \"edges\" as parameters, while \"" + arg + "\" passed");
  };
  return out;
}

std::ostream& malanin::commands::save(std::ostream& out, std::istream& in, const malanin::Workspace& workspace)
{
  std::string arg = "";
  in >> arg;
  if (arg == "-r")
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
  return sendMessage(out, "[INFO] graph \"" + workspace.current.name + "\" saved succesfully");
}

std::ostream& malanin::commands::help(std::ostream& out, std::istream&, const malanin::Workspace&)
{
  out << "help - prints listing of all commands with some clarifications\n" << '\n';
  // out << "navigate < a > < b > - searches for the shortest path between nodes < a > and < b >. ";
  // out << "Note: < a > < b > are positive integers\n\n";
  out << "path < what > < a > < b > - a and b are 2 nodes, actions depend on 'what' argument. ";
  out << "'all' prints all possible paths between nodes. 'any' prints first found path between nodes. ";
  out << "'count' prints amount of paths between nodes. 'exists' prints if path between nodes exists\n\n";
  out << "graph add < graphname > - lets user to create a new graph using standart input. ";
  out << "write down edges in a-b:w format, where a and b are nodes and w is weight\n\n";
  out << "graph add -f < filename > - reads a graph from file. note that file contains name of the graph too\n\n";
  out << "print < what > - prints informations about graph. Take \"nodes\" or \"edges\" as arugents. ";
  out << "If \"nodes\" passed, then prints the list of all nodes of focused graph. ";
  out << "Else if \"edges\" was given, prints edges in format a-b:w, ";
  out << "where a and b are nodes and w is weight of edge\n\n";
  out << "list - prints list of all graphs in workspace\n\n";
  out << "jump < graphname > - swithes focus to the graph named \"graphname\"\n\n";
  out << "node add < number > - adds new node with name < number > to the focused graph\n\n";
  out << "node rm < number > - removes node named < number > from focused graph\n\n";
  out << "edge add < a > < b > < weight > - add an edge between nodes < a > and < b > with specified < weight >\n\n";
  out << "edge rm < a, b > - removes edge between nodes < a > and < b >\n\n";
  out << "save < filepath > - saves focused graph to file in < filepath >. If file doesn't exists it will be created\n\n";
  out << "save -r - if file was read from file, it will be saved int this exact file\n\n";
  out << "quit - close all graphs without saving\n";
  return out;
}
std::ostream& malanin::commands::quit(std::ostream& out, std::istream&, malanin::Workspace& workspace)
{
  workspace.isActive = false;
  return out;
}
