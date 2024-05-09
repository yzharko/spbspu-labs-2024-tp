#include "inputFunctions.hpp"
#include <fstream>
#include "workspace.hpp"

void insertGraph(const miheev::Graph& graph, miheev::Workspace& workspace)
{
  const std::string& name = graph.name;
  workspace.graphs.insert({name, graph});
}

void miheev::initWorkspace(int argc, char* argv[], miheev::Workspace& workspace)
{
  readGraph(argv[1], workspace.current);
  for (size_t i = 2; i < argc; i++)
  {
    Graph temp;
    readGraph(argv[i], temp);
    insertGraph(temp, workspace);
  }
}

void miheev::readGraph(const std::string& filename, miheev::Graph& container)
{
  std::ifstream in(filename);
  if(!in)
  {
    throw std::runtime_error("Input error: error while opening file " + filename);
  }
  std::string name = "";
  std::getline(in, name);

  in >> container;
  container.name = name;
  container.filename = filename;

  in.close();
}