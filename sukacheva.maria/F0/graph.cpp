#include "graph.hpp"
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <iterator>

sukacheva::Graph::Graph(std::string GraphName_):
  GraphName(GraphName_),
  AdjacencyList()
{}

void sukacheva::Graph::addVertex(std::string& name)
{
  auto it = std::find_if(
    VertexesList.begin(),
    VertexesList.end(),
    [&name](const auto& vertex) { return vertex.second == name; }
  );
  if (it != VertexesList.end())
  {
    throw std::logic_error("Vertex with this name already exists.\n");
  }
  size_t key = AdjacencyList.size();
  VertexesList.insert({key, name});
  std::map< size_t, size_t > edges;
  AdjacencyList.insert({key, edges});
}

void sukacheva::Graph::addEdge(std::string& start, std::string& end, size_t weight)
{
  size_t keyStart = getVertexIndex(start);
  size_t keyEnd = getVertexIndex(end);
  if (keyStart == keyEnd)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  auto it = AdjacencyList[keyStart].find(keyEnd);
  if (it != AdjacencyList[keyStart].end())
  {
    throw std::logic_error("Edge between these vertices already exists.\n");
  }
  AdjacencyList[keyStart][keyEnd] = weight;
  AdjacencyList[keyEnd][keyStart] = weight;
}

void sukacheva::Graph::deleteVertex(std::string name)
{
  size_t key = getVertexIndex(name);
  AdjacencyList.erase(key);
  VertexesList.erase(key);
  std::map< size_t, std::string > updatedVertexesList;
  std::transform(
    VertexesList.begin(),
    VertexesList.end(),
    std::inserter(updatedVertexesList, updatedVertexesList.end()),
    [key](const auto& vertex) { return std::make_pair(vertex.first > key ? vertex.first - 1 : vertex.first, vertex.second); }
  );
  VertexesList = std::move(updatedVertexesList);

  std::map< size_t, std::map< size_t, size_t > > updatedAdjacencyList;
  std::transform(
    AdjacencyList.begin(),
    AdjacencyList.end(),
    std::inserter(updatedAdjacencyList, updatedAdjacencyList.end()),
    [key](auto& adjPair) {
      size_t newKey = adjPair.first > key ? adjPair.first - 1 : adjPair.first;
      std::map< size_t, size_t > updatedAdj;
      std::transform(
        adjPair.second.begin(),
        adjPair.second.end(),
        std::inserter(updatedAdj, updatedAdj.end()),
        [key](const auto& adj) {
          return std::make_pair(adj.first > key ? adj.first - 1 : adj.first, adj.second);
        });
      return std::make_pair(newKey, std::move(updatedAdj));
    });
  AdjacencyList = std::move(updatedAdjacencyList);
}

void sukacheva::Graph::deleteEdge(std::string start, std::string end)
{
  size_t keyStart = getVertexIndex(start);
  size_t keyEnd = getVertexIndex(end);
  if (keyStart != keyEnd)
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

size_t sukacheva::Graph::getVertexIndex(std::string& name)
{
  auto it = std::find_if(
    VertexesList.begin(),
    VertexesList.end(),
    [&name](const auto& vertex) { return vertex.second == name; }
  );
  if (it != VertexesList.end())
  {
    return it->first;
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

std::pair< std::map<size_t, size_t >, std::map< size_t, size_t > > sukacheva::Graph::dijkstraDistances(std::string name)
{
  size_t startKey = getVertexIndex(name);
  std::map<size_t, size_t> distances;
  std::map<size_t, size_t> predecessors;
  std::map<size_t, bool> visited;
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
        predecessors[it->first] = minVertex;
      }
    }
  }
  std::pair< std::map<size_t, size_t >, std::map< size_t, size_t > > result = { distances, predecessors };
  return result;
}

std::vector< std::string > sukacheva::Graph::dijkstraPath(const std::map<size_t, size_t>& predecessors, std::string start, std::string end)
{
  std::vector< std::string > path;
  size_t keyStart = getVertexIndex(start);
  size_t keyEnd = getVertexIndex(end);
  for (size_t at = keyEnd; at != keyStart; at = predecessors.at(at))
{
    path.push_back(VertexesList[at]);
  }
  path.push_back(VertexesList[keyStart]);
  std::reverse(path.begin(), path.end());
  return path;
}
