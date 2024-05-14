#include "commands.hpp"
#include <numeric>
#include <iomanip>

namespace nikiforov
{
  using namespace std::placeholders;

  void takingArea(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;
    out << std::fixed << std::setprecision(1);

    if (option == "ODD")
    {
      getAreaOdd(shapes, out);
    }
    else if (option == "EVEN")
    {
      getAreaEven(shapes, out);
    }
    else if (option == "MEAN" && !shapes.empty())
    {
      getAreaMean(shapes, out);
    }
    else if (isdigit(option[0]) && stoi(option) > 2)
    {
      getAreaNumOfVerts(shapes, size_t(stoi(option)), out);
    }
    else
    {
      throw std::out_of_range("");
    }
  }

  void getAreaOdd(const std::vector< Polygon >& shapes, std::ostream& out)
  {
    std::vector< Polygon > figuresOdd;
    std::copy_if(
      std::begin(shapes), std::end(shapes),
      std::back_inserter(figuresOdd),
      isOdd
    );

    out << getAreaResult(figuresOdd, "area") << "\n";
  }

  void getAreaEven(const std::vector< Polygon >& shapes, std::ostream& out)
  {
    std::vector< Polygon > figuresEven;
    std::copy_if(
      std::begin(shapes), std::end(shapes),
      std::back_inserter(figuresEven),
      isEven
    );

    out << getAreaResult(figuresEven, "area") << "\n";
  }

  void getAreaMean(const std::vector< Polygon >& shapes, std::ostream& out)
  {
    out << getAreaResult(shapes, "area") / shapes.size() << "\n";
  }

  void getAreaNumOfVerts(const std::vector< Polygon >& shapes, const size_t& option, std::ostream& out)
  {
    std::vector< Polygon > figuresNumOfVert;
    std::copy_if(
      std::begin(shapes), std::end(shapes),
      std::back_inserter(figuresNumOfVert),
      std::bind(numOfVert, option, _1)
    );

    out << getAreaResult(figuresNumOfVert, "area") << "\n";
  }

  int getPoints(const Point& first, const Point& second)
  {
    return first.x * second.y - first.y * second.x;
  };

  double getArea(const Polygon& polygon)
  {
    double res = 0;
    size_t sizePol = polygon.points.size();
    std::vector< int > countArea;

    std::transform(++polygon.points.cbegin(), polygon.points.cend(),
      polygon.points.cbegin(),
      std::back_inserter(countArea),
      std::bind(getPoints, _1, _2)
    );

    countArea.push_back(getPoints(polygon.points.at(0), polygon.points.at(sizePol - 1)));
    res = std::accumulate(std::begin(countArea), std::end(countArea), 0);
    return abs(res) / 2;
  }

  bool isOdd(const Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0;
  }

  bool isEven(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool numOfVert(size_t num, const Polygon& polygon)
  {
    return polygon.points.size() == num;
  }

  void takingMax(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;
    out << std::fixed << std::setprecision(1);

    if (option == "AREA" && !shapes.empty())
    {
      out << getAreaResult(shapes, "max") << "\n";
    }
    else if (option == "VERTEXES" && !shapes.empty())
    {
      out << getVertexesResult(shapes, "max") << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }
  }

  size_t countOfVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }

  void takingMin(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;
    out << std::fixed << std::setprecision(1);

    if (option == "AREA" && !shapes.empty())
    {
      out << getAreaResult(shapes, "min") << "\n";
    }
    else if (option == "VERTEXES" && !shapes.empty())
    {
      out << getVertexesResult(shapes, "min") << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }
  }

  void takingCount(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;

    if (option == "ODD")
    {
      countOddVerts(shapes, out);
    }
    else if (option == "EVEN")
    {
      countEvenVerts(shapes, out);
    }
    else if (isdigit(option[0]) && stoi(option) > 2)
    {
      countSpecVerts(shapes, size_t(stoi(option)),out);
    }
    else
    {
      throw std::out_of_range("");
    }
  }

  void countOddVerts(const std::vector<Polygon>& shapes, std::ostream& out)
  {
    out << count_if(std::begin(shapes), std::end(shapes), isOdd) << "\n";
  }

  void countEvenVerts(const std::vector<Polygon>& shapes, std::ostream& out)
  {
    out << count_if(std::begin(shapes), std::end(shapes), isEven) << "\n";
  }

  void countSpecVerts(const std::vector<Polygon>& shapes, const size_t& option, std::ostream& out)
  {
    out << count_if(std::begin(shapes), std::end(shapes), std::bind(numOfVert, option, _1)) << "\n";
  }

  double getAreaResult(const std::vector< Polygon >& shapes, std::string mode)
  {
    std::vector< double > areaOfEach;

    std::transform(
      std::begin(shapes), std::end(shapes),
      std::back_inserter(areaOfEach),
      getArea
    );
    if (mode == "area")
    {
      return std::accumulate(std::begin(areaOfEach), std::end(areaOfEach), 0.0);
    }
    else if (mode == "max")
    {
      return *std::max_element(std::begin(areaOfEach), std::end(areaOfEach));
    }
    else
    {
      return *std::min_element(std::begin(areaOfEach), std::end(areaOfEach));
    }
  }

  size_t getVertexesResult(const std::vector< Polygon >& shapes, std::string mode)
  {
    std::vector< size_t > vectOfAllVertexes;

    std::transform(
      std::begin(shapes), std::end(shapes),
      std::back_inserter(vectOfAllVertexes),
      countOfVertexes
    );
    if (mode == "max")
    {
      return *std::max_element(std::begin(vectOfAllVertexes), std::end(vectOfAllVertexes));
    }
    else
    {
      return *std::min_element(std::begin(vectOfAllVertexes), std::end(vectOfAllVertexes));
    }
  }

