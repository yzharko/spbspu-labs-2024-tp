#include "workingGraph.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include "orientedGraph.hpp"

bool kovshikov::isDigit(char ch)
{
  return std::isdigit(ch);
}

void kovshikov::add(Graph& graph, std::istream& is)
{
  std::string parameter;
  size_t key;
  is >> parameter;
  is >> key;
  if(graph.haveThisKey(key) == true)
  {
    throw std::logic_error("This key is already in use");
  }
  else
  {
    if(std::all_of(parameter.begin(), parameter.end(), isDigit) == true)
    {
      unsigned long long count = std::stoll(parameter);
      std::string graphname;
      is >> graphname;
      graph.addVertex(key, graphname);
      graph.connect(key, count, 1);
    }
    else
    {
      graph.addVertex(key, parameter);
    }
  }
}

std::string kovshikov::getGraphname(std::pair< std::string, Graph > element)
{
  return element.first;
}

void kovshikov::connect(Graph& graph, std::istream& is)
{
  size_t num1;
  size_t num2;
  size_t num3;
  is >> num1 >> num2;
  if(is.peek() == '\n')
  {
    std::cout << graph.getWeight(num1, num2) << "\n";
  }
  else
  {
    is >> num3;
    graph.createEdge(num2, num3, num1);
  }
}

void kovshikov::getDouble(Graph& graph, std::istream& is)
{
  size_t num1;
  size_t num2;
  size_t num3;
  is >> num1 >> num2;
  if(is.peek() == '\n')
  {
    if(graph.isDouble(num1, num2) == true)
    {
      std::cout << "TRUE" << "\n";
    }
    else
    {
      std::cout << "FALSE" << "\n";
    }
  }
  else
  {
    is >> num3;
    graph.createEdge(num2, num3, num1);
    graph.createEdge(num3, num2, num1);
  }
}

void kovshikov::deleteElement(Graph& graph, std::istream& is)
{
  size_t num1;
  size_t num2;
  size_t num3;
  is >> num1;
  if(is.peek() == '\n')
  {
    graph.deleteVertex(num1);
  }
  else
  {
    is >> num2 >> num3;
    try
    {
      graph.decreaseWeight(num2, num3, num1);
    }
    catch(const std::logic_error& e)
    {
      throw;
    }
  }
}

void kovshikov::getWeight(Graph& graph, std::istream& is)
{
  size_t key;
  is >> key;
  std::cout << graph.getVertexWeight(key) << "\n";
}

void kovshikov::getDegree(Graph& graph, std::istream& is)
{
  size_t key;
  is >> key;
  std::cout << graph.getDegree(key) << "\n";
}

void kovshikov::getOwn(Graph& graph, std::istream& is)
{
  size_t key;
  is >> key;
  std::cout << graph.getOwn(key) << "\n";
}

void kovshikov::getCountVertex(Graph& graph, std::ostream& out)
{
  out << graph.getSize() << "\n";
}

void kovshikov::outEdge(Graph& graph, std::ostream& out)
{
  out << graph.getEdges() << "\n";
}

void kovshikov::outMax(Graph& graph, std::ostream& out)
{
  graph.getMax(out);
}

void kovshikov::outName(std::string key, std::ostream& out)
{
  out << key << "\n";
}

void kovshikov::change(Graph& graph, std::istream& is)
{
  size_t count;
  size_t who;
  size_t with;
  is >> count >> who >> with;
  graph.change(count, who, with);
}
