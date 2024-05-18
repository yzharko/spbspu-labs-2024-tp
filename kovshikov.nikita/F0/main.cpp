#include <functional>
#include <exception>
#include <iostream>
#include <limits>
#include "createGraph.hpp"
#include "orientedGraph.hpp"

int main()
{
  using namespace kovshikov;
  std::map< std::string, Graph> graphsList;
  std::map< std::string, std::function< void(std::map< std::string, Graph >&, std::istream&) > > interaction;

  {
    using namespace std::placeholders;
    interaction["create"] = std::bind(createGraph, _1, _2);
  }

  std::string command;

  while(std::cin >> command)
  {
    try
    {
      interaction.at(command)(graphsList, std::cin);
    }
    catch(const std::exception& error)
    {
      std::cout << "<ERROR>\n";
      std::cout << error.what() << "\n"; //при out_of_range не должно быть вывода сообщения
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }



/*  try
  {
    using namespace kovshikov;
    Graph graph;
    graph.addVertex(1, "никита");
    graph.addVertex(2, "сессия");
    std::cout << graph.isEmpty() << "\n";
    std::cout << graph.getSize() << "\n";
    graph.outKeys();
    graph.deleteVertex(1);
    graph.outKeys();
    graph.addVertex(3, "вова");
    graph.createEdge(2, 3, 100);
    graph.decreaseWeight(2, 3, 1);
    std::cout << graph.getWeight(2, 3) << "\n";
    graph.deleteEdge(2, 3);
    std::cout << graph.getWeight(2, 3) << "\n";
   // graph.deleteVertex(1);
    graph.createEdge(2, 3, 10);
    std::cout << graph.getWeight(2, 3) << "\n";
    std::cout << graph.getWeight(1, 3) << "\n";
    std::cout << graph.getWeight(2, 4) << "\n";
    std::cout << graph.getWeight(1, 4) << "\n";
  }
  catch(const std::exception& error)
  {
    std::cout << error.what() << "\n";
  }*/
}
