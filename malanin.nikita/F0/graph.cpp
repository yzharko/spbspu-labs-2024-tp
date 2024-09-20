#include "graph.hpp"
#include <delimiters.hpp>
#include <algorithm>
#include <utility>
#include <vector>
#include <limits>
#include <sstream>
#include <iterator>
#include <algorithm>

void malanin::Graph::addNode(int name)
{
  if (contains(name))
  {
    throw std::invalid_argument("[ERROR](insertion): the node you want to add already exists");
  }
  nodes_.insert({name, Node{name}});
}

void malanin::Graph::rmNode(int name)
{
  Node& node = nodes_.at(name);
  for (auto iter(node.edges.begin()); iter != node.edges.end(); iter = node.edges.begin())
  {
    int neighbourName = iter->dest;
    rmEdge(name, neighbourName);
    rmEdge(neighbourName, name);
  }
  nodes_.erase(name);
}

void malanin::Graph::addEdge(int lnode, int rnode, size_t weight)
{
  if (!contains(lnode))
  {
    throw std::invalid_argument("[ERROR](connection): no node named " + std::to_string(lnode));
  }
  if (!contains(rnode))
  {
    throw std::invalid_argument("[ERROR](connection): no node named " + std::to_string(rnode));
  }

  Node& leftNode = nodes_[lnode];
  Node& rightNode = nodes_[rnode];

  Edge fromLeftToRight{rightNode.name, weight};

  leftNode.edges.insert(fromLeftToRight);
  rightNode.backLinks.insert({lnode, fromLeftToRight});
}

void malanin::Graph::rmEdge(int lnode, int rnode)
{
  if (!contains(lnode))
  {
    throw std::invalid_argument("[ERROR](connection): node named" + std::to_string(lnode) + " doesn't exist");
  }
  if (!contains(rnode))
  {
    throw std::invalid_argument("[ERROR](connection): node named" + std::to_string(rnode) + " doesn't exist");
  }

  Node& leftNode = nodes_[lnode];
  Node& rightNode = nodes_[rnode];

  leftNode.edges.erase(rightNode.backLinks[lnode]);
  rightNode.backLinks.erase(lnode);
}

bool malanin::Graph::pathExists(int start, int finish) const
{
  DeepDetourer dd(*this);
  return dd.checkPathExistance(start, finish);
}

size_t malanin::Graph::countPaths(int start, int finish) const
{
  DeepDetourer dd(*this);
  return dd.countPaths(start, finish);
}

size_t malanin::Graph::calcPathLength(const std::deque< int >& path) const
{
  size_t length = 0;
  for (auto iter(next(path.begin())); iter != path.end(); ++iter)
  {
    auto& backlinks = nodes_.at(*iter).backLinks;
    length += backlinks.at(*std::prev(iter)).weight;
  }
  return length;
}

std::forward_list< int > dequeToForward(std::deque < int > dq)
{
  return std::forward_list< int >(dq.begin(), dq.end());
}

malanin::Graph::Path malanin::Graph::findAnyPath(int start, int finish) const
{
  DeepDetourer dd(*this);
  std::deque< int > path = dd.findAnyPath(start, finish);
  return Path{calcPathLength(path), dequeToForward(path)};
}

void malanin::Graph::printPath(const Path& path, std::ostream& out) const
{
  out << "Path nodes: ";
  for (auto iter(path.path.begin()); iter != path.path.end(); ++iter)
  {
    out << *iter << ' ';
  }
  out << "\b; cumulative length: " << path.lenght << '\n';
}

void malanin::Graph::printAnyPath(int start, int finish, std::ostream& out) const
{
  DeepDetourer dd(*this);
  Path path = findAnyPath(start, finish);
  printPath(path, out);
}

std::forward_list< malanin::Graph::Path > malanin::Graph::findAllPaths(int start, int finish) const
{
  DeepDetourer dd(*this);
  std::forward_list< Path > result;
  // Великая путаница с типами - что же на самом деле считать путем
  std::forward_list< std::deque< int > > paths = dd.findAllPaths(start, finish);
  for (std::deque< int > rawPath : paths)
  {
    result.push_front(Path {calcPathLength(rawPath), dequeToForward(rawPath)});
  }
  return result;
}

void malanin::Graph::printAllPaths(int start, int finish, std::ostream& out) const
{
  std::forward_list< Path > paths = findAllPaths(start, finish);
  for (Path path : paths)
  {
    printPath(path, out);
  }
}

std::ostream& malanin::Graph::printNodes(std::ostream& out) const
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

std::ostream& malanin::Graph::printAllEdges(std::ostream& out) const
{
  for (auto iter(nodes_.begin()); iter != nodes_.end(); ++iter)
  {
    for (const Edge& edge : iter->second.edges)
    {
      out << iter->second.name << '-' << edge.dest << ':' << edge.weight << " ";
    }
  }
  out << "\b\n"; // \b - это бэкспейс, потому что мне лень логически задавать когда надо не ставить пробел
  return out;
}

