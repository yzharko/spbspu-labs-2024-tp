#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <utility>
#include <list>
#include <stack>
#include "delimiter.hpp"
#include "datastruct.hpp"

namespace khoroshkin
{
  template< typename T >
  class Graph
  {
  public:
    Graph();
    ~Graph();

    Graph & operator=(const Graph & obj);

    void egdeAdd(const T & startPoint, const T & endPoint);
    void egdeDelete(const T & startPoint, const T & endPoint);
    void clear();

    void printAdjList();
    void printAdjMatrix();

    std::string sortTopological(bool returnLikeStr = false);
  private:
    std::map< T, std::list< T > > graph;

    void deleteIfVertexUseless(const T & vertex);

    bool checkInVisited(const T & vertex, const std::list< T > & visited);
    void sortRecursive(const T & vertex, std::list< T > & graphList, std::list< T > & visited, std::stack< T > & stack);
  };

  template< typename T >
  std::istream & operator>>(std::istream & is, Graph< T > & dest);

  template< typename T >
  struct Comparator
  {
    bool operator()(const std::pair< T, std::list< T > > & rhs, const std::pair< T, std::list< T > > & lhs);
  };
}

template< typename T >
khoroshkin::Graph< T >::Graph() :
  graph(std::map< T, std::list< T > >())
{}

template< typename T >
khoroshkin::Graph< T >::~Graph()
{
  clear();
}

template< typename T >
khoroshkin::Graph< T > & khoroshkin::Graph< T >::operator=(const Graph & obj)
{
  graph = obj.graph;
  return *this;
}

template< typename T >
void khoroshkin::Graph< T >::egdeAdd(const T & startPoint, const T & endPoint)
{
  if (startPoint == endPoint)
  {
    throw std::invalid_argument("Error: cannot point to itself");
  }

  if (graph.size() != 0)
  {
    bool startAlreadyExist = false;
    for (auto it1 = graph.begin(); it1 != graph.end(); it1++)
    {
      for (auto it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++)
      {
        if (*it2 == startPoint)
        {
          startAlreadyExist = true;
        }
      }

      if ((*it1).first == startPoint)
      {
        startAlreadyExist = true;
      }
      if (graph.find(endPoint) != graph.end())
      {
        startAlreadyExist = true;
      }
    }
    if (!startAlreadyExist)
    {
      throw std::invalid_argument("Error: stick your vertexes to existed graph!\n");
    }
  }

  if (graph.find(startPoint) == graph.end())
  {
    graph.insert(std::make_pair(startPoint, std::list< T >()));
  }
  (*graph.find(startPoint)).second.push_front(endPoint);

  if (graph.find(endPoint) == graph.end())
  {
    graph.insert(std::make_pair(endPoint, std::list< T >()));
  }

  (*graph.find(startPoint)).second.unique();
}

template< typename T >
void khoroshkin::Graph< T >::egdeDelete(const T & startPoint, const T & endPoint)
{
  if (graph.find(startPoint) == graph.end())
  {
    throw std::out_of_range("Error: such egde not exist!\n");
  }

  for (auto it = (*graph.find(startPoint)).second.begin(); it != (*graph.find(startPoint)).second.end(); it++)
  {
    if (*it == endPoint && it == (*graph.find(startPoint)).second.begin())
    {
      (*graph.find(startPoint)).second.pop_front();
      deleteIfVertexUseless(endPoint);
      return;
    }
    else if (*it == endPoint)
    {
      (*graph.find(startPoint)).second.erase(it);
      deleteIfVertexUseless(endPoint);
      return;
    }
  }
  throw std::out_of_range("Error: such egde not exist!\n");
}

template< typename T >
void khoroshkin::Graph< T >::deleteIfVertexUseless(const T & vertex)
{
  bool pointNotUsless = false;
  for (auto it = graph.begin(); it != graph.end(); it++)
  {
    for (auto inList = (*it).second.begin(); inList != (*it).second.end(); inList++)
    {
      if (*inList == vertex)
      {
        pointNotUsless = true;
      }
    }
  }
  std::list< T > dependencies = (*graph.find(vertex)).second;
  if (!pointNotUsless)
  {
    graph.erase(vertex);
  }
  for (auto it = dependencies.begin(); it != dependencies.end(); it++)
  {
    deleteIfVertexUseless(*it);
  }
}

template< typename T >
void khoroshkin::Graph< T >::clear()
{
  for (auto it = graph.begin(); it != graph.end(); ++it)
  {
    (*it).second.clear();
  }
  graph.clear();
}

