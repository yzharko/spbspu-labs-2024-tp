#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include "polygon.hpp"

using namespace lisitsyna;
struct Commands
{
  std::vector< Polygon > data;
  void getArea();
  void getMax();
  void getMin();
  void getCount();
  void getRects();
  void areaSum(int param);
  void areaMean();
  void areaSumN(size_t param);
  void minArea();
  void minVertexes();
  void maxArea();
  void maxVertexes();
  void countEven();
  void countOdd();
  void countN(size_t param);
  void rects();
  void messageInvalidCommand(std::ostream & os);
  void messageEmpty(std::ostream & os);
  void printInFrame();
  bool inFrame(const Polygon & figure, const std::vector< Polygon >&figures);
};
#endif
