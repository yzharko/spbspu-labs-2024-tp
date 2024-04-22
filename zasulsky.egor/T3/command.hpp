#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Polygon.hpp"
#include <algorithm>
#include <functional>

namespace zasulsky
{
  using polygons = std::vector< Polygon >;
  using predicate = std::function< bool(const Polygon&) >;
  using comparator = std::function< bool(const Polygon&, const Polygon&) >;

  void printEvAr(const polygons& data, std::ostream& out);
  void printOdAr(const polygons& data, std::ostream& out);
  void printNSizeAr(const polygons& data, size_t number, std::ostream& out);
  void printMeanAr(const polygons& data, std::ostream& out);
  void printMaxAr(const polygons& data, std::ostream& out);
  void printMinAr(const polygons& data, std::ostream& out);
  void printMaxVert(const polygons& data, std::ostream& out);
  void printMaxMinAr(const polygons& data, comparator cmp, std::ostream& out);
  void printMinVert(const polygons& data, std::ostream& out);
  void printEvCount(const polygons& data, std::ostream& out);
  void printOdCount(const polygons& data, std::ostream& out);
  void printNSizeCount(const polygons& data, int number, std::ostream& out);
  void printRectsCount(const polygons& data, std::ostream& out);
  void printMaxSEQCount(const polygons& data, std::ostream& out, const Polygon fig);

  class MaxSEQCounter
  {
  public:
    Polygon fi;
    int count;
    int max;
    int operator()(int a, Polygon rhs)
    {
      if (fi == rhs)
      {
        count++;
        if (count > max)
        {
          max = count;
        }
      }
      else
      {
        count = 0;
      }
      return a = max;
    }
  };
}

#endif
