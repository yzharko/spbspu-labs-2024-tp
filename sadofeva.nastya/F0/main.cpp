#include <iostream>
#include <functional>
#include <limits>
#include "command.hpp"

int main()
{
    using dictionary = std::map < std::string, int >;
    std::map< std::string, dictionary > dicts;
    std::map < std::string, std::function< void(std::map< std::string, dictionary>&, std::istream&, std::ostream&) > > command;
    {
         using namespace std::placeholders;
            command["help"] = std::bind(sadofeva::menuCommand,_2,_3);
            command["insert"] = std::bind(sadofeva::insert, _1, _2, std::ref(std::cout));
            command["remove"] = std::bind(sadofeva::remove, _1, _2, std::ref(std::cout));
            command["search"] = std::bind(sadofeva::search, _1, _2, std::ref(std::cout));
            command["printMaxCountWorld"] = std::bind(sadofeva::printMaxCountWorld, _1, _2, std::ref(std::cout));
           command["size"] = std::bind(sadofeva::save, _1, _2, std::ref(std::cout));
            command["union"] = std::bind(sadofeva::union1, _1, _2, std::ref(std::cout));
            command["save"] = std::bind(sadofeva::save, _1, _2, std::ref(std::cout));
            command["clear"] = std::bind(sadofeva::clear, _1, _2, std::ref(std::cout));
            command["print"] = std::bind(sadofeva::print, _1, _2, std::ref(std::cout));
            command["count"] = std::bind(sadofeva::countTo, _1, _2, std::ref(std::cout));
    }
    std::string cmd;
    while (std::cin >> cmd)
    {
        try
        {
            command.at(cmd)(dicts, std::cin, std::cout);
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
        }
    }
    return 0;
}
