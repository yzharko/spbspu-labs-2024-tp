#include "commands.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "polygon.hpp"
#include "ScopeGuard.hpp"

using namespace lisitsyna;

namespace
{
  bool xPointComparator(const Point& point1, const Point& point2)
  {
    return point1.x < point2.x;
  }

  bool yPointComparator(const Point& point1, const Point& point2)
  {
    return point1.y < point2.y;
  }
  bool xComparator(const Polygon& figure1, const Polygon& figure2)
  {
    bool result = false;

    int firstMax = std::max_element(figure1.points.begin(), figure1.points.end(), xPointComparator)->x;
    int secondMax = std::max_element(figure2.points.begin(), figure2.points.end(), xPointComparator)->x;

    int firstMin = std::min_element(figure1.points.begin(), figure1.points.end(), xPointComparator)->x;
    int secondMin = std::min_element(figure2.points.begin(), figure2.points.end(), xPointComparator)->x;

    if ((firstMax < secondMax) && (firstMin < secondMin))
    {
      result = true;
    }

    return result;
  }

  bool yComparator(const Polygon& figure1, const Polygon& figure2)
  {
    bool result = false;

    int firstMax = std::max_element(figure1.points.begin(), figure1.points.end(), yPointComparator)->y;
    int secondMax = std::max_element(figure2.points.begin(), figure2.points.end(), yPointComparator)->y;

    int firstMin = std::min_element(figure1.points.begin(), figure1.points.end(), yPointComparator)->y;
    int secondMin = std::min_element(figure2.points.begin(), figure2.points.end(), yPointComparator)->y;

    if ((firstMax < secondMax) && (firstMin < secondMin))
    {
      result = true;
    }

    return result;
  }
}

void Commands::getArea()
{
  std::string param = "";
  int res = 0;
  std::cin >> param;
  try
  {
    res = std::stoi(param);
  }
  catch (std::invalid_argument& e)
  {
    res = -1;
  }
  if (param == "ODD")
  {
    areaSum(1);
  }
  else if (param == "EVEN")
  {
    areaSum(0);
  }
  else if (param == "MEAN")
  {
    areaMean();
  }
  else if (res > 2)
  {
    areaSumN(res);
  }
  else
  {
    messageInvalidCommand(std::cout);
  }
}

void Commands::getMax()
{
  std::string param = "";
  std::cin >> param;
  if (param == "AREA")
  {
    maxArea();
  }
  else if (param == "VERTEXES")
  {
    maxVertexes();
  }
  else
  {
    messageInvalidCommand(std::cout);
  }
}

void Commands::getMin()
{
  std::string param = "";
  std::cin >> param;
  if (param == "AREA")
  {
    minArea();
  }
  else if (param == "VERTEXES")
  {
    minVertexes();
  }
  else
  {
    messageInvalidCommand(std::cout);
  }
}

void Commands::getCount()
{
  std::string param = "";
  int res = 0;
  std::cin >> param;
  try
  {
    res = std::stoi(param);
  }
  catch (std::invalid_argument& e)
  {
    res = -1;
  }
  if (param == "ODD")
  {
    countOdd();
  }
  else if (param == "EVEN")
  {
    countEven();
  }
  else if (res > 2)
  {
    countN(res);
  }
  else
  {
    messageInvalidCommand(std::cout);
  }
}

void Commands::getRects()
{
  rects();
}

void Commands::areaSum(int param)
{
  if (data.size() == 0)
  {
    std::cout << std::fixed << std::setprecision(1) << 0.0 << "\n";
    return;
  }
  std::vector< Polygon > tmp(data.size());
  if (param == 0)
  {
    std::copy_if(data.begin(), data.end(), tmp.begin(),
    [&](Polygon i) {return (i.points.size() % 2 == 0); });
    size_t amount = std::count_if(data.begin(), data.end(),
    [&](Polygon i) { return (i.points.size() % 2 == 0); });
    std::vector< double > tmpS(amount);
    std::vector< Polygon >::iterator fin = tmp.begin() + amount;
    std::transform(tmp.begin(), fin, tmpS.begin(), lisitsyna::getArea);
    std::cout << std::fixed << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
  }
  else
  {
    std::copy_if(data.begin(), data.end(), tmp.begin(),
    [&](Polygon i) {return (i.points.size() % 2 != 0); });
    size_t amount = std::count_if(data.begin(), data.end(),
    [&](Polygon i) { return (i.points.size() % 2 != 0); });
    std::vector< double > tmpS(amount);
    std::vector< Polygon >::iterator fin = tmp.begin() + amount;
    std::transform(tmp.begin(), fin, tmpS.begin(), lisitsyna::getArea);
    std::cout << std::fixed << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
  }
}

void Commands::areaMean()
{
  if (data.size() == 0)
  {
    messageInvalidCommand(std::cout);
    return;
  }
  std::vector< double > tmp(data.size());
  std::transform(data.begin(), data.end(), tmp.begin(),
  lisitsyna::getArea);
  std::cout << std::fixed << std::setprecision(1) << std::accumulate(tmp.begin(), tmp.end(), 0.0) / data.size() << "\n";
}

