#include "Commands.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void reznikova::helpCommand(std::ostream & out)
{
  out << "create < graph > < graphname > - создание пустого графа с названием  graphname\n";
  out << "add < vertice > < index > – создание вершины графа с индексом index\n";
  out << "add < edge > < first_vertice, second_vertice > - создание ребра между"
  << "вершинами first_vertice и second_vertice\n";
  out << "delete < vertice > < name > - удаление вершины name\n";
  out << "delete < edge > < first_vertice, second_vertice > - удаление ребра между"
  << "вершинами first_vertice и second_vertice\n";
  out << "capacity <  graphname > - вывод количества вершин в графе graphname\n";
  out << "adjacent < first_vertice, second_ vertice > - проверяет наличие ребра между"
  << "вершинами first_vertice и second_vertice\n";
  out << "list — вывод списка графов\n";
  out << "switch < graphName > - переключение на работу с графом GraphName\n";
  out << "graphname — выводит имя графа, над которым ведется работа\n";
  out << "BFS < first_vertice > - возвращает список вершин в порядке обхода в ширину из"
  << "исходной вершины first_vertice\n";
  out << "clean < filename > — очищает содержимое файла\n";
  out << "open < read >< filename > — открытие файла с заданным названием и чтение его содержимого\n";
  out << "open < write >< filename > — открытие файла с заданным названием для записи данных\n";
}

bool reznikova::checkWrongNumParameters(std::istream & is)
{
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
  {
    return false;
  }
  return true;
}

void reznikova::createCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string second_parameter;
  if (!(is >> second_parameter))
  {
    throw std::logic_error("wrong parameters\n");
  }
  else if (second_parameter != "graph")
  {
    throw std::logic_error("wrong parameters\n");
  }
  std::string graphName;
  if (!(is >> graphName))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  try
  {
    list.addToList(Graph(graphName));
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
  out << "Graph " << graphName << " created. This graph is active\n";
}

void reznikova::switchCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string graphName;
  is >> graphName;
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  if (!list.isGraphInList(graphName))
  {
    throw std::logic_error("can't switch to graph which does not exist\n");
  }
  else if (list.findGraphByName(graphName)->isActive_ == true)
  {
    throw std::logic_error("this graph is active already\n");
  }
  list.resetActiveFlags();
  try
  {
    list.findGraphByName(graphName)->isActive_ = true;
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
  out << "Switched to graph " << graphName << "\n";
}

