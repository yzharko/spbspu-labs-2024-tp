#include "commands.hpp"
#include <numeric>
#include <iomanip>

using namespace std::placeholders;

namespace nikiforov
{
  void takingArea(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;
    out << std::fixed << std::setprecision(1);

    if (option == "ODD" && !shapes.empty())
    {
      std::vector< Polygon > figuresOdd;
      std::copy_if(
        std::begin(shapes), std::end(shapes),
        std::back_inserter(figuresOdd),
        isOdd
      );

      out << getAreaResult(figuresOdd, "area") << "\n";
    }
    else if (option == "EVEN" && !shapes.empty())
    {
      std::vector< Polygon > figuresEven;
      std::copy_if(
        std::begin(shapes), std::end(shapes),
        std::back_inserter(figuresEven),
        isEven
      );

      out << getAreaResult(figuresEven, "area") << "\n";
    }
    else if (option == "MEAN" && !shapes.empty())
    {
      out << getAreaResult(shapes, "area") / shapes.size() << "\n";
    }
    else if (isdigit(option[0]) && !shapes.empty())
    {
      std::vector< Polygon > figuresNumOfVert;
      std::copy_if(
        std::begin(shapes), std::end(shapes),
        std::back_inserter(figuresNumOfVert),
        std::bind(numOfVert, size_t(stoi(option)), _1)
      );

      out << getAreaResult(figuresNumOfVert, "area") << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }
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

    if (option == "ODD" && !shapes.empty())
    {
      out << count_if(std::begin(shapes), std::end(shapes), isOdd) << "\n";
    }
    else if (option == "EVEN" && !shapes.empty())
    {
      out << count_if(std::begin(shapes), std::end(shapes), isEven) << "\n";
    }
    else if (isdigit(option[0]) && !shapes.empty())
    {
      out << count_if(std::begin(shapes), std::end(shapes), std::bind(numOfVert, size_t(stoi(option)), _1)) << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }
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

  double getVertexesResult(const std::vector< Polygon >& shapes, std::string mode)
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
}
