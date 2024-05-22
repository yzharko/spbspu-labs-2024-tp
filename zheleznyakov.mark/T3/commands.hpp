#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ios>
#include "geometry.hpp"
#include "iofmtguard.hpp"
namespace zheleznyakov
{
  namespace commands
  {
    std::ostream & area(const std::vector< Polygon > &, std::istream &, std::ostream &);
    std::ostream & max(const std::vector< Polygon > &, std::istream &, std::ostream &);
    std::ostream & min(const std::vector< Polygon > &, std::istream &, std::ostream &);
    std::ostream & count(const std::vector< Polygon > &, std::istream &, std::ostream &);
    std::ostream & maxseq(const std::vector< Polygon > &, std::istream &, std::ostream &);
    std::ostream & same(const std::vector< Polygon > &, std::istream &, std::ostream &);
  }

  double areaAccumulator(const Polygon & poly);
  double oddAreaAccumulator(const Polygon & poly);
  double evenAreaAccumulator(const Polygon & poly);
  double vertexAreaAccumulator(const Polygon & poly, size_t vertexes);

  double processAreaEven(const std::vector< Polygon > & polygons);
  double processAreaOdd(const std::vector< Polygon > & polygons);
  double processAreaMean(const std::vector< Polygon > & polygons);
  double processAreaVertexes(const std::vector< Polygon > & polygons, size_t vertexes);

  double processMaxArea(const std::vector< Polygon > & polygons);
  size_t processMaxVertex(const std::vector< Polygon > & polygons);

  double processMinArea(const std::vector< Polygon > & polygons);
  size_t processMinVertex(const std::vector< Polygon > & polygons);

  size_t processCountEven(const std::vector< Polygon > & polygons);
  size_t processCountOdd(const std::vector< Polygon > & polygons);
  size_t processCountVertex(const std::vector< Polygon > & polygons, const size_t vertexes);

  bool polygonIsVertexesOdd(const Polygon & polygons);
  bool polygonIsVertexesEven(const Polygon & polygons);
  bool polygonIsVertexesEquals(const Polygon & polygons, const size_t vertexes);

  size_t processMaxseq(const std::vector< Polygon > & polygons, const Polygon & target);
  size_t maxseqTransformHelper(const Polygon& polygon, const Polygon& target);

  size_t processSame(const std::vector<Polygon> & polygons, const Polygon & target);
  bool sameCountIfHelper(const Polygon & current, const Polygon & target);
  Point diffVector(const Point & p1, const Point & p2);
  bool hasLayeredPoints(const Polygon & p1, const Point & p2, const Point & movement);
  bool arePointsLayering(const Point & p1, const Point & p2, const Point & movement);

  std::ostream & outInvalidCommand(std::ostream &);
}
#endif
