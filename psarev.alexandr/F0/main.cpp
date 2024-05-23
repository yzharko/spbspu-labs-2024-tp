#include <limits>
#include <functional>
#include <iostream>
#include "userCmds.hpp"
#include "internalFuncs.hpp"

int main()
{
  using storage_t = std::map< std::string, std::vector< std::string > >;
  std::map< std::string, storage_t > depot;
  std::string defaultSt = "";
  std::map< std::string, std::function < void(std::istream&, std::ostream&, std::map< std::string, storage_t >&) > > userCmds;
  {
    using namespace std::placeholders;
    userCmds["help"] = std::bind(psarev::cmdHelp, _1, _2);
    userCmds["create"] = std::bind(psarev::cmdCreate, _1, _2, _3, "");
    userCmds["delete"] = psarev::cmdDelete;
    userCmds["list"] = std::bind(psarev::cmdList, _2, _3);
    userCmds["show"] = psarev::cmdShow;
    userCmds["rename"] = psarev::cmdRename;
    userCmds["choose"] = std::bind(psarev::cmdCreate, _1, _2, _3, defaultSt);
    userCmds["save"] = psarev::cmdSave;

    userCmds["print"] = std::bind(psarev::cmdPrint, _1, _2, _3, defaultSt);
    //userCmds["fono"] = psarev::cmdFono;
    userCmds["makeSent"] = std::bind(psarev::cmdMakeSent, _1, _2, _3, defaultSt);
  }

  std::string userCmd = "";
  while (std::cin >> userCmd)
  {
    try
    {
      userCmds.at(userCmd)(std::cin, std::cout, depot);
    }
    catch (const std::logic_error&)
    {
      psarev::outError(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
