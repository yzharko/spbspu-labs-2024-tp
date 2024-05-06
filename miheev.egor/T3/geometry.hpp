#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <ios>

namespace miheev
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& rhs);
  std::ostream& operator<<(std::ostream& out, const Point& rhs);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& rhs);
  std::ostream& operator<<(std::ostream& out, const Polygon& rhs);

  struct GaussLacing
  {
  public:
    GaussLacing();
    double operator()(const Point&);

  private:
    int changeSign();
    int sign_; // TODO: rename Хранит, надо ли сейчас вычитать или прибавлять
    const Point* prevPoint_;
  };
  double getArea(const Polygon&);
}

#endif