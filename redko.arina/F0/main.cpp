#include <functional>
#include "userCommands.hpp"
#include "processingFunctions.hpp"

int main()
{
  redko::printMessage(std::cout, "--------- Huffman Coding ---------");
  redko::printMessage(std::cout, "type <help> to see list of commands");

  std::map< std::string, std::function< void(const std::string &)> > functions;
  functions["help"] = redko::help;
  functions["code"] = redko::code;
  functions["decode"] = redko::decode;
  functions["recode"] = redko::recode;
  functions["compare"] = redko::compare;

  std::string description = "";
  std::string command = "";
  while (std::getline(std::cin, description) && description != "quit")
  {
    command = redko::cutName(description);
    try
    {
      functions.at(command)(description);
    }
    catch (const std::out_of_range &)
    {
      redko::printMessage(std::cout, "<invalid command>");
    }
    catch (const std::logic_error & e)
    {
      redko::printMessage(std::cout, e.what());
    }
  }

  return 0;
}
