#include "polygon.hpp"
#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <iterator>
#include <limits>

using namespace hohlova;
int main(int argc, char* argv[])
{
    std::ifstream in(argv[1]);
    if (argc != 2)
    {
        std::cerr << "wrong input\n";
        return 1;
    }
    if (!in.is_open())
    {
      std::cerr << "Failed to open file: " << argv[1] << std::endl;
      return 1;
    }
    std::vector< Polygon > polygons;
    while (!in.eof())
    {
        std::copy
        (
            std::istream_iterator<Polygon>(in),
            std::istream_iterator<Polygon>(),
            std::back_inserter(polygons)
        );
        if (in.eof()) {
            break;
        }
        if (in.fail() && !in.eof()) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    using CommandFunction = std::function<void(const std::vector<Polygon>&, std::istream&, std::ostream&)>;

    std::map<std::string, CommandFunction> command;

    using namespace std::placeholders;
    command["AREA"] = std::bind(AREACommandMenu, _1, _2, _3);
    command["MAX"] = std::bind(MAXCommandMenu, _1, _2, _3);
    command["MIN"] = std::bind(MINCommandMenu, _1, _2, _3);
    command["COUNT"] = std::bind(COUNTCommandMenu, _1, _2, _3);
    command["PERMS"] = std::bind(PERMSCommandMenu, _1, _2, _3);
    command["MAXSEQ"] = std::bind(MAXSEQCommandMenu, _1, _2, _3);
    command["RIGHTSHAPES"] = std::bind(RIGHTSHAPESCommandMenu, _1, _3);

    std::string incommand;
    while (std::cin >> incommand)
    {
        try
        {
            command.at(incommand)(polygons, std::cin, std::cout);
        }
        catch (const std::out_of_range& e)
        {
            Error();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }
    return 0;
}
