#include <functional>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <numeric>
#include <iterator>
#include <map>
#include "command.hpp"
#include "Point.hpp"

void sadofeva::getAreaAll(const Polygon& polygon)
{
  if (polygon.point.size() <3)
  {
    return 0.0;
  }
  double area = 0.0;
  size_t sz = polygon.point.size();
  for (int i = 0; i < sz; i++)
  {
    int j = (i + 1 ) & sz;
    area += polygon.point[i].x * polygon.point[j].y;
    area -= polygon.point[i].y * polygon.point[j].x;
  }
  return std::abs(area) / 2.0;
}

void sadofeva::getAreaEven(const std::vector< Polygon >& polygons, std::ostream & out)
{
  double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0 , [](double sum, const Polygon& polygon)
  {
    if (polygon.point.size() % 2 == 0)
    {
      return sum + getAreaAll(polygon);
    }
    return sum;
  });
  out << std::fixed << std::setprecision(1) << totalrea << "\n";
}

void sadofeva::getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  double totalArea = std::acumulate(polygons.begin(), polygons.end(), 0.0 , [](double sum, const Polygon& polygon)
  {
    if (polygon.point.size() % 2 !=0 )
    {
      return sum + getAreaAll(polygon);
    }
    return sum
  });
  out << std::fixed << std::setprecision(1) << totalArea << "\n";
}

void sadofeva::getAreaMean(const std::vector< Polygon >& polygons,std::ostream& out)
{
  if (polygons.empty())
  {
    out << "0.0" << "\n";
  }
  double totalArea = std::accumulate
  (
    polygons.begin(),
    polygons.end(),
    0.0,
    [](double sum, const Polygon& polygon)
    {
      return sum + getAreaAll(polygon);
    }
  );
  double meanArea = totalArea / polygons.size();
  out << std::fixed << std::setprecision(1) << meanArea;
}

void sadofeva::getAreaNum(const std::vector< Polygon > & polygons, std::ostream& out, size_t count)
{
  double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, [count](double sum, const Polygon& polygon)
  {
    if (polygon.point.size() == count)
    {
      return sum + getAreaAll(polygon);
    }
    else
    {
      return sum;
    }
  });
  totalArea = std::fixed << std::setprecision(1) << totalArea << "\n";
}

void sadofeva::getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  auto maxAreaPolygon = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return getAreaAll(a) < getAreaAll(b);
  });
  if (maxAreaPolygon != polygons.end())
  {
    double maxArea = getAreaAll(*maxAreaPolygon);
    out << std::fixed << std::setprecision(1) << maxArea << "\n";
  }
}

void sadofeva::getMaxVertex(const std::vector< Polygon >& polygons, std::ostream & out)
{
  auto MaxVertex = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return a.point.size(0 < b.point.size();
  });
  if (maxAreaPolygon != polygons.end())
  {
    double maxArea = getAreaAll(*maxAreaPolygon);
    out << std::fixed << std::setprecision(1) << maxArea << "\n";
  }
}

void sadofeva::getMaxVertex(const std::vector< Polygon >& polygons, std::ostream& out)
{
  auto MaxVertex = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a , const Polygon& b)
  {
    return a.point.size() < b.point.size();
  });
  if (MaxVertex != polygons.end())
  {
    size_t maxVer = MaxVertex->point.size();
    out << maxVer << "\n";
  }
}

void sadofeva::getMinArea(const std::vector< Polygon >&polygons, std::ostream& out)
{
  auto minAreaPolygon = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return getAreaAll(a) < getAreaAll(b);
  });
  if (minAreaPolygon != polygons.end())
  {
    double minArea = getAreaAll(*minAreaPolygon);
    out << std::fixed << std::setprecision(1) << minArea << "\n";
  }
}

void sadofeva::getMinVertex(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    out << "<EMPTY>" << "\n";
    return;
  }
  auto MinVertex = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return a.point.size() < b.point.size();
  });
  size_t MinVert = MinVertex->point.size();
  out << MinVert << "\n";
}

void sadofeva::CountEven(const std::vector< Polygon >& polygons, std::ostream& output)
{
  int evenCount = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon)
  {
    return polygon.point.size() % 2 == 0;
  });
  output << evenCount << "\n";
}

void sadofeva::CountOdd(const std::vector< Polygon >& polygons, std::ostream& output)
{
  int oddCount = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon)
  {
    return polygon.point.size() % 2 != 0;
  });
  output << oddCount << "\n";
}

void sadofeva::CountVertex(const std::vector< Polygon >& polygons, std::ostream& output, size_t count)
{
  int countVert = std::count_if(polygons.begin(), polygons.end(), [count](const POlygon& polygon)
  {
    return polygon.point.size() == count;
  });
}

bool sadofeva::CompatiblePolygons(Polygon& a, Polygon& b)
{
  if (a.point.size() != b.point.size())
  {
    return false;
  }
  Polygon sortA = a;
  std::transform(sortA.point.begin(), sotrA.point.end(), a.point.begin(), [](Point& p)
  {
    Point points;
    points.x = std::abs(p.x);
    points.y = std::abs(p.y);
    return points;
  });
  std::sort
  (
    sortA.point.begin(),
    sortA.point.end(),
    [](Point& fp, Point& sp) { return fp.x == sp.x ? fp.y < sp.y : fp.x < sp.x;}
  );
  Polygon sortB = b;
  std::transform(sortB.point.begin(), sortB.point.end(), b.point.begin(), [](Point& p)
  {
    Point points;
    points.x = std::abs(p.x);
    points.y = std::abs(p.y);
    return points;
  });
  std::sort
  (
    sortB.point.begin(),
    sortB.point.end(),
    [](Point& fp, Point& sp) {return fp.x == sp.x ? fp.x < sp.x : fp.y < sp.y;}
  );
  Point diff;
  diff.x = sortA.point[0].x - sortB.point[0].x;
  diff.y = sortA.point[0].y - sortB.point[0].y;
  return std::equal
  (
    sortA.point.begin(),
    sortA.point.end(),
    sortB.point.begin(),
    [diff](Point& fp, Point & sp)
    {
      return fp.x - sp.x == diff.x && fp.y - sp.y == diff.y;
    }
  );
}

