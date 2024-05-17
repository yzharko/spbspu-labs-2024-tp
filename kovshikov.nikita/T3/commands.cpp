#include "commands.hpp"
#include <algorithm>
#include <cstring>
#include <functional>
#include <fstream>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <numeric>
#include "polygons.hpp"
void kovshikov::getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > area;
  {
    using namespace std::placeholders;
    area["EVEN"] = std::bind(kovshikov::getAreaEven, _1, _2);
    area["ODD"] = std::bind(kovshikov::getAreaOdd, _1, _2);
    area["MEAN"] = std::bind(kovshikov::getAreaMean, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    area.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    getCheck(command, getAreaVertex, allData, out);
  }
}

void kovshikov::getAreaEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > even;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(even), isEven);
  double area = std::accumulate(even.begin(), even.end(), 0, resultArea);
  out << area << "\n";
}

void kovshikov::getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > odd;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(odd), isOdd);
  double area = std::accumulate(odd.begin(), odd.end(), 0, resultArea);
  out << area << "\n";
}

void kovshikov::getAreaMean(const std::vector< Polygon >& allData, std::ostream& out)
{
  fileIsEmpty(allData);
  double area = std::accumulate(allData.begin(), allData.end(), 0, resultArea);
  double result = area / allData.size();
  out << result << "\n";
}

void kovshikov::getAreaVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out)
{
  double result = 0;
  if(allData.empty())
  {
    out << result << "\n";
  }
  else
  {
    using namespace std::placeholders;
    std::vector< Polygon >::const_iterator detected = std::find_if(allData.begin(), allData.end(), std::bind(isThisVertex, num, _1));
    int count = std::count_if(allData.begin(), allData.end(), std::bind(isThisVertex, num, _1));
    if(detected == allData.end())
    {
      out << result << "\n";
    }
    result = countArea(*detected) * count;
    out << result << "\n";
  }
}

void kovshikov::getMax(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > max;
  {
    using namespace std::placeholders;
    max["AREA"] = std::bind(kovshikov::getMaxArea, _1, _2);
    max["VERTEXES"] = std::bind(kovshikov::getMaxVertexes, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    fileIsEmpty(allData);
    max.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    throw;
  }
}

void kovshikov::getMaxArea(const std::vector< Polygon >& allData, std::ostream& out)
{
  double maxArea = 0;
  std::vector< double > allAreas;
  std::transform(allData.begin(), allData.end(), std::back_inserter(allAreas), countArea);
  std::sort(allAreas.begin(), allAreas.end());
  maxArea = *(allAreas.end() - 1);
  out << maxArea << "\n";
}

void kovshikov::getMaxVertexes(const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long maxVertexes = 0;
  std::vector< unsigned long long > allVertexes;
  std::transform(allData.begin(), allData.end(), std::back_inserter(allVertexes), getVertexes);
  std::sort(allVertexes.begin(), allVertexes.end());
  maxVertexes = *(allVertexes.end() - 1);
  out << maxVertexes << "\n";
}

void kovshikov::getMin(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > min;
  {
    using namespace std::placeholders;
    min["AREA"] = std::bind(kovshikov::getMinArea, _1, _2);
    min["VERTEXES"] = std::bind(kovshikov::getMinVertexes, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    min.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    throw;
  }
}

void kovshikov::getMinArea(const std::vector< Polygon >& allData, std::ostream& out)
{
  double minArea = 0;
  if(allData.empty())
  {
    out << minArea << "\n";
  }
  else
  {
    std::vector< double > allAreas;
    std::transform(allData.begin(), allData.end(), std::back_inserter(allAreas), countArea);
    std::sort(allAreas.begin(), allAreas.end());
    minArea = *(allAreas.begin());
    out << minArea << "\n";
  }
}

void kovshikov::getMinVertexes(const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long minVertexes = 0;
  if(allData.empty())
  {
    out << minVertexes << "\n";
  }
  else
  {
    std::vector< unsigned long long > allVertexes;
    std::transform(allData.begin(), allData.end(), std::back_inserter(allVertexes), getVertexes);
    std::sort(allVertexes.begin(), allVertexes.end());
    minVertexes = *(allVertexes.begin());
    out << minVertexes << "\n";
  }
}

void kovshikov::count(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > count;
  {
    using namespace std::placeholders;
    count["EVEN"] = std::bind(kovshikov::countEven, _1, _2);
    count["ODD"] = std::bind(kovshikov::countOdd, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    count.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    getCheck(command, countVertexes, allData, out);
  }
}

void kovshikov::countEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > even;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(even), isEven);
  unsigned long long count = even.size();
  out << count << "\n";
}

void kovshikov::countOdd(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > odd;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(odd), isOdd);
  unsigned long long count = odd.size();
  out << count << "\n";
}

void kovshikov::countVertexes(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long count = 0;
  std::vector< Polygon > withThisVertexes;
  using namespace std::placeholders;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(withThisVertexes), std::bind(isThisVertex, num, _1));
  count = withThisVertexes.size();
  out << count << "\n";
}

void kovshikov::countRightshapes(const std::vector< Polygon >& allData, std::ostream& out)
{
  out << std::count_if(allData.begin(), allData.end(), isPolygonRight) << "\n";
}

void kovshikov::checkInframe(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  Polygon polygon;
  is >> polygon;
  if(!is)
  {
    throw std::out_of_range("");
  }
  else
  {
    bool check = isInframe(allData, polygon);
    if(check == true)
    {
      out << "<TRUE>" << "\n";
    }
    else
    {
      out << "<FALSE>" << "\n";
    }
  }
}
