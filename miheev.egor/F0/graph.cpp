#include "graph.hpp"
#include <delimiters.hpp>
#include <algorithm>
#include <utility>
#include <vector>
#include <limits>
#include <iterator>

const std::string& miheev::Graph::getName() const noexcept
{
  return name_;
}

void miheev::Graph::setName(const std::string& name)
{
  name_ = name;
}

void miheev::Graph::addNode(int name)
{
  if (nodes_.count(name) > 0)
  {
    throw std::invalid_argument("Insertion error: the node you want to add already exists\n");
  }
  nodes_.insert({name, Node{name}});
}

void miheev::Graph::rmNode(int name)
{
  Node& node = nodes_.at(name);
  auto iter(node.edges.begin());
  for (auto iter(node.edges.begin()); iter != node.edges.end(); iter = node.edges.begin())
  {
    int neighbourName = iter->dest->name;
    rmEdge(name, neighbourName);
  }
  nodes_.erase(name);
}

void miheev::Graph::addEdge(int lnode, int rnode, size_t weight)
{
  bool LnodeDoesNotExists = nodes_.count(lnode) == 0;
  if (LnodeDoesNotExists)
  {
    throw std::invalid_argument("Connection error: no node named " + std::to_string(lnode) + "\n");
  }
  bool rnodeDoesNotExists = nodes_.count(rnode) == 0;
  if (rnodeDoesNotExists)
  {
    throw std::invalid_argument("Connection error: no node named " + std::to_string(rnode) + "\n");
  }
  Node& leftNode = nodes_[lnode];
  Node& rightNode = nodes_[rnode];

  Edge fromLeftToRight{&rightNode, weight};
  Edge fromRightToLeft{&leftNode, weight};

  leftNode.edges.insert(fromLeftToRight);
  leftNode.backLinks.insert({rnode, fromRightToLeft});

  rightNode.edges.insert(fromRightToLeft);
  rightNode.backLinks.insert({lnode, fromLeftToRight});
}

void miheev::Graph::rmEdge(int lnode, int rnode)
{
  bool leftNodeExists = nodes_.count(lnode) > 0;
  if (!leftNodeExists)
  {
    throw std::invalid_argument("Disconnection error: node names" + std::to_string(lnode) + " doesn't exist");
  }
  bool rightNodeExists = nodes_.count(rnode) > 0;
  if (!rightNodeExists)
  {
    throw std::invalid_argument("Disconnection error: node names" + std::to_string(rnode) + " doesn't exist");
  }

//   --->
// A      B
//   <---
  Node& leftNode = nodes_[lnode];
  Node& rightNode = nodes_[rnode];

  leftNode.edges.erase(rightNode.backLinks[lnode]);
  rightNode.backLinks.erase(lnode);

  rightNode.edges.erase(leftNode.backLinks[rnode]);
  leftNode.backLinks.erase(rnode);
}

miheev::Graph::Path miheev::Graph::navigate(int start, int finish)
{
  Dextra dextra(*this);
  Path path = dextra(start, finish);
  return path;
}

std::ostream& miheev::Graph::printNodes(std::ostream& out)
{
  for (auto cIter(nodes_.cbegin()); cIter != nodes_.cend();)
  {
    out << cIter->first;
    if (++cIter != nodes_.end())
    {
      out << ' ';
    }
  }
  out << '\n';
  return out;
}

std::ostream& miheev::Graph::printAllEdges(std::ostream& out) // здесь потребуется алгоритм обхода графа.
{
  Printer printer{{}, false};
  for (auto cIter(nodes_.cbegin()); cIter != nodes_.cend();)
  {
    if (++cIter != nodes_.end() && printer.somethingPrinted)
    {
      out << ' ';
    }
    printer.somethingPrinted = false;
    printer.printUniqueEdges(cIter->second, out);
  }
  return out << '\n';
}

std::ostream& miheev::Graph::Printer::printUniqueEdges(const Node& node, std::ostream& out)
{
  visitedNodes.insert(node.name);
  for (auto cIter(node.edges.cbegin()); cIter != node.edges.cend();)
  {
    int destinationName = cIter->dest->name;
    bool edgeIsUnique = visitedNodes.count(destinationName) == 0;

    if (!edgeIsUnique)
    {
      ++cIter;
      continue;
    }
    out << node.name << " - " << destinationName;
    if (++cIter != node.edges.cend())
    {
      out << ' ';
    }
    somethingPrinted = edgeIsUnique;
  }
  return out;
}

size_t miheev::Graph::Edge::HashFunction::operator()(const Edge& rhs) const
{
  size_t ptrHash = std::hash< Node* >()(rhs.dest);
  size_t weightHash = std::hash< size_t >()(rhs.weight) << 1;
  return ptrHash ^ weightHash;
}

