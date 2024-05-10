#include <vector>
#include <string>
#include <iomanip>
#include "iofmtguard.hpp"
#include "comand.hpp"

namespace taskaev
{
  void AreaComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
  {
    std::string nameComand;
    if (in >> nameComand)
    {
      if (nameComand == "EVEN")
      {
        // later;
      }
      else if (nameComand == "ODD")
      {
        // later
      }
      else if (nameComand == "MEAN")
      {
        // later
      }
      else
      {
        // later
      }
    }
    else
    {
      //later
    }
  }
}
