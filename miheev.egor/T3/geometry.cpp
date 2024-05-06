#include "geometry.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include "delimiters.hpp"
#include "dataTypes.hpp"
#include "scopeguard.hpp"

std::istream& miheev::operator>>(std::istream& in, miheev::Point& rhs)
{
  using del = miheev::DelimiterIO;
  using i = miheev::IntIO;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> del{'('} >> i{rhs.x} >> del{';'} >> i{rhs.y} >> del{')'};
}

std::ostream& miheev::operator<<(std::ostream& out, const miheev::Point& rhs)
{
  iofmtguard fguard(out);
  return out << '(' << rhs.x << ';' << rhs.y << ')';
}

std::istream& miheev::operator>>(std::istream& in, miheev::Polygon& rhs)
{
  using size = miheev::SizeTIO;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t pointsAmount = 0;
  in >> size{pointsAmount};
  for (size_t i = 0; i < pointsAmount; i++)
  {
    Point temp{};
    in >> temp;
    rhs.points.push_back(temp);
  }
  return in;
}

std::ostream& miheev::operator<<(std::ostream& out, const miheev::Polygon& rhs)
{
  iofmtguard fguard(out);
  out << rhs.points.size() << ' ';
  for (size_t i = 0; i < rhs.points.size(); i++)
  {
    out << rhs.points[i];
    if (i != rhs.points.size() - 1)
    {
      out << ' ';
    }
  }
  out << '\n';
  return out;
}

miheev::GaussLacing::GaussLacing():
  sign_(false),
  prevPoint_(nullptr)
{}

int miheev::GaussLacing::changeSign()
{
  int sign = sign_;
  sign_ = -1;
  return sign;
}

double miheev::GaussLacing::operator()(const miheev::Point& point)
{
  if (!prevPoint_)
  {
    prevPoint_ = &point;
    return 0;
  }

  double dS = static_cast< double >(prevPoint_->x * point.y - prevPoint_->y * point.x) / 2;
  prevPoint_ = &point;
  return dS * changeSign();
}

double miheev::getArea(const miheev::Polygon& polygon)
{
  // подготавиваем вектор к особенностям шнуровки гаусса
  std::vector< double > areaDeltas(polygon.points.size());

  miheev::GaussLacing gaussLacing;
  std::transform(
    std::begin(polygon.points),
    std::end(polygon.points),
    std::back_inserter(areaDeltas),
    gaussLacing
  );

  double lastDelta = gaussLacing(polygon.points.at(0));
  areaDeltas.push_back(lastDelta);

  double area = std::accumulate(
    std::begin(areaDeltas),
    std::end(areaDeltas),
    0
  );

  return std::abs(area);
}