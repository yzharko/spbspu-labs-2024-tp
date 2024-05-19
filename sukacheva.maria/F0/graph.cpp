#include "graph.hpp"
#include <queue>

sukacheva::Graph::Graph(std::string GraphName_):
  GraphName(GraphName_),
  AdjacencyList()
{}

void sukacheva::Graph::addVertex(std::string name)
{
  size_t key = AdjacencyList.size();
  VertexesList.insert({key, name});
  std::map< size_t, size_t > edges;
  AdjacencyList.insert({ key, edges});
}

void sukacheva::Graph::addEdge(std::string start, std::string end, size_t weight)
{
  size_t keyStart = 0;
  size_t keyEnd = 0;
  using const_iterator = typename std::map< size_t, std::string >::const_iterator;
  for (const_iterator it = VertexesList.cbegin(); it != VertexesList.cend(); ++it)
  {
    if (it->second == start)
    {
      keyStart = it->first;
    }
    if (it->second == end)
    {
      keyEnd = it->first;
    }
  }
  if (keyStart == keyEnd)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  AdjacencyList[keyStart][keyEnd] = weight;
  AdjacencyList[keyEnd][keyStart] = weight;
}

void sukacheva::Graph::deleteVertex(std::string name)
{
  using const_iterator = typename std::map< size_t, std::string >::const_iterator;
  size_t key = 0;
  bool flag = false;
  for (const_iterator it = VertexesList.cbegin(); it != VertexesList.cend(); ++it)
  {
    if (it->second == name)
    {
      key = it->first;
      flag = true;
    }
  }
  if (!flag)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  AdjacencyList.erase(key);
  VertexesList.erase(key);
}

void sukacheva::Graph::deleteEdge(std::string start, std::string end)
{
  size_t keyStart = 0;
  size_t keyEnd = 0;
  bool startFlag = false;
  bool endFlag = false;
  using const_iterator = std::map< size_t, std::string >::const_iterator;
  for (const_iterator it = VertexesList.cbegin(); it != VertexesList.cend(); ++it)
  {
    if (it->second == start)
    {
      keyStart = it->first;
      startFlag = true;
    }
    if (it->second == end)
    {
      keyEnd = it->first;
      endFlag = true;
    }
  }
  if (startFlag && endFlag)
  {
    AdjacencyList[keyStart].erase(keyEnd);
    AdjacencyList[keyEnd].erase(keyStart);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

size_t sukacheva::Graph::capacity()
{
  return AdjacencyList.size();
}

void sukacheva::Graph::clear()
{
  AdjacencyList.clear();
  VertexesList.clear();
}

std::map<size_t, size_t> sukacheva::Graph::dijkstra(size_t startKey)
{
  std::map< size_t, size_t > distances;
  std::map< size_t, bool > visited;
  using iterator = std::map< size_t, std::string >::iterator;
  for (iterator it = VertexesList.begin(); it != VertexesList.end(); it++)
  {
    distances[it->first] = std::numeric_limits< size_t >::max();
    visited[it->first] = false;
  }
  distances[startKey] = 0;
  for (size_t i = 0; i < VertexesList.size(); ++i)
  {
    size_t minDistance = std::numeric_limits<size_t>::max();
    size_t minVertex = startKey;
    for (std::map< size_t, size_t >::iterator it = distances.begin(); it != distances.end(); it++)
    {
      if (!visited[it->first] && it->second <= minDistance)
      {
        minDistance = it->second;
        minVertex = it->first;
      }
    }
    if (minDistance == std::numeric_limits<size_t>::max())
    {
      break;
    }
    visited[minVertex] = true;
    for (std::map< size_t, size_t >::iterator it = AdjacencyList[minVertex].begin(); it != AdjacencyList[minVertex].end(); it++)
    {
      if (!visited[it->first] && distances[minVertex] + it->second < distances[it->first])
      {
        distances[it->first] = distances[minVertex] + it->second;
      }
    }
  }
  return distances;
}
