#include "accessoryFunctions.hpp"

std::string ponomarev::cutType(std::string & line)
{
  std::string type = line.substr(0, line.find(" "));
  if (line.find(" ") == std::string::npos)
  {
    line = "";
  }
  else
  {
    line = line.substr(line.find(" ") + 1);
  }
  return type;
}

std::ostream & ponomarev::printInvalidCommandMessage(std::ostream & out)
{
  std::string message = "<INVALID COMMAND>";
  out << message << "\n";
  return out;
}
