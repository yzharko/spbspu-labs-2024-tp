#include <cstring>
#include <map>
#include <functional>
#include <fstream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "polygons.hpp"
#include "commands.hpp"

int main(int argc, char ** argv)
{
  if(argc != 2)
  {
    std::cerr << "NO FILE SPECIFIED" << "\n";
    return 1;
  }

  using namespace kovshikov;
  std::vector< Polygon > allData;
  std::fstream input(argv[1]);
  using input_it = std::istream_iterator< Polygon >;
  while(!input.eof())
  {
    std::copy(input_it{input}, input_it{}, std::back_inserter(allData));
    if(input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::istream&, std::ostream&) > > interaction;
  {
    using namespace std::placeholders;
    interaction["AREA"] = std::bind(kovshikov::getArea, _1, _2, _3); //заменить первый параметр на allData
    interaction["MAX"] = std::bind(kovshikov::getMax, _1, _2, _3);
    interaction["MIN"] = std::bind(kovshikov::getMin, _1, _2, _3);
    interaction["COUNT"] = std::bind(kovshikov::count, _1, _2, _3);
    interaction["RIGHTSHAPES"] = std::bind(kovshikov::countRightshapes, _1, _3);
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      interaction.at(command)(allData, std::cin, std::cout); //в зависимости от std::bind убрать allData
    }
    catch(const std::out_of_range& error)
    {
      std::cerr << "INVALID COMMAND" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
