#include "workingGraph.hpp"
#include "orientedGraph.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

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
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    std::cout << graph.getWeight(num1, num2) << "\n";
  }
  else
  {
    is >> num3;
    graph.createEdge(num2, num3, num1);
  }
}