bool miheev::Graph::Edge::operator==(const Edge& rhs) const
{
  return dest == rhs.dest && weight == rhs.weight;
}

miheev::Graph::Dextra::Dextra(const Graph& curGraph):
  graph(curGraph)
{
  for (auto cIter(curGraph.nodes_.begin()); cIter != curGraph.nodes_.end(); cIter++)
  {
    const Node& node = cIter->second;
    unprocessedNodes.insert(node.name);
    timeToNodes.insert({node.name, std::numeric_limits< size_t >::max()});
  }
}

miheev::Graph::Path miheev::Graph::Dextra::operator()(int start, int finish)
{
  bool startDoesntExist = graph.nodes_.count(start) == 0;
  bool finishDoesntExist = graph.nodes_.count(finish) == 0;
  if (startDoesntExist)
  {
    throw std::invalid_argument("Navigation error: no node " + std::to_string(start) + "\n");
  }
  if (finishDoesntExist)
  {
    throw std::invalid_argument("Navigation error: no node " + std::to_string(finish) + "\n");
  }
  updateNodeState(start, 0);
  std::cout << "start node state changed\n";
  calcMinTimeToEach();
  std::cout << "min time to nodes calculated\n";
  Path path;
  path.lenght = timeToNodes.at(finish);
  path.path = findShortestPath(start, finish);
  std::cout << "found shortest way\n";
  return path;
}

void miheev::Graph::Dextra::calcMinTimeToEach()
{
  while(!unprocessedNodes.empty())
  {
    int nameOfNodeWithMinimumTime = getNodeWithMinimumTimeToIt();
    const Node& node = graph.nodes_.at(nameOfNodeWithMinimumTime);
    if (timeToNodes.at(nameOfNodeWithMinimumTime) == std::numeric_limits< size_t >::max())
    { // значит остались только узлы, до которых нельзя добраться
      return;
    }
    recalculateTimeToNeighboursOfTheNode(node);
    unprocessedNodes.erase(node.name);
  }
}

void miheev::Graph::Dextra::recalculateTimeToNeighboursOfTheNode(const Node& node)
{
  for (auto iter(node.edges.begin()); iter != node.edges.end(); iter++)
  {
    int neighbourName = iter->dest->name;
    bool neighbourIsUnprocessed = unprocessedNodes.count(neighbourName) > 0;
    if (neighbourIsUnprocessed)
    {
      size_t timeToNeighbour = timeToNodes.at(node.name) + iter->weight;
      if (timeToNeighbour < timeToNodes.at(neighbourName))
      {
        updateNodeState(neighbourName, timeToNeighbour, node.name);
      }
    }
  }
}

int miheev::Graph::Dextra::getNodeWithMinimumTimeToIt()
{
  size_t minTime = std::numeric_limits< size_t >::max();
  int node = -1;
  for (auto iter(unprocessedNodes.cbegin()); iter != unprocessedNodes.cend(); iter++)
  {
    size_t curTime = timeToNodes.at(*iter);
    if (curTime < minTime)
    {
      node = *iter;
      minTime = curTime;
    }
  }
  return node;
}

std::forward_list< int > miheev::Graph::Dextra::findShortestPath(int start, int finish)
{
  if (timeToNodes.at(finish) == std::numeric_limits< size_t >::max())
  {
    std::invalid_argument("Navigation error: no path exists from node " + std::to_string(start) + " to node " + std::to_string(finish) + '\n');
  }
  std::forward_list< int > path;
  path.push_front(finish);
  do
  {
    int parentNode = nodesParrents.at(finish);
    path.push_front(parentNode);
    finish = parentNode;
  } while (finish != start);
  return path;
}

void miheev::Graph::Dextra::updateNodeState(int node, size_t timeToNode, int parrentNode)
{
  timeToNodes.erase(node);
  timeToNodes.insert({node, timeToNode});

  nodesParrents.erase(node);
  nodesParrents.insert({node, parrentNode});
}

std::istream& operator>>(std::istream& in, miheev::Graph& graph)
{
  // ребро выглядит так: a-b:w
  using del = miheev::DelimiterIO;
  int lnode = -1, rnode = -1;
  size_t weight;
  while(!in.eof())
  {
    in >> lnode >> del{'-'} >> lnode >> del{':'} >> weight;
    if (in.fail())
    {
      std::cerr << "Warning: failed to read one of the nodes in file";
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), ' ');
      continue;
    }
    graph.addNode(lnode);
    graph.addNode(rnode);
    graph.addEdge(lnode, rnode, weight);
  }
}