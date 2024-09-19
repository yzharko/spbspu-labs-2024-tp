#include "Polygon.hpp"
#include <sstream>

namespace kaseev
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && c != dest.exp)
    {
      in.setstate(std::ios::failbit);
      //std::cout << "DELIM EXP: " << dest.exp << " GOT : " << c << '\n';
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, Point &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    return in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' }
              >> dest.y >> DelimiterIO{ ')' };
  }
  std::istream &operator>>(std::istream &in, Polygon &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    dest.points.clear();
    size_t size = 0;
    in >> size;
    std::string str;
    std::getline(in, str , '\n');
    std::istringstream input(str);
    if (!input || size < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    std::vector < Point > temp{};
    std::copy(std::istream_iterator< Point >(input), std::istream_iterator< Point >(),
              std::back_inserter(temp));
    if (temp.size() == size && temp.size() >= 3)
    {
      dest.points = temp;
      //std::cout << temp.size() << " " << dest.points.size() << " DONE \n";
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  bool operator >(const Point& p1, const Point& p2)
  {
    if (p1.x > p2.x)
    {
      return true;
    }
    else if (p1.x < p2.x)
    {
      return false;
    }
    else
    {
      return (p1.y >= p2.y);
    }
  }
  bool Point::operator<(const Point& object) const
  {
    return (x < object.x and y < object.y);
  }
  bool Point::operator<=(const Point& object) const
  {
    return (x <= object.x and y <= object.y);
  }
  bool Point::operator>=(const Point& object) const
  {
    return (x >= object.x and y >= object.y);
  }
}
