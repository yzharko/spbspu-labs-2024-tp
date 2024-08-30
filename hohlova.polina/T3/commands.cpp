#include "commands.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <functional>
#include <limits>

void hohlova::Error(std::ostream& out)
{
    out << "<INVALID COMMAND>\n";
}

double hohlova::CalcArea(const Polygon& polygons)
{
    if (polygons.points.size() < 3) {
        return 0.0;
    }

    std::function<double(size_t, double)> calcAreaRecursive = [&](size_t i, double area) -> double {
        if (i == polygons.points.size()) {
            return area;
        }
        size_t j = (i + 1) % polygons.points.size();
        area += (polygons.points[i].x + polygons.points[j].x) * (polygons.points[i].y - polygons.points[j].y);
        return calcAreaRecursive(i + 1, area);
        };

    double area = calcAreaRecursive(0, 0.0);
    return std::abs(area) / 2.0;
}



unsigned long long int hohlova::countVertices(const Polygon& polygon)
{
    return polygon.points.size();
}

void hohlova::AREACommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
    using CommandFunction = std::function<void(const std::vector<Polygon>&, std::ostream&)>;

    std::map<std::string, CommandFunction> subcommand;
    {
        using namespace std::placeholders;

        subcommand["EVEN"] = std::bind(AREACommandEven, _1, _2);
        subcommand["ODD"] = std::bind(AREACommandOdd, _1, _2);
        subcommand["MEAN"] = std::bind(AREACommandMean, _1, _2);
    }
    std::string incommand;
    in >> incommand;
    try
    {
        subcommand.at(incommand)(polygons, out);
    }
    catch (const std::exception& e)
    {
        if (std::isdigit(incommand[0]))
        {
            unsigned long long numVertices = std::stoull(incommand);
            AREACommandNumVertices(polygons, numVertices, out);
        }
        else
            Error(out);
    }
}

void hohlova::AREACommandEven(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<double(const std::vector<Polygon>&, size_t)>
      calcTotalAreaRecursive = [&](const std::vector<Polygon>& polygons, size_t index) -> double {
        if (index == polygons.size()) {
            return 0.0;
        }
        double area = 0.0;
        if (polygons[index].points.size() % 2 == 0) {
            area = CalcArea(polygons[index]);
        }
        return area + calcTotalAreaRecursive(polygons, index + 1);
        };

    double totalArea = calcTotalAreaRecursive(polygons, 0);
    out << std::fixed << std::setprecision(1) << totalArea << std::endl;
}

void hohlova::AREACommandOdd(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<double(const std::vector<Polygon>&, size_t)>
      calcTotalAreaRecursive = [&](const std::vector<Polygon>& polygons, size_t index) -> double {
        if (index == polygons.size()) {
            return 0.0;
        }
        double area = 0.0;
        if (polygons[index].points.size() % 2 != 0) {
            area = CalcArea(polygons[index]);
        }
        return area + calcTotalAreaRecursive(polygons, index + 1);
        };

    double totalArea = calcTotalAreaRecursive(polygons, 0);
    out << std::fixed << std::setprecision(1) << totalArea << std::endl;
}

void hohlova::AREACommandMean(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<std::pair<double, int>(const std::vector<Polygon>&, size_t)> calcTotalAreaAndCountRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> std::pair<double, int> {
        if (index == polygons.size()) {
            return { 0.0, 0 };
        }
        double area = CalcArea(polygons[index]);
        auto result = calcTotalAreaAndCountRecursive(polygons, index + 1);
        return { result.first + area, result.second + 1 };
        };

    auto result = calcTotalAreaAndCountRecursive(polygons, 0);
    double totalArea = result.first;
    int count = result.second;

    if (count > 0) {
        double meanArea = totalArea / count;
        out << std::fixed << std::setprecision(1) << meanArea << std::endl;
    }
    else {
        Error(out);
    }
}

void hohlova::AREACommandNumVertices(const std::vector<Polygon>& polygons, unsigned long long numVertices, std::ostream& out)
{
    if (numVertices < 3) {
        Error(out);
        return;
    }

    std::function<double(const std::vector<Polygon>&, size_t)> calcTotalAreaRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> double {
        if (index == polygons.size()) {
            return 0.0;
        }
        double area = 0.0;
        if (countVertices(polygons[index]) == numVertices) {
            area = CalcArea(polygons[index]);
        }
        return area + calcTotalAreaRecursive(polygons, index + 1);
        };

    double totalArea = calcTotalAreaRecursive(polygons, 0);
    out << std::fixed << std::setprecision(1) << totalArea << std::endl;
}

void hohlova::MAXCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
    using CommandFunction = std::function<void(const std::vector<Polygon>&, std::ostream&)>;
    std::map<std::string, CommandFunction> subcommand;
    {
        using namespace std::placeholders;
        subcommand["AREA"] = std::bind(MAXCommandArea, _1, _2);
        subcommand["VERTEXES"] = std::bind(MAXCommandVertices, _1, _2);
    }
    std::string incommand;
    in >> incommand;
    try
    {
        subcommand.at(incommand)(polygons, out);
    }
    catch (const std::exception& e)
    {
        Error(out);
    }
}

