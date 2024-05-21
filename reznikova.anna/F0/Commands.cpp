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