  void takingIntersections(const std::vector< Polygon >& shapes, std::istream& input, std::ostream& out)
  {
    std::vector< std::pair< Point, Point > > vectorsIntersectios;
    nikiforov::Polygon shapeIntersectios;

    if (input >> shapeIntersectios)
    {
      std::transform(++shapeIntersectios.points.cbegin(), shapeIntersectios.points.cend(),
        shapeIntersectios.points.cbegin(),
        std::back_inserter(vectorsIntersectios),
        std::bind(getPointsInter, _2, _1)
      );

      size_t sizePol = shapeIntersectios.points.size();
      vectorsIntersectios.push_back(getPointsInter(shapeIntersectios.points.at(0), shapeIntersectios.points.at(sizePol - 1)));

      std::vector< size_t > resultsIntersectios;
      std::transform(
        std::begin(shapes), std::end(shapes),
        std::back_inserter(resultsIntersectios),
        std::bind(intersectingLines, vectorsIntersectios, _1)
      );

      out << std::count_if(std::begin(resultsIntersectios), std::end(resultsIntersectios),
        [](size_t countIntersections)
        {
          return countIntersections > 0;
        });
      out << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }
  }

  std::pair< Point, Point > getPointsInter(const Point& first, const Point& second)
  {
    return std::make_pair(first, second);
  }

  size_t intersectingLines(const std::vector< std::pair< Point, Point > >& vectorsIntersectios, const Polygon& shapes)
  {
    return std::count_if(std::begin(vectorsIntersectios), std::end(vectorsIntersectios),
      std::bind(intersectingShapes, _1, shapes)
    );
  }

  bool intersectingShapes(const std::pair < Point, Point >& vectIntersectios, const Polygon& polygon)
  {
    std::vector< std::pair< Point, Point > > vectorsPolygon;

    std::transform(++polygon.points.cbegin(), polygon.points.cend(),
      polygon.points.cbegin(),
      std::back_inserter(vectorsPolygon),
      std::bind(getPointsInter, _2, _1)
    );

    size_t sizePol = polygon.points.size();
    vectorsPolygon.push_back(getPointsInter(polygon.points.at(0), polygon.points.at(sizePol - 1)));

    return std::count_if(std::begin(vectorsPolygon), std::end(vectorsPolygon),
      std::bind(intersecting, _1, vectIntersectios)
    );
  }

  bool intersecting(const std::pair < Point, Point >& vectPolygon, const std::pair < Point, Point >& vectIntersectios)
  {
    return doIntersect(vectPolygon.first, vectPolygon.second, vectIntersectios.first, vectIntersectios.second);
  }

  bool doIntersect(Point begin1, Point end1, Point begin2, Point end2)
  {
    int o1 = orientation(begin1, end1, begin2);
    int o2 = orientation(begin1, end1, end2);
    int o3 = orientation(begin2, end2, begin1);
    int o4 = orientation(begin2, end2, end1);

    if (o1 != o2 && o3 != o4)
    {
      return true;
    }

    if (o1 == o2 && o1 == o3 && o1 != o4)
    {
      return true;
    }

    if (o1 == 0 && onSegment(begin1, begin2, end1))
    {
      return true;
    }

    if (o2 == 0 && onSegment(begin1, end2, end1))
    {
      return true;
    }

    if (o3 == 0 && onSegment(begin2, begin1, end2))
    {
      return true;
    }

    if (o4 == 0 && onSegment(begin2, end1, end2))
    {
      return true;
    }
    return false;
  }

  int orientation(Point p, Point q, Point r)
  {
    int collinear = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (collinear == 0)
    {
      return 0;
    }
    return (collinear > 0) ? 1 : 2;
  }

  bool onSegment(Point p, Point q, Point r)
  {
    if (xCoordinatePointInSegment(p, q, r) && yCoordinatePointInSegment(p, q, r))
    {
      return true;
    }
    return false;
  }

  bool xCoordinatePointInSegment(Point p, Point q, Point r)
  {
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x);
  }

  bool yCoordinatePointInSegment(Point p, Point q, Point r)
  {
    return q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
  }

  void takingSame(const std::vector<Polygon>& shapes, std::istream& input, std::ostream& out)
  {
    nikiforov::Polygon shapeSame;

    if (input >> shapeSame)
    {
      out << std::count_if(std::begin(shapes), std::end(shapes), std::bind(countSame, shapeSame, _1)) << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }

  }

  bool countSame(const Polygon& polygonSame, const Polygon& polygonShape)
  {
    size_t sizeShape = polygonShape.points.size();
    size_t sizeSame = polygonSame.points.size();

    if (sizeSame == sizeShape)
    {
      std::vector< int > resultsSame;
      std::transform(
        std::begin(polygonShape.points), std::end(polygonShape.points),
        std::begin(polygonSame.points),
        std::back_inserter(resultsSame),
        std::bind(pointsSame, _1, _2)
      );
      auto it = std::search_n(resultsSame.begin(), resultsSame.end(), sizeSame, resultsSame.at(0));
      return it != resultsSame.end();
    }
    else
    {
      return false;
    }
  }

  int pointsSame(const Point& first, const Point& second)
  {
    return (first.x - second.x) + (first.y - second.y);
  }

  void takingError(std::ostream& out, const std::string& errorStr)
  {
    out << errorStr << "\n";
  }
}
