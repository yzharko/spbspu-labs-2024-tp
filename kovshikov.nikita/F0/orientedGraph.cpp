#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>
#include <numeric>
#include <vector>
#include "orientedGraph.hpp"

//проверка-исключения
void kovshikov::Graph::haveThisVertex(size_t key)
{
  if(tree.find(key) == tree.end())
  {
    throw std::logic_error("This key does not exist");
  }
}

void kovshikov::Graph::haveNot(size_t keyWho, size_t keyWith)
{
  bool haveWho = tree.find(keyWho) == tree.end();
  bool haveWith = tree.find(keyWith) == tree.end();
  if(haveWho || haveWith)
  {
    throw std::logic_error("At least one key does not exist");
  }
}

bool kovshikov::Graph::haveThisKey(size_t key)
{
  return tree.find(key) != tree.end();
}

bool kovshikov::Graph::isDouble(size_t key1, size_t key2)
{
  bool have1 = tree.at(key1).edges.find(key2) != tree.at(key1).edges.end();
  bool have2 = tree.at(key2).edges.find(key1) != tree.at(key2).edges.end();
  return have1 && have2;
}

bool kovshikov::noThis(size_t whoKey, size_t randomKey)
{
  return whoKey != randomKey;
}

//возвращение элементов, вспомогатедьные функции
void kovshikov::Graph::getConnectKeys(std::vector< size_t >& connectKeys, size_t whoKey)
{
   std::vector< size_t > keys;
   std::transform(tree.begin(), tree.end(), std::back_inserter(keys), getKey);
   std::copy_if(keys.begin(), keys.end(), std::back_inserter(connectKeys), std::bind(noThis, whoKey, std::placeholders::_1));
}

std::string kovshikov::Graph::getVertex(std::pair< size_t, Node > vertex)
{
  return vertex.second.value;
}

size_t kovshikov::Graph::getCountEdge(std::pair< size_t, Node > vertex)
{
  return vertex.second.edges.size();
}

size_t kovshikov::getKey(std::pair< size_t, Graph::Node > vertex)
{
  return vertex.first;
}

size_t kovshikov::getWith(std::pair< size_t, size_t > edge)
{
  return edge.first;
}

size_t kovshikov::getWeightEdge(std::pair< size_t, size_t > edge)
{
  return edge.second;
}

//добавление-удаление вершины
void kovshikov::Graph::addVertex(size_t key, std::string str)
{
  tree[key] = Node(str);
}

void kovshikov::Graph::deleteVertex(size_t key)
{ //обратить внимание
  try
  {
    haveThisVertex(key);
  }
  catch(const std::logic_error& e)
  {
    throw;
  }
  std::vector< size_t > allKeys;
  std::transform(tree.begin(), tree.end(), std::back_inserter(allKeys), getKey);
  std::vector< size_t > keys;
  std::copy_if(allKeys.begin(), allKeys.end(), std::back_inserter(keys), std::bind(noThis, key, std::placeholders::_1));
  size_t size = keys.size();
  for(size_t i = 0; i < size; i++)
  {
    if(tree[keys[i]].edges.find(key) != tree[keys[i]].edges.end())
    {
      tree[keys[i]].edges.erase(key);
    }
  }
  tree.erase(key);
}

