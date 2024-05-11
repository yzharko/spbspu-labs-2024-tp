#include <iostream>
#include <map>
#include "fstream"
#include <functional>
#include <limits>
#include "polygon.hpp"
namespace doroshenko
{
  void cmd1(std::vector< Polygon >&, std::istream&, std::ostream& out)
  {
    out << "CMD1 dispatched\n";
  }
  void cmd2(int&, std::istream&, std::ostream& out)
  {
    out << "CMD2 dispatched\n";
  }
  void cmd3(const int&, std::istream&, std::ostream& out)
  {
    out << "CMD3 dispatched\n";
  }
  void cmd4(const int&, std::istream&, std::ostream& out)
  {
    //...
    out << "hello goth programmer nation!!!\n";
    throw std::overflow_error("overflow cmd4");
  }
}
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


  return 0;
}
