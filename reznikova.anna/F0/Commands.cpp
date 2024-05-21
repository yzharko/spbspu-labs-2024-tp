#include "Commands.hpp"
#include <iostream>
#include <sstream>

void reznikova::helpCommand(std::ostream & out)
{
  out << "create < graph > < graphname > - создание пустого графа с названием  graphname\n";
  out << "add < vertice > < index > – создание вершины графа с индексом index\n";
  out << "add < edge > < first_vertice, second_vertice > - создание ребра между вершинами first_vertice и second_vertice\n";
  out << "delete < vertice > < name > - удаление вершины name\n";
  out << "delete < edge > < first_vertice, second_vertice > - удаление ребра между вершинами first_vertice и second_vertice\n";
  out << "capacity <  graphname > - вывод количества вершин в графе graphname\n";
  out << "adjacent < first_vertice, second_ vertice > - проверяет наличие ребра между вершинами first_vertice и second_vertice\n";
  out << "list — вывод списка графов\n";
  out << "switch < graphName > - переключение на работу с графом GraphName\n";
  out << "graphname — выводит имя графа, над которым ведется работа\n";
  out << "BFS < first_vertice > - возвращает список вершин в порядке обхода в ширину из исходной вершины first_vertice\n";
  out << "clean < filename > — очищает содержимое файла\n";
  out << "open < read >< filename > — открытие файла с заданным названием и чтение его содержимого\n";
  out << "open < write >< filename > — открытие файла с заданным названием для записи данных\n";
}
void reznikova::addVertex(std::istream & is, std::ostream & out, reznikova::GraphList & list)
{
  size_t index;
  if (!(is >> index))
  {
    throw std::logic_error("wrong parameters\n");
  }
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
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
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
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
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
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
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
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
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
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
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
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
  std::string extra;
  if (std::getline(is, extra) and !extra.empty())
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

void reznikova::readMatrix(std::istream & is, std::vector< std::vector< size_t > > & table)
{
  std::string line;
  while (std::getline(is, line))
  {
    std::istringstream iss(line);
    std::vector< size_t > row;
    size_t num;
    while (iss >> num) 
    {
      row.push_back(num);
    }
    table.push_back(row);
  }
  size_t n = table.size();
  bool is_square = true;
  for (const auto & row : table)
  {
    if (row.size() != n)
    {
      is_square = false;
      break;
    }
  }
  if (!is_square) 
  {
     throw std::logic_error("The input table is not square\n");
  }
}
