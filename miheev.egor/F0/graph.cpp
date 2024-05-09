#include "graph.hpp"
#include <delimiters.hpp>
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
