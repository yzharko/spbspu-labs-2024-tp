#include "processingFunctions.hpp"

std::string redko::cutName(std::string & str)
{
  std::string name = str.substr(0, str.find_first_of(" ", 0));
  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return name;
}

void redko::printMessage(std::ostream & out, const std::string & message)
{
  out << message << '\n';
}
