#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>

#include "polygon.hpp"
#include "mainExtensions.hpp"

int main(int argc, char **argv)
{
  using namespace anikanov;

  if (argc < 2 || argc > 2) {
    return 1;
  }

  std::string filename = argv[1];
  std::vector< Polygon > polygons;

  try {
    polygons = readPolygons(filename);
  }
  catch (const std::exception &e) {
    std::cerr << "Error reading file: " << e.what() << "\n";
    return 2;
  }

  std::string cmd, subcmd;
  while (std::cin >> cmd) {
    if (cmd != "RECTS" && cmd != "RIGHTSHAPES") {
      std::cin >> subcmd;
    }
    if (cmd == "AREA") {
      std::vector< double > areas;
      if (subcmd == "ODD") {
        areas = getAreasIf(polygons, [](const Polygon &pol) {
          return pol.getSize() % 2 == 1;
        });
      } else if (subcmd == "EVEN") {
        areas = getAreasIf(polygons, [](const Polygon &pol) {
          return pol.getSize() % 2 == 0;
        });
      } else {
        size_t count = std::stoull(subcmd);
        areas = getAreasIf(polygons, [&count](const Polygon &pol) {
          return pol.getSize() == count;
        });
      }
      double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
      std::cout << std::fixed << std::setprecision(1) << sum << "\n";
    } else if (cmd == "MAX") {
      if (subcmd == "AREA") {
        std::vector< double > areas = getAreas(polygons);
        auto maxAreaPolygon = *std::max_element(areas.begin(), areas.end());
        std::cout << std::fixed << std::setprecision(1) << maxAreaPolygon << '\n';
      } else if (subcmd == "VERTEXES") {
        std::vector< size_t > count = getVertexes(polygons);
        auto maxVertexesPolygon = *std::max_element(count.begin(), count.end());
        std::cout << maxVertexesPolygon << '\n';
      }
    } else if (cmd == "MIN") {
      if (subcmd == "AREA") {
        std::vector< double > areas = getAreas(polygons);
        auto minAreaPolygon = *std::min_element(areas.begin(), areas.end());
        std::cout << std::fixed << std::setprecision(1) << minAreaPolygon << '\n';
      } else if (subcmd == "VERTEXES") {
        std::vector< size_t > count = getVertexes(polygons);
        auto minVertexesPolygon = *std::min_element(count.begin(), count.end());
        std::cout << minVertexesPolygon << '\n';
      }
    } else if (cmd == "COUNT") {
      size_t count;
      if (subcmd == "ODD") {
        count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
          return pol.getSize() % 2 == 1;
        });
      } else if (subcmd == "EVEN") {
        count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
          return pol.getSize() % 2 == 0;
        });
      } else {
        size_t specificNumber = std::stoull(subcmd);
        count = std::count_if(polygons.begin(), polygons.end(), [&specificNumber](const Polygon &pol) {
          return pol.getSize() == specificNumber;
        });
      }
      std::cout << count << '\n';
    } else if (cmd == "RECTS") {
    } else if (cmd == "RIGHTSHAPES") {
    }

    cmd.clear();
    subcmd.clear();
  }

  return 0;
}