void Commands::areaSumN(size_t param)
{
  if (data.size() == 0)
  {
    std::cout << std::fixed << std::setprecision(1) << 0.0 << "\n";
    return;
  }
  std::vector< Polygon > tmp(data.size());
  std::copy_if(data.begin(), data.end(), tmp.begin(),
  [&](Polygon i) {return (i.points.size() == param); });
  size_t amount = std::count_if(data.begin(), data.end(),
  [&](Polygon i) { return (i.points.size() == param); });
  std::vector< double > tmpS(amount);
  std::vector< Polygon >::iterator fin = tmp.begin() + amount;
  std::transform(tmp.begin(), fin, tmpS.begin(), ::getArea);
  std::cout << std::fixed << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}

void Commands::minArea()
{
  if (data.size() == 0)
  {
    messageInvalidCommand(std::cout);
    return;
  }
  std::vector< Polygon > tmp(data.size());
  std::copy(data.begin(), data.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorArea);
  std::cout << std::setprecision(1) << lisitsyna::getArea(tmp[tmp.size() - 1]) << "\n";
}

void Commands::minVertexes()
{
  if (data.size() == 0)
  {
    messageInvalidCommand(std::cout);
    return;
  }
  std::vector< Polygon > tmp(data.size());
  std::copy(data.begin(), data.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorVertexes);
  std::cout << std::setprecision(1) << tmp[tmp.size() - 1].points.size() << "\n";
}

void Commands::maxArea()
{
  if (data.size() == 0)
  {
    messageInvalidCommand(std::cout);
    return;
  }
  std::vector< Polygon > tmp(data.size());
  std::copy(data.begin(), data.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorArea);
  std::cout << std::fixed << std::setprecision(1) << lisitsyna::getArea(tmp[0]) << "\n";
}

void Commands::maxVertexes()
{
  if (data.size() == 0)
  {
    messageInvalidCommand(std::cout);
    return;
  }
  std::vector< Polygon > tmp(data.size());
  std::copy(data.begin(), data.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorVertexes);
  std::cout << tmp[0].points.size() << "\n";
}

void Commands::countEven()
{
  std::cout << std::count_if(data.begin(), data.end(),
  [&](Polygon i) { return i.points.size() % 2 == 0; }) << "\n";
}

void Commands::countOdd()
{
  std::cout << std::count_if(data.begin(), data.end(),
  [&](Polygon i) { return i.points.size() % 2 != 0; }) << "\n";
}

void Commands::countN(size_t param)
{
  std::cout << std::count_if(data.begin(), data.end(),
  [&](Polygon i) { return i.points.size() == param; }) << "\n";
}

void Commands::rects()
{
  std::cout << std::count_if(data.begin(), data.end(), [&](Polygon i) { return isRect(i); }) << "\n";
}

void Commands::messageInvalidCommand(std::ostream& os)
{
  os << "<INVALID COMMAND>\n";
}

void Commands::messageEmpty(std::ostream& os)
{
  os << "<EMPTY>\n";
}

void Commands::printInFrame()
{
  Polygon parameter;

  std::cin >> parameter;

  if (std::cin && ((std::cin.peek() == '\n') || std::cin.eof()))
  {
    iofmtguard guardian(std::cout);
    std::cout << ((inFrame(parameter, data)) ? "<TRUE>" : "<FALSE>") << '\n';
  }
}

bool Commands::inFrame(const Polygon& figure, const std::vector< Polygon >& figures)
{
  Polygon rectMaxX = *std::max_element(figures.begin(), figures.end(), xComparator);
  Polygon rectMinX = *std::min_element(figures.begin(), figures.end(), xComparator);
  Polygon rectMaxY = *std::max_element(figures.begin(), figures.end(), yComparator);
  Polygon rectMinY = *std::min_element(figures.begin(), figures.end(), yComparator);

  std::pair< int, int > downLeftCorner
  {
    std::min_element(rectMinX.points.begin(), rectMinX.points.end(), xPointComparator)->x,
    std::min_element(rectMinY.points.begin(), rectMinY.points.end(), yPointComparator)->y
  };

  std::pair< int, int > upRightCorner
  {
    std::max_element(rectMaxX.points.begin(), rectMaxX.points.end(), xPointComparator)->x,
    std::max_element(rectMaxY.points.begin(), rectMaxY.points.end(), yPointComparator)->y
  };

  int maxX = std::max_element(figure.points.begin(), figure.points.end(), xPointComparator)->x;
  int minX = std::min_element(figure.points.begin(), figure.points.end(), xPointComparator)->x;
  int maxY = std::max_element(figure.points.begin(), figure.points.end(), yPointComparator)->y;
  int minY = std::min_element(figure.points.begin(), figure.points.end(), yPointComparator)->y;

  return (maxX <= upRightCorner.first) && (maxY <= upRightCorner.second)
  && (minX >= downLeftCorner.first) && (minY >= downLeftCorner.second);
}