std::ostream& malanin::Graph::Printer::printUniqueEdges(const Node& node, std::ostream& out)
{
  visitedNodes.insert(node.name);
  for (auto cIter(node.edges.cbegin()); cIter != node.edges.cend(); cIter++)
  {
    int destinationName = cIter->dest;
    size_t weight = cIter -> weight;
    bool edgeIsUnique = visitedNodes.count(destinationName) == 0;
    if (edgeIsUnique)
    {
      if (cIter != node.edges.begin())
      {
        out << ' ';
      }
      out << node.name << '-' << destinationName << ':' << weight;
    }
  }
  return out;
}

bool malanin::Graph::Printer::hasUniqueEdges(const Node& node) const
{
  for (auto cIter(node.edges.cbegin()); cIter != node.edges.cend(); cIter++)
  {
    int destName = cIter->dest;
    bool isUnique = visitedNodes.count(destName) == 0;
    if (isUnique)
    {
      return true;
    }
  }
  return false;
}

size_t malanin::Graph::Edge::HashFunction::operator()(const Edge& rhs) const
{
  size_t ptrHash = std::hash< int >()(rhs.dest);
  size_t weightHash = std::hash< size_t >()(rhs.weight) << 1;
  return ptrHash ^ weightHash;
}

bool malanin::Graph::Edge::operator==(const Edge& rhs) const
{
  return dest == rhs.dest && weight == rhs.weight;
}

std::istream& malanin::operator>>(std::istream& in, malanin::Graph& graph)
{
  using del = malanin::DelimiterIO;

  int lnode = -1, rnode = -1;
  size_t weight;

  while(!in.eof())
  {
    in >> lnode >> del{'-'} >> rnode >> del{':'} >> weight;
    if (in.fail() && !in.eof())
    {
      std::cerr << "Warning: failed to read one of the nodes\n";
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), ' ');
      continue;
    }
    if (!graph.contains(lnode))
    {
      graph.addNode(lnode);
    }
    if (!graph.contains(rnode))
    {
      graph.addNode(rnode);
    }
    graph.addEdge(lnode, rnode, weight);
  }
  return in;
}

bool malanin::Graph::contains(int nodeName) const
{
  return nodes_.count(nodeName) > 0;
}

malanin::Graph::DeepDetourer::DeepDetourer(const Graph& curGraph):
  graph_(curGraph)
{}

bool malanin::Graph::DeepDetourer::checkPathExistance(int begin, int end)
{
  return !findAnyPath(begin, end).empty();
}

size_t malanin::Graph::DeepDetourer::countPaths(int begin, int end)
{
  std::forward_list< Path > paths = findAllPaths(begin, end);
  return std::distance(paths.begin(), paths.end());
}

bool malanin::Graph::DeepDetourer::getPath(int begin, int end, Path& path)
{
  if (begin == end)
  {
    path.push_front(begin);
    return true;
  }
  passedNodes_.insert(begin);
  auto& edges = graph_.nodes_.at(begin).edges;
  for (auto edgeIter(edges.begin()); edgeIter != edges.end(); ++ edgeIter)
  {
    if (!passedNodes_.count(edgeIter->dest))
    {
      if (getPath(edgeIter->dest, end, path))
      {
        path.push_front(begin);
        return true;
      }
    }
  }
  return false;
}

malanin::Graph::DeepDetourer::Path malanin::Graph::DeepDetourer::findAnyPath(int begin, int end)
{
  Path path;
  getPath(begin, end, path);
  return path;
}

bool malanin::Graph::DeepDetourer::doPathContainsNode(int node, const Path& path)
{
  for (auto iter(path.begin()); iter != path.end(); ++iter)
  {
    if (*iter == node)
    {
      return true;
    }
  }
  return false;
}

void malanin::Graph::DeepDetourer::getAllPaths(int begin, int end, std::forward_list< Path >& paths, Path curPath)
{
  if (begin == end)
  {
    Path pathCopy = curPath;
    pathCopy.push_back(end);
    paths.push_front(pathCopy);
  }
  curPath.push_back(begin);
  auto& edges = graph_.nodes_.at(begin).edges;
  for (auto edgeIter(edges.begin()); edgeIter != edges.end(); ++ edgeIter)
  {
    if (!doPathContainsNode(edgeIter->dest, curPath))
    {
      getAllPaths(edgeIter->dest, end, paths, curPath);
    }
  }
  passedNodes_.erase(begin);
}

std::forward_list< malanin::Graph::DeepDetourer::Path > malanin::Graph::DeepDetourer::findAllPaths(int begin, int end)
{
  std::forward_list< Path > paths;
  getAllPaths(begin, end, paths, Path());
  return paths;
}
