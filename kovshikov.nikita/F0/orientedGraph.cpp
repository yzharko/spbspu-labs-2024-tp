#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "orientedGraph.hpp"

void kovshikov::Graph::addVertex(size_t key, std::string str)
{
  tree[key] = Node(str);
}

bool kovshikov::Graph::isEmpty() const noexcept
{
  return tree.empty();
}


size_t kovshikov::Graph::getSize() const noexcept
{
  return tree.size();
}

size_t kovshikov::getKey(std::pair< size_t, Graph::Node > vertex)
{
  return vertex.first;
}

void kovshikov::Graph::outKeys()
{
  std::vector< size_t > keysList;
  std::transform(tree.begin(), tree.end(), std::back_inserter(keysList), getKey);
  using output_it = std::ostream_iterator< size_t >;
  std::copy(keysList.cbegin(), keysList.cend(), output_it{std::cout, " "});
  std::cout << "\n";
}

void kovshikov::Graph::deleteVertex(size_t key)
{
  if(tree.find(key) == tree.end())
  {
    throw std::logic_error("<There is no vertex>");
  }
  tree.erase(key);
}

void kovshikov::Graph::createEdge(size_t keyWho, size_t keyWith, size_t weight)
{
  tree.at(keyWho).edges[keyWith] = weight;
}

void kovshikov::Graph::decreaseWeight(size_t keyWho, size_t keyWith, size_t decrease)
{
  if(tree.at(keyWho).edges[keyWith] < decrease)
  {
    throw std::logic_error("<The edge weight is less than the entered value>");
  }
  else
  {
    tree.at(keyWho).edges[keyWith] -= decrease;
    if(tree.at(keyWho).edges[keyWith] == 0)
    {
      tree.at(keyWho).edges.erase(keyWith);
    }
  }
}

size_t kovshikov::Graph::getWeight(size_t keyWho, size_t keyWith)
{
  if(tree.find(keyWho) != tree.end())
  {
    if(tree.at(keyWho).edges.find(keyWith) != tree.at(keyWho).edges.end())
    {
      return tree.at(keyWho).edges.at(keyWith);
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

void kovshikov::Graph::deleteEdge(size_t keyWho, size_t keyWith)
{
  if(getWeight(keyWho, keyWith) == 0)
  {
    throw std::logic_error("<The edge does not exist>");
  }
  else
  {
    tree.at(keyWho).edges.erase(keyWith);
  }
}
