#include "command.hpp"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <functional>
#include "Iofmtguard.hpp"
#include "InpOutTypes.hpp"
#include "cmdTree.hpp"

namespace zasulsky
{
  using namespace std::placeholders;
  auto takeSizeF = std::bind(zasulsky::getSize, _1);
  auto takeSizeS = std::bind(zasulsky::getSize, _2);
  auto takeArF = std::bind(zasulsky::countArea, _1);
  auto takeArS = std::bind(zasulsky::countArea, _2);

  auto isOdd = std::bind(std::modulus< size_t >{}, takeSizeF, 2);
  auto isEven = std::bind(std::logical_not< bool >{}, std::bind(isOdd, _1));
  auto isSizeEqualToN = std::bind(std::equal_to< size_t >{}, takeSizeF, _2);
  auto countAreas = std::bind(std::plus< double >{}, _1, takeArS);
}

void printArea(const zasulsky::polygons& data, zasulsky::predicate pred, std::ostream& out)
{
  zasulsky::polygons areas;
  std::copy_if(data.cbegin(), data.cend(), std::back_inserter(areas), pred);

  zasulsky::iofmtguard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(areas.begin(), areas.end(), 0.0, zasulsky::countAreas);
}


void zasulsky::printEvAr(const polygons& data, std::ostream& out)
{
  printArea(data, isEven, out);
}

void zasulsky::printOdAr(const polygons& data, std::ostream& out)
{
  printArea(data, isOdd, out);
}

void zasulsky::printNSizeAr(const polygons& data, size_t number, std::ostream& out)
{
  if (number < 3)
  {
    throw std::invalid_argument("empty data");
  }
  else
  {
    using namespace std::placeholders;
    printArea(data, std::bind(isSizeEqualToN, _1, number), out);
  }
}

void zasulsky::printMeanAr(const polygons& data, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }
  else
  {
    zasulsky::iofmtguard streamGuard(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(data.begin(), data.end(), 0.0, countAreas) / data.size();
  }
}

void zasulsky::printMaxMinAr(const polygons& data, comparator cmp, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }
  zasulsky::iofmtguard streamGuard(out);
  out << std::fixed << std::setprecision(1);
  out << countArea(*(std::max_element(data.begin(), data.end(), cmp)));
}

void zasulsky::printMaxAr(const polygons& data, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }
  else
  {
    auto isGreater = std::bind(std::less< double >{}, takeArF, takeArS);

    printMaxMinAr(data, isGreater, out);
  }
}

void zasulsky::printMinAr(const polygons& data, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }
  else
  {
    auto isLess = std::bind(std::greater< double >{}, takeArF, takeArS);
    printMaxMinAr(data, isLess, out);
  }
}

void printSize(const zasulsky::polygons& data, zasulsky::comparator cmp, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }

  out << getSize(*(std::max_element(data.begin(), data.end(), cmp)));
}

void zasulsky::printMaxVert(const polygons& data, std::ostream& out)
{
  if (data.empty())
  {
    throw std::invalid_argument("empty data");
  }
  else
  {
    auto isGreater = std::bind(std::less< size_t >{}, takeSizeF, takeSizeS);
    printSize(data, isGreater, out);
  }
}

void zasulsky::printMinVert(const polygons& data, std::ostream& out)
{
  auto isLess = std::bind(std::greater< size_t >{}, takeSizeF, takeSizeS);

  printSize(data, isLess, out);
}

void printSizeCount(const zasulsky::polygons& data, zasulsky::predicate pred, std::ostream& out)
{
  out << std::count_if(data.begin(), data.end(), pred) << '\n';
}

void zasulsky::printEvCount(const polygons& data, std::ostream& out)
{
  printSizeCount(data, isEven, out);
}

void zasulsky::printOdCount(const polygons& data, std::ostream& out)
{
  printSizeCount(data, isOdd, out);
}

void zasulsky::printNSizeCount(const polygons& data, int number, std::ostream& out)
{
  if (number < 3)
  {
    throw std::invalid_argument("empty data");
  }
  else
  {
    using namespace std::placeholders;
    printSizeCount(data, std::bind(isSizeEqualToN, _1, number), out);
  }
}

void zasulsky::printRectsCount(const polygons& dat, std::ostream& out)
{
  out << count_if(dat.begin(), dat.end(), checkForRect);
}

void zasulsky::printMaxSEQCount(const polygons& data, std::ostream& out, const Polygon fig)
{
  MaxSEQCounter cr;
  cr.fi = fig;
  cr.max = 0;
  cr.count = 0;
  auto res = std::accumulate(data.begin(), data.end(), 0, cr);
  out << res;
}
