#include <iostream>
#include <limits>
#include <functional>
#include <map>
#include "commands.hpp"

void clearStream(std::istream& in)
{
  in.clear();
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

int main()
{
  using namespace proselkov;
  using langDictionary = std::map< std::string, std::string >;
  using majorDictionary = std::map< std::string, langDictionary >;
  majorDictionary engRusDict;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;

  using namespace std::placeholders;
  commands.insert(std::make_pair("help", std::bind(helpCmd, _2)));
  commands.insert(std::make_pair("create", std::bind(createCmd, std::ref(engRusDict), _1)));
  commands.insert(std::make_pair("remove", std::bind(removeCmd, std::ref(engRusDict), _1)));
  commands.insert(std::make_pair("print", std::bind(printCmd, std::ref(engRusDict), _1, _2)));
  commands.insert(std::make_pair("clear", std::bind(clearCmd, std::ref(engRusDict), _1)));
  commands.insert(std::make_pair("delete", std::bind(deleteCmd, std::ref(engRusDict), _1)));
  commands.insert(std::make_pair("insert", std::bind(insertCmd, std::ref(engRusDict), _1)));
  commands.insert(std::make_pair("search", std::bind(searchCmd, std::ref(engRusDict), _1, _2)));
  commands.insert(std::make_pair("size", std::bind(sizeCmd, std::ref(engRusDict), _1, _2)));
  commands.insert(std::make_pair("edit", std::bind(editCmd, std::ref(engRusDict), _1)));
  commands.insert(std::make_pair("combine", std::bind(combineCmd, std::ref(engRusDict), _1)));
  commands.insert(std::make_pair("save", std::bind(saveCmd, std::ref(engRusDict), _1)));

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "command doesn't exist\n";
      clearStream(std::cin);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      clearStream(std::cin);
    }
  }
}