void reznikova::addVertex(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t index;
  if (!(is >> index))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  try
  {
    WorkObject * graph = list.getActiveGraph();
    graph->graph_.addVertex(index);
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
  out << "Vertex with index " << index << " were added\n";
}

void reznikova::addEdge(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t first_index;
  size_t second_index;
  if (!(is >> first_index >> second_index))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  try
  {
    WorkObject * graph = list.getActiveGraph();
    graph->graph_.addEdge(first_index, second_index);
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
  out << "Edge between " << first_index << " and " << second_index << " indexes were added\n";
}

void reznikova::addCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string second_parameter;
  if (!(is >> second_parameter))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (second_parameter == "vertex")
  {
    addVertex(is, out, list);
  }
  else if (second_parameter == "edge")
  {
    addEdge(is, out, list);
  }
  else
  {
    throw std::logic_error("wrong parameters\n");
  }
}

void reznikova::deleteVertex(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t index;
  if (!(is >> index))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  try
  {
    WorkObject * graph = list.getActiveGraph();
    graph->graph_.removeVertex(index);
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
  out << "Vertex with index " << index << " were deleted\n";
}

void reznikova::deleteEdge(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t first_index;
  size_t second_index;
  if (!(is >> first_index >> second_index))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  try
  {
    WorkObject * graph = list.getActiveGraph();
    graph->graph_.removeEdge(first_index, second_index);
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
  out << "Edge between " << first_index << " and " << second_index << " indexes were deleted\n";
}

void reznikova::deleteCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string second_parameter;
  if (!(is >> second_parameter))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (second_parameter == "vertex")
  {
    deleteVertex(is, out, list);
  }
  else if (second_parameter == "edge")
  {
    deleteEdge(is, out, list);
  }
  else
  {
    throw std::logic_error("wrong parameters\n");
  }
}

void reznikova::capacityCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string graphName;
  is >> graphName;
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  if (!list.isGraphInList(graphName))
  {
    throw std::logic_error("can't get capacity of a graph which does not exist\n");
  }
  size_t capacity;
  try
  {
    capacity = list.findGraphByName(graphName)->graph_.getCapacity();
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
  out << "Capacity of graph " << graphName << " is " << capacity << "\n";
}

void reznikova::adjacentCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t first_index;
  size_t second_index;
  if (!(is >> first_index >> second_index))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  bool isEdge;
  try
  {
    WorkObject * graph = list.getActiveGraph();
    isEdge = graph->graph_.isEdge(first_index, second_index);
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
  out << "Edge between " << first_index << " and " << second_index;
  if (isEdge == true)
  {
    out << " is exist\n";
  }
  else
  {
    out << " is not exist\n";
  }
}

void reznikova::listCommand(std::ostream & out, reznikova::GraphList & list)
{
  if (list.graphList_.empty())
  {
    out << "graph list is empty\n";
  }
  else
  {
    for (auto graph: list.graphList_)
    {
      out << graph->graph_.getGraphName() << "\n";
    }
  }
}

void reznikova::graphNameCommand(std::ostream & out, reznikova::GraphList & list)
{
  if (list.graphList_.empty())
  {
    out << "graph list is empty\n";
  }
  else
  {
    out << list.getActiveGraph()->graph_.getGraphName() << "\n";
  }
}

void reznikova::bfsCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t index;
  if (!(is >> index))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  try
  {
    WorkObject * graph = list.getActiveGraph();
    graph->graph_.BFS(index, out);
  }
  catch (const std::exception & e)
  {
    throw std::logic_error(e.what());
  }
}

void reznikova::readMatrix(const std::string & filename, std::string & graphname, size_t & num,
  std::vector< size_t > & indices, std::vector< std::vector< size_t > > & matrix)
{
  std::ifstream ifs(filename);
  if (!ifs)
  {
    throw std::logic_error("File does not exist\n");
  }
  if (!std::getline(ifs, graphname))
  {
    throw std::logic_error("Unable to read graph name\n");
  }
  if (!(ifs >> num))
  {
    throw std::logic_error("Unable to read number of vertices\n");
  }
  ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  indices.resize(num);
  for (size_t i = 0; i < num; ++i)
  {
    if (!(ifs >> indices[i]))
    {
      throw std::logic_error("Unable to read vertex indices\n");
    }
  }
  ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  matrix.resize(num, std::vector<size_t>(num));
  size_t extra;
  for (size_t i = 0; i < num; ++i)
  {
    ifs >> extra;
    for (size_t j = 0; j < num; ++j)
    {
      if (!(ifs >> matrix[i][j]))
      {
        throw std::logic_error("Unable to read adjacency matrix\n");
      }
    }
  }
}

void reznikova::clearCommand(std::istream & is, std::ostream & out)
{
  std::string filename;
  if (!(is >> filename))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  std::ofstream ofs(filename, std::ios::trunc);
  if (!ofs.is_open())
  {
    throw std::logic_error("no such file\n");
  }
  ofs.close();
  out << "File " << filename << " were cleared\n";
}

void reznikova::openFileToRead(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string filename;
  if (!(is >> filename))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  std::string graphName;
  size_t num;
  std::vector< std::vector< size_t > > matrix;
  std::vector< size_t > indices;
  readMatrix(filename, graphName, num, indices, matrix);
  Graph graph = createGraphFromAdjacencyMatrix(indices, matrix, graphName);
  list.addToList(graph);
  out << "Graph " << graphName << " were read from file " << filename << "\n";
}

void reznikova::openFileToWrite(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string filename;
  if (!(is >> filename))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (!checkWrongNumParameters(is))
  {
    throw std::logic_error("too much parameters\n");
  }
  std::ofstream ofs(filename);
  if (!ofs.is_open())
  {
    throw std::logic_error("no such file\n");
  }
  WorkObject * graph = list.getActiveGraph();
  graph->graph_.printAdjacencyMatrix(ofs);
  ofs.close();
  out << "Matrix of graph " << graph->graph_.getGraphName() << " were written in file " << filename;
}

void reznikova::openCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string second_parameter;
  if (!(is >> second_parameter))
  {
    throw std::logic_error("wrong parameters\n");
  }
  if (second_parameter == "read")
  {
    openFileToRead(is, out, list);
  }
  else if (second_parameter == "write")
  {
    openFileToWrite(is, out, list);
  }
  else
  {
    throw std::logic_error("wrong parameters\n");
  }
}
