#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ios>
#include "geometry.hpp"
namespace zheleznyakov
{
  namespace commands
  {
    std::ostream & area(const std::vector< Polygon > &, std::istream &, std::ostream &);
  }

  double areaAccumulator(double currentSum, const Polygon & poly);
  double oddAreaAccumulator(double currentSum, const Polygon & poly);
  double evenAreaAccumulator(double currentSum, const Polygon & poly);
  double vertexAreaAccumulator(double currentSum, const Polygon & poly, size_t vertexes);

  double processAreaEven(const std::vector< Polygon > & polys);
  double processAreaOdd(const std::vector< Polygon > & polys);
  double processAreaMean(const std::vector< Polygon > & polys);
  double processAreaVertexes(const std::vector< Polygon > & polys, size_t vertexes);
}
#endif
