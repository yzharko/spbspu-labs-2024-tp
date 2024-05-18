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
}
