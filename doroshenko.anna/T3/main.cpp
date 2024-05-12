#include <iostream>
#include <map>
#include <fstream>
#include <iterator>
#include <functional>
#include <limits>
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  //int context = 0;
  //std::map< std::string, std::function < void(std::istream&, std::ostream&) > > cmds;
  //{
  //  using namespace std::placeholders;
  //  cmds["CMD1"] = std::bind(goth::cmd1, context, _1, _2);
  //  cmds["CMD2"] = std::bind(goth::cmd2, context, _1, _2);
  //  cmds["CMD3"] = std::bind(goth::cmd3, context, _1, _2);
  //  cmds["CMD4"] = std::bind(goth::cmd4, context, _1, _2);
  //}
  //std::string cmd;
  //while (std::cin >> cmd)
  //{
  //  try
  //  {
  //    cmds.at(cmd)(std::cin, std::cout);
  //  }
  //  catch (const std::overflow_error& e)
  //  {
  //    std::cerr << "<GOTH_ERROR: " << e.what() << ">\n";
  //  }
  //  catch (const std::out_of_range&)
  //  {
  //    std::cerr << "<INVALID COMMAND>\n";
  //    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  //  }
  //}

  using namespace doroshenko;
  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  using input_it_t = std::istream_iterator< Polygon >;
  std::ifstream input(argv[1]);
  std::vector< Polygon > polygons;

  while (!input.eof())
  {
    std::copy(input_it_t{ input }, input_it_t{}, std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    //interaction["AREA"] = std::bind(kovshikov::getArea, _1, _2, _3); //заменить первый параметр на allData
    //interaction["MAX"] = std::bind(kovshikov::getMax, _1, _2, _3);
    //interaction["MIN"] = std::bind(kovshikov::getMin, _1, _2, _3);
    //interaction["COUNT"] = std::bind(kovshikov::count, _1, _2, _3);
    //interaction["RIGHTSHAPES"] = std::bind(kovshikov::countRightshapes, _1, _3);
    //interaction["INFRAME"] = std::bind(kovshikov::checkInframe, _1, _2, _3);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(polygons, std::cin, std::cout);
    }
    catch(const std::out_of_range& error)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
      //std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
