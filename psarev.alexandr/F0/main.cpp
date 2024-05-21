#include <limits>
#include <functional>
#include <iostream>
#include "userCmds.hpp"
#include "internalFuncs.hpp"

int main()
{
  using storage_t = std::map< std::string, std::vector< std::string > >;
  std::map< std::string, storage_t > depot;
  std::map< std::string, std::function < void (std::map< std::string, storage_t >&, std::istream&, std::ostream&) > > userCmds;
  {
    using namespace std::placeholders;
    userCmds["help"] = std::bind(psarev::cmdHelp, _2, _3);
    userCmds["create"] = psarev::cmdCreate;
    userCmds["delete"] = psarev::cmdDelete;
    userCmds["list"] = psarev::cmdList;
    userCmds["show"] = psarev::cmdShow;
    userCmds["rename"] = psarev::cmdRename;
    userCmds["choose"] = psarev::cmdChoose;
    userCmds["save"] = psarev::cmdSave;
  }

  std::string userCmd = "";
  while (std::cin >> userCmd)
  {
    try
    {
      userCmds.at(userCmd)(depot, std::cin, std::cout);
    }
    catch (const std::logic_error&)
    {
      psarev::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}