#include "commands.hpp"
#include <numeric>

using namespace std::placeholders;

namespace nikiforov
{
  void takingArea(const std::vector< Polygon >& figure, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;
    std::vector< double > areaOfEach;

    if (option == "ODD")
    {
      std::vector< Polygon > figuresOdd;
      std::copy_if(
        std::begin(figure), std::end(figure),
        std::back_inserter(figuresOdd),
        isOdd
      );

      std::transform(
        std::begin(figuresOdd), std::end(figuresOdd),
        std::back_inserter(areaOfEach),
        getArea
      );
      out << std::accumulate(std::begin(areaOfEach), std::end(areaOfEach), 0) << "\n";
    }
    else if (option == "EVEN")
    {
      std::vector< Polygon > figuresEven;
      std::copy_if(
        std::begin(figure), std::end(figure),
        std::back_inserter(figuresEven),
        isEven
      );

      std::transform(
        std::begin(figuresEven), std::end(figuresEven),
        std::back_inserter(areaOfEach),
        getArea
      );
      out << std::accumulate(std::begin(areaOfEach), std::end(areaOfEach), 0) << "\n";
    }
    else if (option == "MEAN")
    {
      std::transform(
        std::begin(figure), std::end(figure),
        std::back_inserter(areaOfEach),
        getArea
      );
      out << (std::accumulate(std::begin(areaOfEach), std::end(areaOfEach), 0)) / figure.size() << "\n";
    }
    else if (isdigit(option[0]))
    {
      std::vector< Polygon > figuresNumOfVert;
      std::copy_if(
        std::begin(figure), std::end(figure),
        std::back_inserter(figuresNumOfVert),
        std::bind(numOfVert, std::stoi(option), _1)
      );

      std::transform(
        std::begin(figuresNumOfVert), std::end(figuresNumOfVert),
        std::back_inserter(areaOfEach),
        getArea
      );
      out << std::accumulate(std::begin(areaOfEach), std::end(areaOfEach), 0) << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }
  }

  double getPoints(const Point& first, const Point& second)
  {
    return first.x * second.y - first.y * second.x;
  };

  double getArea(const Polygon& polygon)
  {
    double res = 0;
    size_t sizePol = polygon.points.size();
    std::vector< double > countArea;

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
    return polygon.points.size() % 2 == 0 ? true : false;
  }

  bool isEven(const Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0 ? true : false;
  }

  bool numOfVert(int num, const Polygon& polygon)
  {
    return polygon.points.size() == num ? true : false;
  }

  void takingMax(const std::vector< Polygon >& figure, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;

    if (option == "AREA")
    {
      std::vector< double > areaOfEach;
      std::transform(
        std::begin(figure), std::end(figure),
        std::back_inserter(areaOfEach),
        getArea
      );
      out << *std::max_element(std::begin(areaOfEach), std::end(areaOfEach)) << "\n";
    }
    else if (option == "VERTEXES")
    {
      std::vector< size_t > vectOfAllVertexes;
      std::transform(
        std::begin(figure), std::end(figure),
        std::back_inserter(vectOfAllVertexes),
        numOfVertexes
      );
      out << *std::max_element(std::begin(vectOfAllVertexes), std::end(vectOfAllVertexes)) << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }
  }

  size_t numOfVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }

  void takingMin(const std::vector< Polygon >& figure, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;

    if (option == "AREA")
    {
      std::vector< double > areaOfEach;
      std::transform(
        std::begin(figure), std::end(figure),
        std::back_inserter(areaOfEach),
        getArea
      );
      out << *std::min_element(std::begin(areaOfEach), std::end(areaOfEach)) << "\n";
    }
    else if (option == "VERTEXES")
    {
      std::vector< size_t > vectOfAllVertexes;
      std::transform(
        std::begin(figure), std::end(figure),
        std::back_inserter(vectOfAllVertexes),
        numOfVertexes
      );
      out << *std::min_element(std::begin(vectOfAllVertexes), std::end(vectOfAllVertexes)) << "\n";
    }
    else
    {
      throw std::out_of_range("");
    }
  }

  void takingCount(const std::vector< Polygon >& figure, std::istream& in, std::ostream& out)
  {
    std::string option = "";
    in >> option;

    if (option == "ODD")
    {
      out << count_if(std::begin(figure), std::end(figure), isOdd);
    }
    else if (option == "EVEN")
    {
      out << count_if(std::begin(figure), std::end(figure), isEven);
    }
    else if (isdigit(option[0]))
    {
      out << count_if(std::begin(figure), std::end(figure), std::bind(numOfVert, stoi(option), _1));
    }
    else
    {
      throw std::out_of_range("");
    }
  }
}