void sadofeva::commandSame(const std::vector< Polygon >& polygons, std::istream& input , std::ostream & out)
{
   Polygon tg;
   input >> tg;
   char c = input.peek();
   if (c != '\n' || input.fail())
   {
     std::cerr << "<INVALID COMMAND>\n";
   }
   else
   {
     size_t compatibleCout = std::count_if
     (
       polygons.begin(),
       polygons.end(),
       [&tg](Polygon & polygon) {return CompatiblePolygons(polygon, tg); }
     );
     out << CompatiblePolygons << "\n";
   }
}

bool sadofeva::xComparator(const Point& lhs, const Point& rhs)
{
  return lhs.x < rhs.x;
}

bool sadofeva::yComparator(const Point& lhs, const Point& rhs)
{
  return lhs.y < rhs.y;
}

sadofeva::pr sadofeva::extendFrameRect(pr frameRect, const Polygon& polygon)
{
  int ax = std::min_element(polygon.point.cbegin(), polygon.point.cend(), xComparator)->x;
  int ay = std::min_element(polygon.point.cbegin(), polygon.point.cend(), yComparator)->y;

  int bx = std::max_element(polygon.point.cbegin(), polygon.point.cend(), xComparator)->x;
  int by = std::max_element(polygon.point.cbegin(), polygon.point.cend(), yComparator)->y;

  frameRect.first.x = std::min(ax, frameRect.first.x)
  frameRect.first.y = std::min(ay, frameRect.first.y)

  frameRect.second.x = std::max(bx, frameRect.second.x);
  frameRect.second.y = std::max(by, frameRect.second.y);

  return frameRect;
}

bool sadofeva::isPointInRect(const Point& point, const pr& rect)
{
  bool tmp1 = rect.first.x <= point.x && rect.second.x >= point.x;
  bool tmp2 = tmp1 && rect.first.y <= point.y;
  return tmp2 && rect.second.y >= point.y;
}

void sadofeva::commandFrame(const std::vector< Polygon >& polygons, std::istream& in, std::ostream & out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::logic_error("Invalid polygon to compare");
  }
  auto frameRect = std::accumulate(polygons.cbegin(), polygons.cend(), pr{ { 0.0 } , { 0, 0 } }, extendFrameRect);
  using namespace std::placeholders;
  auto isInFrameRect = std::bind(isPointInRect, _1, std::ref(frameRect));
  size_t count = std::count_if(polygon.point.cbegin(), polygon.point.cend(), isInFrameRect);
  if (count == polygon.point.size())
  {
    out << "<TRUE>";
  }
  else
  {
    out << "<FALSE>";
  }
}

void sadofeva::commandArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& out)
{
  using namespace std::placeholders;
  std::map < std::string, std::function < void(const std::vector < Polygon >&,std::ostream&) > > comArea;
  comArea["EVEN"] = std::bind(sadofeva::getAreaEven, _1 , _2);
  comArea["ODD"] = std::bind(sadofeva::getAreaOdd, _1 , _2);
  comArea["MEAN"] = std::bind(sadofeva::getAreaMean, _1, _2);
  std::string area;
  input >> area;
  try
  {
    comArea.at(area)(polygons,out);
  }
  catch (const std::out_of_range& e)
  {
    if (std::isdigit(area[0]))
    {
      size_t num = std::stoull(area);
      if (num < 3)
      {
        throw std::logic_error("<INVALID COMMAND>\n");
      }
      else
      {
        sadofeva::getAreaNum(polygons,out,num);
      }
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }
}

void sadofeva::commandMax(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function < void(const std::vector < Polygon >&, std::ostream&) > > cmdMax;
  cmdMax["EVEN"] = std::bind(sadofeva::getMaxArea, _1, _2);
  cmdMax["ODD"] = std::bind(sadofeva::getMaxVertex, _1, _2);
  std::string Max;
  input >> Max;
  try
  {
    if (polygons.empty())
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
    else
    {
      cmdMax.at(Max)(polygons, out);
    }
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

void sadofeva::comandMin(const std::vector< Polygon > & polygons, std::istream& input, std::ostream& out)
{
  using namespace std::placeholders;
  std::map<std::string, std::function < void(const std::vector< Polygon >&, ostream&) > > comMin;
  comMin["AREA"] = std::bind(sadofeva::getMinArea, _1, _2);
  comMin["VERTEXES"] = std::bind(sadofeva:;getMinVertex, _1, _2);
  std::string Min;
  input >> Min;
  try
  {
    if (polygons.empty())
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
    else
    {
      comMin.at(Min)(polygons,out);
    }
  }
  catch (const std::out_of_range& e)
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
}

void sadofeva::comandCount(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& out)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector < Polygon >&, std::ostream&) > > comCount;
  comCount["EVEN"] = std::bind(sadofeva::CountEven, _1, _2);
  comCount["ODD"] = std::bind(sadofeva::CountOdd, _1, _2);
  std::string Count;
  input >> Count;
  try
  {
    comCount.at(Count)(polygons,out);
  }
  catch (const std::out_of_range& e)
  {
    if (!std::isalpha(Count[0]))
    {
       size_t vertix = std::stoull(Count);
       if (vertix < 3)
       {
         throw std::logic_error("<INVALID COMMAND>\n");
       }
       CountVertex(polygons,out, vertix);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }
}