#include "IOFunctions.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include "workspace.hpp"

const std::string& getName(std::pair< const std::string&,
const malanin::Graph& > pair)
{
  return pair.first;
}

bool compareNames(const std::string& rhs,
const std::string& lhs)
{
  return lhs == rhs;
}

bool nameIsNotUnique(const std::string& name,
const malanin::Workspace& workspace)
{
  std::vector< std::string > names;
  malanin::getGraphsNames(workspace, names);
  {
    using namespace std::placeholders;
    bool nameAlreadyExists = std::any_of(
      std::begin(names),
      std::end(names),
      std::bind(compareNames, _1, name)
    );
    return nameAlreadyExists;
  }
}

void malanin::getGraphsNames(const malanin::Workspace& workspace,
std::vector< std::string >& accumulator)
{
  std::transform(workspace.graphs.cbegin(),
workspace.graphs.cend(),
std::back_inserter(accumulator), getName);
}

void insertGraph(const malanin::Graph& graph,
malanin::Workspace& workspace)
{
  const std::string& name = graph.name;
  if (nameIsNotUnique(name, workspace))
  {
    throw std::logic_error("[ERROR](insertion): graph, named \"" +
name + "\" already exists");
  }
  workspace.graphs.insert({name, graph});
}

void malanin::initWorkspace(int argc, char* argv[],
malanin::Workspace& workspace)
{
  if (argc == 1)
  {
    return;
  }
  readGraph(argv[1], workspace.current);
  insertGraph(workspace.current, workspace);
  if (argc == 2)
  {
    return;
  }
  for (int i = 2; i < argc; i++)
  {
    Graph temp;
    readGraph(argv[i], temp);
    try
    {
      insertGraph(temp, workspace);
    }
    catch (const std::runtime_error& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
}

void malanin::readGraph(const std::string& filename,
malanin::Graph& container)
{
  std::ifstream in(filename);
  if(!in)
  {
    throw std::runtime_error("[ERROR](input): error while\n"
"opening file " + filename);
  }
  std::string name = "";
  std::getline(in, name);

  in >> container;
  container.name = name;
  container.filename = filename;

  in.close();
}

std::ostream& malanin::sendMessage(std::ostream& out,
const std::string& message)
{
  return out << message << '\n';
}
