#include "io.hpp"
#include <string>
#include <stdexcept>

std::istream& operator>>(std::istream& in, Polygon& poly) {
  bool sentry = true;
  
  try {
        if (!sentry) {
            throw std::runtime_error("Sentry condition failed.");
        }

        std::string str;
        if (!(in >> str)) {
            throw std::runtime_error("Failed to read string from input.");
        }

std::istream& std::operator>>(std::istream& in, std::Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;
    std::string str;
    in >> str;
    if (!std::isPoint(str))
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    char ch;
    std::stringstream ss(str);
    ss >> ch >> point.x >> ch >> point.y >> ch;
    return in;
}
std::istream& std::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry)
     return in;
  poly.points.clear();
  std::size_t n;
  in >> n;
  if (in.fail() || n < 3)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  poly.points.resize(n);

  if (in.peek() != '\n') {
            throw std::runtime_error("Input not terminated correctly.");
        }

        return in;
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    in.setstate(std::ios::failbit);
    return in;
  }
}
for (auto& p : poly.points)
  {
    in >> p;
  }
  if (in.peek() != '\n')
     in.setstate(std::ios_base::failbit);
     return in;
}
std::ostream& std::operator<<(std::ostream& out, const std::Point& point)
{
  return (out << '(' << point.x << ';' << point.y << ')');
}
bool std::isPoint(std::string& str)
{
  std::regex pattern("\\(-?[0-9]+;-?[0-9]+\\)");
  return std::regex_match(str, pattern);
}
