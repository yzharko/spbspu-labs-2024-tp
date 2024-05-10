#include <iostream>
#include "geometry.hpp"

int main()
{
  zheleznyakov::Polygon p;
  std::cin >> p;
  std::cout << p;
  double area = zheleznyakov::calculatePolygonArea(p, 0, 0.0);
  std::cout << "Area of the polygon is: " << area << std::endl;
  return 0;
}