void hohlova::MAXCommandArea(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<std::pair<double, int>(const std::vector<Polygon>&, size_t)> findMaxAreaRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> std::pair<double, int> {
        if (index == polygons.size()) {
            return { 0.0, 0 };
        }
        double area = CalcArea(polygons[index]);
        auto result = findMaxAreaRecursive(polygons, index + 1);
        double maxValue = std::max(result.first, area);
        return { maxValue, result.second + 1 };
        };

    auto result = findMaxAreaRecursive(polygons, 0);
    double maxValue = result.first;
    int count = result.second;

    if (count == 0) {
        Error(out);
    }
    else {
        out << std::fixed << std::setprecision(1) << maxValue << std::endl;
    }
}

void hohlova::MAXCommandVertices(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<std::pair<int, int>(const std::vector<Polygon>&, size_t)> findMaxVerticesRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> std::pair<int, int> {
        if (index == polygons.size()) {
            return { 0, 0 };
        }
        int vertices = countVertices(polygons[index]);
        auto result = findMaxVerticesRecursive(polygons, index + 1);
        int maxVertices = std::max(result.first, vertices);
        return { maxVertices, result.second + 1 };
        };

    auto result = findMaxVerticesRecursive(polygons, 0);
    int maxVertices = result.first;
    int count = result.second;

    if (count == 0) {
        Error(out);
    }
    else {
        out << maxVertices << std::endl;
    }
}

void hohlova::MINCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
    using CommandFunction = std::function<void(const std::vector<Polygon>&, std::ostream&)>;
    std::map<std::string, CommandFunction> subcommand;
    {
        using namespace std::placeholders;
        subcommand["AREA"] = std::bind(MINCommandArea, _1, _2);
        subcommand["VERTEXES"] = std::bind(MINCommandVertices, _1, _2);
    }
    std::string incommand;
    in >> incommand;
    try
    {
        subcommand.at(incommand)(polygons, out);
    }
    catch (const std::exception& e)
    {
        Error(out);
    }
}

void hohlova::MINCommandArea(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<double(const std::vector<Polygon>&, size_t, double)> findMinAreaRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index, double minValue) -> double {
        if (index == polygons.size()) {
            return minValue;
        }
        double area = CalcArea(polygons[index]);
        return findMinAreaRecursive(polygons, index + 1, std::min(minValue, area));
        };

    double minValue = findMinAreaRecursive(polygons, 0, std::numeric_limits<double>::max());
    out << std::fixed << std::setprecision(1) << minValue << std::endl;
}

void hohlova::MINCommandVertices(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<int(const std::vector<Polygon>&, size_t, int)> findMinVerticesRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index, int minVertices) -> int {
        if (index == polygons.size()) {
            return minVertices;
        }
        int vertices = countVertices(polygons[index]);
        return findMinVerticesRecursive(polygons, index + 1, std::min(minVertices, vertices));
        };

    int minVertices = findMinVerticesRecursive(polygons, 0, std::numeric_limits<int>::max());
    out << minVertices << std::endl;
}

void hohlova::COUNTCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
    using CommandFunction = std::function<void(const std::vector<Polygon>&, std::ostream&)>;
    std::map<std::string, CommandFunction> subcommand;
    {
        using namespace std::placeholders;
        subcommand["EVEN"] = std::bind(COUNTCommandEven, _1, _2);
        subcommand["ODD"] = std::bind(COUNTCommandOdd, _1, _2);
    }
    std::string incommand;
    in >> incommand;
    try
    {
        subcommand.at(incommand)(polygons, out);
    }
    catch (const std::exception& e)
    {
        if (std::isdigit(incommand[0]))
        {
            unsigned long long numVertices = std::stoull(incommand);
            COUNTCommandNumVertices(polygons, numVertices, out);
        }
        else
            Error(out);
    }
}

void hohlova::COUNTCommandOdd(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<int(const std::vector<Polygon>&, size_t)> countOddVerticesRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> int {
        if (index == polygons.size()) {
            return 0;
        }
        int count = countOddVerticesRecursive(polygons, index + 1);
        if (countVertices(polygons[index]) % 2 != 0) {
            count++;
        }
        return count;
        };

    int count = countOddVerticesRecursive(polygons, 0);
    out << count << std::endl;
}

void hohlova::COUNTCommandEven(const std::vector<Polygon>& polygons, std::ostream& out)
{
    std::function<int(const std::vector<Polygon>&, size_t)> countEvenVerticesRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> int {
        if (index == polygons.size()) {
            return 0;
        }
        int count = countEvenVerticesRecursive(polygons, index + 1);
        if (countVertices(polygons[index]) % 2 == 0) {
            count++;
        }
        return count;
        };

    int count = countEvenVerticesRecursive(polygons, 0);
    out << count << std::endl;
}

