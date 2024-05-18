#ifndef CREATEGRAPH_HPP
#define CREATEGRAPH_HP
#include "orientedGraph.hpp"

namespace kovshikov
{
  bool isDigit(char ch);
// для создания графа надо устроить проверку на уникальность ключа
  void createGraph(std::map< std::string, Graph >& graphsList, std::istream& is);
  void createLonely(std::map< std::string, Graph >& graphsList, std::istream& is);
  void deleteGraph(std::map< std::string, Graph >& graphsList, std::istream& is);
}

#endif