template< typename T >
void khoroshkin::Graph< T >::printAdjList()
{
  if (graph.size() == 0)
  {
    std::cout << "Look like the graph is empty!\n";
  }
  for (auto it1 = graph.begin(); it1 != graph.end(); it1++)
  {
    std::cout << "Vertex: " << (*it1).first << " -> ";

    for (auto it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++)
    {
      std::cout << *it2;
      std::cout << ((std::next(it2) == (*it1).second.end()) ? "\n" : ", ");
    }

    if ((*it1).second.begin() == (*it1).second.end())
    {
      std::cout << "null" << "\n";
    }
  }
}

template< typename T >
void khoroshkin::Graph< T >::printAdjMatrix()
{
  if (graph.size() == 0)
  {
    std::cout << "Look like the graph is empty!\n";
  }

  if (graph.size() > 0)
  {
    std::cout << "Note: 1 - path exist (without considering direction), 0 - no path\n";
    std::cout << "0 ";
  }

  for (auto it = graph.begin(); it != graph.end(); it++)
  {
    std::cout << (*it).first;
    std::cout << ((std::next(it) == graph.end()) ? "\n" : " ");
  }

  for (auto it1 = graph.begin(); it1 != graph.end(); it1++)
  {
    std::cout << (*it1).first << " ";
    for (auto it2 = graph.begin(); it2 != graph.end(); it2++)
    {
      bool havePath = false;
      for (auto searchIn = (*it2).second.begin(); searchIn != (*it2).second.end(); searchIn++)
      {
        if (*searchIn == (*it1).first)
        {
          havePath = true;
        }
      }
      for (auto searchIn = (*it1).second.begin(); searchIn != (*it1).second.end(); searchIn++)
      {
        if (*searchIn == (*it2).first)
        {
          havePath = true;
        }
      }
      std::cout << ((havePath) ? "1" : "0");
      std::cout << ((std::next(it2) == graph.end()) ? "\n" : " ");
    }
  }
}

template< typename T >
std::string khoroshkin::Graph< T >::sortTopological(bool retunLikeString)
{
  if (graph.empty())
  {
    std::cout << "Graph is empty!\n";
    return "";
  }

  std::list< std::pair< T, std::list< T > > > graphList{};
  for (auto it = graph.begin(); it != graph.end(); it++)
  {
    graphList.push_back(*it);
  }

  Comparator< T > comp;
  graphList.sort(comp);

  std::stack< T > stack;
  std::list< T > visitedVerts;
  for (auto it = graphList.begin(); it != graphList.end(); ++it)
  {
    if (!checkInVisited((*it).first, visitedVerts))
    {
      sortRecursive((*it).first, (*it).second, visitedVerts, stack);
    }
  }

  std::string result = "";
  if (!retunLikeString)
  {
    while (!stack.empty())
    {
      std::cout << stack.top();
      stack.pop();
      std::cout << ((stack.empty()) ? "\n" : ", ");
    }
  }
  else
  {
    while (!stack.empty())
    {
      result.append(std::to_string(stack.top()));
      stack.pop();
      result.append(((stack.empty()) ? "\n" : ", "));
    }
  }
  return result;
}

template< typename T >
bool khoroshkin::Graph< T >::checkInVisited(const T & vertex, const std::list< T > & visited)
{
  for (auto it = visited.begin(); it != visited.end(); it++)
  {
    if (*it == vertex)
    {
      return true;
    }
  }
  return false;
}

template< typename T >
void khoroshkin::Graph< T >::sortRecursive(const T & vertex, std::list< T > & graphList, std::list< T > & visited, std::stack< T > & stack)
{
  visited.push_back(vertex);

  for (auto it = graphList.begin(); it != graphList.end(); it++)
  {
    if (!checkInVisited(*it, visited))
    {
      sortRecursive(*it, (*graph.find(*it)).second, visited, stack);
    }
  }

  stack.push(vertex);
}

template< typename T >
bool khoroshkin::Comparator< T >::operator()(const std::pair< T, std::list< T > > & rhs, const std::pair< T, std::list< T > > & lhs)
{
  if (rhs.second.size() != lhs.second.size())
  {
    return rhs.second.size() < lhs.second.size();
  }
  return rhs.first < lhs.first;
}

template< typename T >
std::istream & khoroshkin::operator>>(std::istream & is, Graph< T > & dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  using sep = DelimiterIO;
  size_t edges;
  if (!(is >> edges))
  {
    is.setstate(std::ios::failbit);
  }
  Graph< T > graph;
  try
  {
    for (size_t i = 0; i < edges; i++)
    {
      T start;
      T end;
      is >> sep{ '(' } >> start >> sep{ ',' } >> end >> sep{ ')' };
      graph.egdeAdd(start, end);
    }
  }
  catch(const std::exception & e)
  {
    is.setstate(std::ios::failbit);
  }
  if (is)
  {
    dest = graph;
  }
  return is;
}

#endif
