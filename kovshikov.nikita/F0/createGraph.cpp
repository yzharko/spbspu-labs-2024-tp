#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>
#include <vector>
#include "createGraph.hpp"

void kovshikov::createGraph(std::map< std::string, Graph >& graphsList, std::istream& is)
{
  std::string parameter;
  is >> parameter;
  if(std::all_of(parameter.begin(), parameter.end(), isDigit) == true)
  {
    unsigned long long count = std::stoll(parameter);  //create< count, graphname >
    Graph graph;
    for(size_t i = 1; i <= count; i++)
    {
      graph.addVertex(i, "vertex");
    }
    for(size_t i = 1; i <= count; i++)
    {
      for(size_t j = 1; j <= count; j++)
      {
        if(i != j)
        {
          graph.createEdge(i, j, 1);
        }
      }
    }
    std::string graphname;
    is >> graphname;
    graphsList[graphname] = graph;
  }
  else
  {
    graphsList[parameter]; //create< graphname >
  }
}

void kovshikov::createLonely(std::map< std::string, Graph >& graphsList, std::istream& is)
{
  std::string graphname; //lonely< name > < count >
  is >> graphname;
  std::string parameter;
  is >> parameter;
  if(std::all_of(parameter.begin(), parameter.end(), isDigit) == true)
  {
    unsigned long long count = std::stoll(parameter);
    Graph graph;
    for(size_t i = 1; i <= count; i++)
    {
      graph.addVertex(i, "vertex");
    }
    graphsList[graphname] = graph;
  }
  else
  {
    throw std::logic_error("This is not number");
  }
}

void kovshikov::deleteGraph(std::map< std::string, Graph >& graphsList, std::istream& is)
{
  //delete< graphname >
  std::string key;
  is >> key;
  if(graphsList.find(key) == graphsList.end())
  {
    throw std::logic_error("This graph is not there");
  }
  else
  {
    graphsList.erase(key);
  }
}

void kovshikov::workWith(std::map< std::string, Graph >& graphsList, std::istream& is)
{
  std::string key;
  is >> key;
  if(graphsList.find(key) == graphsList.end())
  {
    throw std::logic_error("This graph is not there");
  }
  else
  {
    std::map< std::string, std::function< void(Graph& graph, std::istream& is) > > working;
    {
      using namespace std::placeholders;
      working["add"] = std::bind(add, _1, _2);
     // working["connect"] = std::bind()
    }

    std::string command;
    while(std::cin >> command)
    {
      try
      {
        working.at(command)(graphsList.at(key), std::cin);
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
}

void kovshikov::outputGraphs(const std::map< std::string, Graph >& graphsList, std::ostream& out)
{
  std::vector< std::string > graphnames;
  std::transform(graphsList.begin(), graphsList.end(), std::back_inserter(graphnames), getGraphname);
  using output_it = std::ostream_iterator< std::string >;
  std::copy(graphnames.cbegin(), graphnames.cend(), output_it{out, " "});
  out << "\n";
}
