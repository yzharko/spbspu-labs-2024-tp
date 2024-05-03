#include "commands.hpp"
#include <map>
#include <cctype>
#include <functional>

void sobolevsky::area(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "EVEN")
  {
    
  }
  else if (arg == "ODD")
  {

  }
  else if (arg == "MEAN")
  {
    
  }
  else
  {

  }
}

void sobolevsky::max(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  out << "max\n";
}

void sobolevsky::min(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  out << "min\n";
}

void sobolevsky::count(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  out << "count\n";
}
