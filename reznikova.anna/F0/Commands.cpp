#include "Commands.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

void reznikova::getOutputMessage(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}

bool checkExtraSymbols(std::istream & is)
{
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
  {
    return 1;
  }
  return 0;
}

void reznikova::helpCommand(std::ostream & out)
{
  out << "create < graph > < graphname > - создание пустого графа"
  << " с названием  graphname\n";
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
  out << "open < read >< filename > — открытие файла с заданным названием и чтение"
  << "его содержимого\n";
  out << "open < write >< filename > — открытие файла с заданным "
  << "названием для записи данных\n";
}

void reznikova::createCommand(std::istream & is, std::ostream & out,
  reznikova::GraphList & list)
{
  std::string second_parameter;
  std::string graphName;
  if (!(is >> second_parameter) or (second_parameter != "graph") or !(is >> graphName))
  {
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    try
    {
      list.addToList(Graph(graphName));
      out << "Graph " << graphName << " created. This graph is active\n";
    }
    catch (const std::exception & e)
    {
      out << e.what();
    }
  }
}

void reznikova::switchCommand(std::istream & is, std::ostream & out,
  reznikova::GraphList & list)
{
  std::string graphName;
  is >> graphName;
  if (!list.isGraphInList(graphName))
  {
    out << "can't switch to graph which does not exist\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else if (list.findGraphByName(graphName)->isActive_ == true)
  {
    out << "this graph is active already\n";
  }
  else
  {
    list.resetActiveFlags();
    try
    {
      list.findGraphByName(graphName)->isActive_ = true;
      out << "Switched to graph " << graphName << "\n";
    }
    catch (const std::exception & e)
    {
      out << e.what();
    }
  }
}

void addVertex(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t index;
  if (!(is >> index))
  {
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    try
    {
      reznikova::WorkObject * graph = list.getActiveGraph();
      graph->graph_.addVertex(index);
      out << "Vertex with index " << index << " were added\n";
    }
    catch (const std::exception & e)
    {
      out << e.what();
    }
  }
}

void addEdge(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t first_index;
  size_t second_index;
  if (!(is >> first_index >> second_index))
  {
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    try
    {
      reznikova::WorkObject * graph = list.getActiveGraph();
      graph->graph_.addEdge(first_index, second_index);
      out << "Edge between " << first_index << " and " << second_index << " indexes were added\n";
    }
    catch (const std::exception & e)
    {
      out << e.what();
    }
  }
}

void reznikova::addCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string second_parameter;
  if (!(is >> second_parameter))
  {
    out << "wrong parameters\n";
  }
  else
  {
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
      out << "wrong parameters\n";
    }
  }
}

void deleteVertex(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t index;
  if (!(is >> index))
  {
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    try
    {
      reznikova::WorkObject * graph = list.getActiveGraph();
      graph->graph_.removeVertex(index);
      out << "Vertex with index " << index << " were deleted\n";
    }
    catch (const std::exception & e)
    {
      out << e.what();
    }
  }
}

void deleteEdge(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t first_index;
  size_t second_index;
  if (!(is >> first_index >> second_index))
  {
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    try
    {
      reznikova::WorkObject * graph = list.getActiveGraph();
      graph->graph_.removeEdge(first_index, second_index);
      out << "Edge between " << first_index << " and " << second_index << " indexes were deleted\n";
    }
    catch (const std::exception & e)
    {
      out << e.what();
    }
  }
}

void reznikova::deleteCommand(std::istream & is, std::ostream & out,
  reznikova::GraphList & list)
{
  std::string second_parameter;
  if (!(is >> second_parameter))
  {
    out << "wrong parameters\n";
  }
  else
  {
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
      out << "wrong parameters\n";
    }
  }
}

void reznikova::capacityCommand(std::istream & is, std::ostream & out,
  reznikova::GraphList & list)
{
  std::string graphName;
  is >> graphName;
  if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else if (!list.isGraphInList(graphName))
  {
    out << "can't get capacity of a graph which does not exist\n";
  }
  else
  {
    size_t capacity;
    try
    {
      capacity = list.findGraphByName(graphName)->graph_.getCapacity();
      out << "Capacity of graph " << graphName << " is " << capacity << "\n";
    }
    catch (const std::exception & e)
    {
      throw std::logic_error(e.what());
    }
  }
}

void reznikova::adjacentCommand(std::istream & is, std::ostream & out,
  reznikova::GraphList & list)
{
  size_t first_index;
  size_t second_index;
  if (!(is >> first_index >> second_index))
  {
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    bool isEdge;
    try
    {
      WorkObject * graph = list.getActiveGraph();
      isEdge = graph->graph_.isEdge(first_index, second_index);
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
    catch (const std::exception & e)
    {
      out << e.what();
    }
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
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    try
    {
      WorkObject * graph = list.getActiveGraph();
      graph->graph_.BFS(index, out);
    }
    catch (const std::exception & e)
    {
      out << e.what();
    }
  }
}

void readMatrix(const std::string & filename, std::string & graphname, size_t & num,
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
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    std::ofstream ofs(filename, std::ios::trunc);
    if (!ofs.is_open())
    {
      out << "no such file\n";
    }
    else
    {
      ofs.close();
      out << "File " << filename << " were cleared\n";
    }
  }
}

void openFileToRead(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string filename;
  if (!(is >> filename))
  {
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    std::string graphName;
    size_t num;
    std::vector< std::vector< size_t > > matrix;
    std::vector< size_t > indices;
    readMatrix(filename, graphName, num, indices, matrix);
    reznikova::Graph graph = reznikova::createGraphFromAdjacencyMatrix(indices, matrix, graphName);
    list.addToList(graph);
    out << "Graph " << graphName << " were read from file " << filename << "\n";
  }
}

void openFileToWrite(std::istream & is, std::ostream & out,
  reznikova::GraphList & list)
{
  std::string filename;
  if (!(is >> filename))
  {
    out << "wrong parameters\n";
  }
  else if (checkExtraSymbols(is))
  {
    out << "wrong num of parameters\n";
  }
  else
  {
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
      out << "no such file\n";
    }
    else
    {
      reznikova::WorkObject * graph = list.getActiveGraph();
      graph->graph_.printAdjacencyMatrix(ofs);
      ofs.close();
      out << "Matrix of graph " << graph->graph_.getGraphName() << " were written in file ";
      out << filename;
    }
  }
}

void reznikova::openCommand(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  std::string second_parameter;
  if (!(is >> second_parameter))
  {
    out << "wrong parameters\n";
  }
  else if (second_parameter == "read")
  {
    openFileToRead(is, out, list);
  }
  else if (second_parameter == "write")
  {
    openFileToWrite(is, out, list);
  }
  else
  {
    out << "wrong parameters\n";
  }
}
