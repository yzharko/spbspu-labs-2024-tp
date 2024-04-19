#include "Polygon.hpp"

std::istream& zasulsky::operator>>(std::istream& in, Point& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  zasulsky::Point input{ 0, 0 };
  using del = DelimiterIO;
  in >> del{ '(' } >> input.x >> del{ ';' } >> input.y >> del{ ')' };
  if (in) {
    rhs = input;
  }
  return in;
}

std::ostream& zasulsky::operator<<(std::ostream& out, const zasulsky::Point& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  return out << '(' << data.x << ';' << data.y << ')';
}

bool zasulsky::checkUniqueness(zasulsky::Polygon pol)
{
  bool isid = true;
  zasulsky::Polygon oth;
  for (size_t j = 0; j < pol.points.size(); j++)
  {
    oth.points.push_back(pol.points[j]);
  }
  for (size_t k = 0; k < oth.points.size(); k++)
  {
    int equal = 0;
    for (size_t i = 0; i < pol.points.size(); i++)
    {
      if (oth.points[k] == pol.points[i])
      {
        equal += 1;
      }
    }
    if (equal >= 2)
    {
      isid = false;
    }
  }
  return isid;
}

bool zasulsky::checkSize(zasulsky::Polygon pol)
{
  return pol.points.size() >= 3 ? true : false;
}

bool zasulsky::operator==(const Point& lhs, const Point& rhs)
{
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

std::istream& zasulsky::operator>>(std::istream& in, Polygon& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  Polygon input;
  size_t points = 0;
  in >> points;
  if (points < 3) {
    in.setstate(std::ios::failbit);
  }
  else
  {
    input.points.reserve(points);
    std::copy_n(std::istream_iterator< Point >(in),
      points,
      std::back_inserter(input.points));
  }
  if (in) {
    rhs.points.swap(input.points);
  }
  return in;
}

std::ostream& zasulsky::operator<<(std::ostream& out, const Polygon& rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  size_t points = rhs.points.size();
  out << points;
  std::copy_n(rhs.points.begin(),
    points - 1,
    std::ostream_iterator< Point >(out << ' ', " ")
  );
  return out << rhs.points.back();
}

bool zasulsky::operator==(const Polygon& lhs, const Polygon& rhs)
{
  auto firstLhs = lhs.points.begin();
  auto lastLhs = lhs.points.end();
  auto firstRhs = rhs.points.begin();
  auto lastRhs = rhs.points.end();
  bool result = std::equal(firstLhs, lastLhs, firstRhs, lastRhs);
  return result;
}

size_t zasulsky::getSize(const Polygon& polygon)
{
  return polygon.points.size();
}

void zasulsky::skipUntilNewLine(std::istream& in)
{
  auto maxstream = std::numeric_limits< std::streamsize >::max();
  in.ignore(maxstream, '\n');
}
bool zasulsky::lessX(Point lhs, Point rhs)
{
  return lhs.x < rhs.x;
}

bool zasulsky::lessY(Point lhs, Point rhs)
{
  return lhs.y < rhs.y;
}

std::pair<zasulsky::Point, zasulsky::Point> zasulsky::getFrame(const Polygon& pol)
{

  auto begin = pol.points.begin();
  auto end = pol.points.end();

  int minX = std::min_element(begin, end, lessX)->x;
  int maxX = std::max_element(begin, end, lessX)->x;
  int minY = std::min_element(begin, end, lessY)->y;
  int maxY = std::max_element(begin, end, lessY)->y;

  return { {minX, minY}, {maxX, maxY} };
}

zasulsky::frame correctFrame(zasulsky::frame lhs, zasulsky::frame rhs)
{
  int minX = lessX(lhs.first, rhs.first) ? lhs.first.x : rhs.first.x;
  int maxX = lessX(lhs.second, rhs.second) ? rhs.second.x : lhs.second.x;
  int minY = lessY(lhs.first, rhs.first) ? lhs.first.y : rhs.first.y;
  int maxY = lessY(lhs.second, rhs.second) ? rhs.second.y : lhs.second.y;

  return { {minX, minY}, {maxX, maxY} };
}

double zasulsky::sumPmArea(double accumulatedArea, const Point& startPoint)
{
  auto nextPoint = std::next(&startPoint);
  auto currentTriangleArea = ((startPoint.x * nextPoint->y) - (nextPoint->x * startPoint.y));
  auto newAccumulatedArea = accumulatedArea + currentTriangleArea;
  return newAccumulatedArea;
}

double zasulsky::countArea(const Polygon& pol)
{
  double area = 0.0;

  if (pol.points.size() >= 3)
  {
    auto last = std::prev(pol.points.end());

    area = std::accumulate(pol.points.begin(), last, 0.0, sumPmArea);
    auto lhs = last->x * pol.points.front().y;
    auto rhs = pol.points.front().x * last->y;
    auto PmArea = lhs - rhs;
    area += PmArea;
    area = std::abs(area) / 2.0;
  }
  return area;
}

zasulsky::frame accumulateFrames(const zasulsky::frame& frame, const zasulsky::Polygon& poly)
{
  return correctFrame(frame, getFrame(poly));
}

zasulsky::frame getOverallFrame(const std::vector<zasulsky::Polygon>& polygons)
{
  if (polygons.empty())
  {
    return { {0, 0}, {0, 0} };
  }
  zasulsky::frame overallFrame = getFrame(polygons.front());
  return std::accumulate(std::next(polygons.begin()), polygons.end(), overallFrame, accumulateFrames);
}

bool zasulsky::isRightAngle(int v1x, int v2x, int v1y, int v2y)
{
  auto numerator = ((v1x * v2x) + (v1y * v2y));
  auto denominator = ((v1x ^ 2) + (v1y ^ 2)) ^ (1 / 2) * ((v2x ^ 2) + (v2y ^ 2)) ^ (1 / 2);
  auto res = numerator / denominator;
  if (res == 0)
  {
    return true;
  }
  return false;
}



bool zasulsky::checkForRect(const Polygon& pol)
{
  auto np = pol.points;
  if (np.size() == 4)
  {
    auto firstT = np.back();
    np.pop_back();
    auto secondT = np.back();
    np.pop_back();
    auto thirdT = np.back();
    np.pop_back();
    auto fourthT = np.back();

    auto firstVecX = (firstT.x - secondT.x);
    auto secondVecX = (thirdT.x - secondT.x);
    auto firstVecY = (firstT.y - secondT.y);
    auto secondVecY = (thirdT.y - secondT.y);
    bool equalitySides = (secondT.x - firstT.x == thirdT.x - fourthT.x && secondT.y - thirdT.y == firstT.y - fourthT.y);
    bool rightAngle = (zasulsky::isRightAngle(firstVecX, secondVecX, firstVecY, secondVecY));
    return equalitySides && rightAngle ? 1 : 0;
  }
  return 0;
}

bool zasulsky::IsEqual(Polygon lhs, Polygon rhs)
{
  return lhs == rhs;
}
