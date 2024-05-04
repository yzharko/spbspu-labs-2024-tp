#include <fstream>
#include <iostream>
#include <functional>
#include <map>
#include <limits>
#include <iterator>
#include "commands.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }

  std::vector< redko::Polygon > data;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< redko::Polygon >(input),
      std::istream_iterator< redko::Polygon >(),
      std::back_inserter(data)
    );
    if (input.fail() && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function < std::ostream & (std::istream &, std::ostream &, const std::vector< redko::Polygon > &) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(redko::countAreas, _1, _2, _3);
    commands["MAX"] = std::bind(redko::getMax, _1, _2, _3);
    commands["MIN"] = std::bind(redko::getMin, _1, _2, _3);
    commands["COUNT"] = std::bind(redko::count, _1, _2, _3);
    commands["INTERSECTIONS"] = std::bind(redko::countIntersections, _1, _2, _3);
    commands["RIGHTSHAPES"] = std::bind(redko::countRightShapes, _1, _2, _3);
  }

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, data);
    }
    catch (const std::out_of_range &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