void hohlova::COUNTCommandNumVertices(const std::vector<Polygon>& polygons, unsigned long long numVertices, std::ostream& out)
{
    if (numVertices < 3) {
        Error(out);
        return;
    }

    std::function<int(const std::vector<Polygon>&, size_t)> countVerticesRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> int {
        if (index == polygons.size()) {
            return 0;
        }
        int count = countVerticesRecursive(polygons, index + 1);
        if (countVertices(polygons[index]) == numVertices) {
            count++;
        }
        return count;
        };

    int count = countVerticesRecursive(polygons, 0);
    out << count << std::endl;
}

void hohlova::PERMSCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
    Polygon polyg;
    in >> polyg;
    if (in.fail())
    {
        in.clear();
    }
    else
    {
        PERMScount(polyg, polygons, out);
        int count = PERMScount(polyg, polygons, out);
        out << count << std::endl;
    }
}

int hohlova::PERMScount(const Polygon& polyg, const std::vector<Polygon>& polygons)
{
    std::function<bool(const Polygon&, const Polygon&, std::vector<bool>&, size_t, size_t)> isPermutationRecursive =
        [&](const Polygon& polyg, const Polygon& polygon, std::vector<bool>& used, size_t polygonIndex, size_t polygIndex) -> bool {
        if (polygonIndex == polygon.points.size()) {
            return true;
        }
        if (polygIndex == polyg.points.size()) {
            return false;
        }
        const auto& point = polygon.points[polygonIndex];
        if (!used[polygIndex] && ((point.x == polyg.points[polygIndex].x && point.y == polyg.points[polygIndex].y) ||
          (point.x == polyg.points[polygIndex].y && point.y == polyg.points[polygIndex].x))) {
            used[polygIndex] = true;
            if (isPermutationRecursive(polyg, polygon, used, polygonIndex + 1, 0)) {
                return true;
            }
            used[polygIndex] = false;
        }
        return isPermutationRecursive(polyg, polygon, used, polygonIndex, polygIndex + 1);
        };

    std::function<int(const std::vector<Polygon>&, size_t)> countPermutationsRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> int {
        if (index == polygons.size()) {
            return 0;
        }
        int count = countPermutationsRecursive(polygons, index + 1);
        if (polygons[index].points.size() == polyg.points.size()) {
            std::vector<bool> used(polyg.points.size(), false);
            if (isPermutationRecursive(polyg, polygons[index], used, 0, 0)) {
                count++;
            }
        }
        return count;
        };

    return countPermutationsRecursive(polygons, 0);
}

void hohlova::MAXSEQCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
    Polygon polygon;
    in >> polygon;
    if (in.fail()) {
        Error(out);
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    std::function<std::pair<int, int>(const std::vector<Polygon>&, size_t, const Polygon&)> findMaxSeqRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index, const Polygon& polygon) -> std::pair<int, int> {
        if (index == polygons.size()) {
            return { 0, 0 };
        }
        auto result = findMaxSeqRecursive(polygons, index + 1, polygon);
        if (polygons[index] == polygon) {
            result.second++;
            result.first = std::max(result.first, result.second);
        }
        else {
            result.second = 0;
        }
        return result;
        };

    auto result = findMaxSeqRecursive(polygons, 0, polygon);
    out << result.first << std::endl;
}

void hohlova::RIGHTSHAPESCommandMenu(const std::vector<Polygon>& polygons, std::ostream& out)
{
    int count = countRightShapes(polygons);
    out << count << std::endl;
}

int hohlova::countRightShapes(const std::vector<Polygon>& polygons)
{
    std::function<bool(const Polygon&, size_t)> isRightShapeRecursive =
        [&](const Polygon& polygon, size_t index) -> bool {
        if (index == polygon.points.size()) {
            return false;
        }
        size_t j = (index + 1) % polygon.points.size();
        size_t k = (j + 1) % polygon.points.size();
        int dx1 = polygon.points[j].x - polygon.points[index].x;
        int dy1 = polygon.points[j].y - polygon.points[index].y;
        int dx2 = polygon.points[k].x - polygon.points[j].x;
        int dy2 = polygon.points[k].y - polygon.points[j].y;
        if (dx1 * dx2 + dy1 * dy2 == 0) {
            return true;
        }
        return isRightShapeRecursive(polygon, index + 1);
        };

    std::function<int(const std::vector<Polygon>&, size_t)> countRightShapesRecursive =
        [&](const std::vector<Polygon>& polygons, size_t index) -> int {
        if (index == polygons.size()) {
            return 0;
        }
        int count = countRightShapesRecursive(polygons, index + 1);
        if (isRightShapeRecursive(polygons[index], 0)) {
            count++;
        }
        return count;
        };

    return countRightShapesRecursive(polygons, 0);
}


