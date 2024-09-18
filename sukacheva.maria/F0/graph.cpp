#include "graph.hpp"
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iostream>

sukacheva::Graph::Graph(std::string GraphName_):
  GraphName(GraphName_),
  AdjacencyList()
{}

void sukacheva::Graph::addVertex(std::string& name)
{
  if (isVertexExist(name))
  {
    throw std::logic_error("Vertex with this name already exists.\n");
  }
  size_t key = AdjacencyList.size();
  VertexesList.insert({key, name});
  std::map< size_t, size_t > edges;
  AdjacencyList.insert({key, edges});
}

bool sukacheva::Graph::isEdgeExist(std::string& start, std::string& end)
{
  size_t keyStart = getVertexIndex(start);
  size_t keyEnd = getVertexIndex(end);
  auto it = AdjacencyList[keyStart].find(keyEnd);
  if (it != AdjacencyList[keyStart].end())
  {
    return true;
  }
  return false;
}

void sukacheva::Graph::addEdge(std::string& start, std::string& end, size_t weight)
{
  size_t keyStart = getVertexIndex(start);
  size_t keyEnd = getVertexIndex(end);
  if (keyStart == keyEnd)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  if (isEdgeExist(start, end))
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
  std::map< size_t, size_t > distances;
  std::map< size_t, size_t > predecessors;
  std::map< size_t, bool > visited;
  std::transform(
    VertexesList.begin(),
    VertexesList.end(),
    std::inserter(distances, distances.end()),
    [](const std::pair< size_t, std::string >& vertex) { return std::make_pair(vertex.first, std::numeric_limits< size_t >::max()); }
  );

  std::transform(
    VertexesList.begin(),
    VertexesList.end(),
    std::inserter(visited, visited.end()),
    [](const std::pair< size_t, std::string >& vertex) { return std::make_pair(vertex.first, false); }
  );
  distances[startKey] = 0;

  for (size_t i = 0; i < VertexesList.size(); ++i)
  {
    size_t minDistance = std::numeric_limits< size_t >::max();
    size_t minVertex = startKey;
    for (std::map< size_t, size_t >::iterator it = distances.begin(); it != distances.end(); it++)
    {
      if (!visited[it->first] && it->second <= minDistance)
      {
        minDistance = it->second;
        minVertex = it->first;
      }
    }
    if (minDistance == std::numeric_limits< size_t >::max())
    {
      predecessors[i] = std::numeric_limits< size_t >::max();
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
  std::pair< std::map< size_t, size_t >, std::map< size_t, size_t > > result = { distances, predecessors };
  return result;
}

std::vector< std::string > sukacheva::Graph::dijkstraPath(const std::map<size_t, size_t>& predecessors, std::string start, std::string end)
{
  std::vector< std::string > path;
  size_t keyStart = getVertexIndex(start);
  size_t keyEnd = getVertexIndex(end);
  for (size_t at = keyEnd; at != keyStart; at = predecessors.at(at))
  {
    if (at == std::numeric_limits< size_t >::max())
    {
      path.push_back("unattainable");
      return path;
    }
    path.push_back(VertexesList[at]);
  }
  path.push_back(VertexesList[keyStart]);
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector< std::vector< size_t > > sukacheva::Graph::weightTable()
{
  size_t vertexCount = VertexesList.size();
  std::vector< std::vector< size_t > > matrix(vertexCount, std::vector< size_t >(vertexCount, std::numeric_limits< size_t >::max()));
  for (size_t i = 0; i < vertexCount; ++i)
  {
    matrix[i][i] = 0;
  }
  for (auto it = AdjacencyList.cbegin(); it != AdjacencyList.cend(); ++it)
  {
    size_t from = it->first;
    const auto& edges = it->second;
    for (auto edgeIt = edges.cbegin(); edgeIt != edges.cend(); ++edgeIt)
    {
      size_t to = edgeIt->first;
      size_t weight = edgeIt->second;
      matrix[from][to] = weight;
    }
  }
  return matrix;
}

bool sukacheva::Graph::isVertexExist(std::string& name)
{
  auto it = std::find_if(
    VertexesList.begin(),
    VertexesList.end(),
    [&name](const auto& vertex) { return vertex.second == name; }
  );
  if (it != VertexesList.end())
  {
    return true;
  }
  return false;
}

std::istream& sukacheva::operator>>(std::istream& in, Graph& applicant)
{
  std::istream::sentry guard(in);
  Graph graph;
  if (!guard)
  {
    return in;
  }
  size_t vertices = 0;
  size_t edges = 0;
  in >> graph.GraphName >> vertices >> edges;
  for (size_t i = 0; i < edges + 1; i++)
  {
    std::string start;
    std::string end;
    size_t weight;
    std::istream::pos_type startPos = in.tellg();
    if (!(in >> start) || !(in >> end) || !(in >> weight))
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      in.seekg(startPos);
      break;
    }
    else
    {
      if (!graph.isVertexExist(start))
      {
        graph.addVertex(start);
      }
      if (!graph.isVertexExist(end))
      {
        graph.addVertex(end);
      }
      if (!graph.isEdgeExist(start, end))
      {
        graph.addEdge(start, end, weight);
      }
    }
    if (in)
    {
      applicant = graph;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