//взаимодействие с ребрами
void kovshikov::Graph::createEdge(size_t keyWho, size_t keyWith, size_t weight)
{
  try
  {
    haveNot(keyWho, keyWith);
  }
  catch(const std::logic_error& e)
  {
    throw;
  }
  tree.at(keyWho).edges[keyWith] = weight;
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

void kovshikov::Graph::increaseWeight(size_t keyWho, size_t keyWith, size_t increase)
{
  try
  {
    haveNot(keyWho, keyWith);
  }
  catch(const std::logic_error& e)
  {
    throw;
  }
  if(getWeight(keyWho, keyWith) == 0)
  {
    createEdge(keyWho, keyWith, increase);
  }
  else
  {
    tree.at(keyWho).edges[keyWith] += increase;
  }
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

void kovshikov::Graph::change(size_t count, size_t who, size_t with)
{
  if(tree.at(who).edges.find(with) == tree.at(who).edges.end())
  {
    throw std::logic_error("There is no connection");
  }
  if(tree.at(who).edges.at(with) < count)
  {
    throw std::logic_error("links are less than the requested number");
  }
  tree.at(who).edges.at(with) -= count;
  if(tree.at(with).edges.find(who) == tree.at(with).edges.end())
  {
    createEdge(with, who, count);
  }
  else
  {
    tree.at(with).edges.at(who) += count;
  }
}

//особенность создания графа
void kovshikov::Graph::connect(size_t whoKey, size_t count, size_t weight)
{
  size_t size = getSize() - 1;
  size_t remainder = count % size;
  size_t numCircules = (remainder == 0)?(count / size):(count / size + 1);
  std::vector< size_t > connectKeys;
  getConnectKeys(connectKeys, whoKey);
  for(size_t i = 1; i <= numCircules; i++)
  {
    //STL с помощью адресной арифметики!!!!!
    if(i == numCircules)
    {
      for(size_t j = 1; j <= remainder; j++)
      {
        increaseWeight(whoKey, connectKeys[j], weight);
      }
    }
    else
    {
      for(size_t k = 0; k < size; k++)
      {
        increaseWeight(whoKey, connectKeys[k], weight);
      }
    }
  }
}

//функции для системы команд
size_t kovshikov::Graph::getVertexWeight(size_t key)
{ // в других может быть такая же ошибка, надо проверить
  //считал с учетом веса
  try
  {
    haveThisVertex(key);
  }
  catch(const std::logic_error& e)
  {
    throw;
  }
  std::vector< size_t > sum;
  std::transform(tree.at(key).edges.begin(), tree.at(key).edges.end(), std::back_inserter(sum), getWeightEdge);
  return std::accumulate(sum.begin(), sum.end(), 0);
}

size_t kovshikov::Graph::getDegree(size_t key)
{
  //степень - количество ребер входящих и исходящих
  try
  {
    haveThisVertex(key);
  }
  catch(const std::logic_error& e)
  {
    throw;
  }
  size_t degree = 0;
  degree += tree.at(key).edges.size();
  std::vector< size_t > allKeys;
  std::transform(tree.begin(), tree.end(), std::back_inserter(allKeys), getKey);
  std::vector< size_t > keys;
  std::copy_if(allKeys.begin(), allKeys.end(), std::back_inserter(keys), std::bind(noThis, key, std::placeholders::_1));
  size_t size = keys.size();
  for(size_t i = 0; i < size; i++)
  {
    if(tree[keys[i]].edges.find(key) != tree[keys[i]].edges.end())
    {
      degree += 1;
    }
  }
  return degree;
}

size_t kovshikov::Graph::getOwn(size_t key)
{
  //эту функцию можно использовать в методе getVertexWeight
  try
  {
    haveThisVertex(key);
  }
  catch(const std::logic_error& e)
  {
    throw;
  }
  size_t own = 0;
  std::vector< size_t > allKeys;
  std::transform(tree.begin(), tree.end(), std::back_inserter(allKeys), getKey);
  std::vector< size_t > keys;
  std::copy_if(allKeys.begin(), allKeys.end(), std::back_inserter(keys), std::bind(noThis, key, std::placeholders::_1));
  size_t size = keys.size();
  for(size_t i = 0; i < size; i++)
  {
    if(tree[keys[i]].edges.find(key) != tree[keys[i]].edges.end())
    {
      own += tree[keys[i]].edges[key];
    }
  }
  return own;
}

size_t kovshikov::Graph::getEdges()
{
  std::vector< size_t > count;
  std::transform(tree.begin(), tree.end(), std::back_inserter(count), getCountEdge);
  return std::accumulate(count.begin(), count.end(), 0);
}

//вывод
void kovshikov::Graph::outKeys() //??
{
  std::vector< size_t > keysList;
  std::transform(tree.begin(), tree.end(), std::back_inserter(keysList), getKey);
  using output_it = std::ostream_iterator< size_t >;
  std::copy(keysList.cbegin(), keysList.cend(), output_it{std::cout, " "});
  std::cout << "\n";
}

void kovshikov::Graph::outGraph(std::ostream& out) const
{
  if(isEmpty())
  {
    out << "This graph is empty" << "\n";
  }
  else
  {
    std::vector< size_t > keysList;
    std::transform(tree.begin(), tree.end(), std::back_inserter(keysList), getKey);
    size_t size = tree.size();
    for(size_t i = 0; i < size; i++)
    {
      out << keysList[i] << " " << tree.at(keysList[i]).value << " "; //ключ и вершину
      if(tree.at(keysList[i]).edges.empty())
      {
        out << 0 << "\n";
      }
      else
      {
        std::vector< size_t > keysWith;
        std::transform(tree.at(keysList[i]).edges.begin(), tree.at(keysList[i]).edges.end(), std::back_inserter(keysWith), getWith);
        size_t count = tree.at(keysList[i]).edges.size();
        for(size_t j = 0; j < count; j++)
        {
          if(j == count - 1)
          {
            out << keysWith[j] << " : " << tree.at(keysList[i]).edges.at(keysWith[j]) << "\n";
          }
          else
          {
            out << keysWith[j] << " : " << tree.at(keysList[i]).edges.at(keysWith[j]) << "  ";
          }
        }
      }
    }
  }
}

//cтандартные проверки
bool kovshikov::Graph::isEmpty() const noexcept
{
  return tree.empty();
}


size_t kovshikov::Graph::getSize() const noexcept
{
  return tree.size();
}

bool kovshikov::Graph::comp(std::pair< size_t, Node > left, std::pair< size_t, Node > right, Graph& graph)
{
  return graph.getDegree(left.first) > graph.getDegree(right.first);
}
void kovshikov::Graph::getMax(std::ostream& out)
{
  using namespace std::placeholders;
  std::vector< std::pair< size_t, Node > > tempVector(tree.begin(), tree.end());
  std::sort(tempVector.begin(), tempVector.end(), std::bind(comp, _1, _2, *this));
  size_t max = tempVector.front().first;
  std::vector< size_t > keys;
  std::transform(tree.begin(), tree.end(), std::back_inserter(keys), getKey);
  std::vector< size_t > keysWithout;
  std::copy_if(keys.begin(), keys.end(), std::back_inserter(keysWithout), std::bind(noThis, max, _1));
  size_t size = keysWithout.size();
  for(size_t i = 0; i < size; i++)
  {
    if(getDegree(max) == getDegree(keysWithout[i]))
    {
      out << keysWithout[i] << " ";
    }
  }
  out << max << "\n";
}
