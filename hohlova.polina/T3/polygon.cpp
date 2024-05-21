#include <iostream>
#include "polygon.hpp"
#include "delimiter.hpp"

std::istream& hohlova::operator>>(std::istream& in, Point& dest)
{

    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Point point{};
    using exp = DelimiterIO;
    if (in >> exp{ '(' } >> point.x >> exp{ ';' } >> point.y >> exp{ ')' })
        dest = point;
    else
        in.setstate(std::ios::failbit);
    return in;

}

bool hohlova::checkPointCount(size_t expectedPoints, size_t actualPoints) {
    return actualPoints == expectedPoints;
}

std::istream& hohlova::operator>>(std::istream& in, Polygon& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    size_t numVertices = 0;
    if (!(in >> numVertices) || numVertices < 3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::vector<Point> polygons;
    Point currentPoint;

    while (in >> currentPoint) {
        polygons.push_back(currentPoint);
        if (in.peek() == '\n' || in.peek() == EOF) {
            break;
        }
    }
    if (!checkPointCount(numVertices, polygons.size())) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (in.peek() == '\n') {
        in.get();
    }
    else if (in.peek() == EOF) {
        in.clear();
    }
    dest = Polygon{ polygons };
    return in;
}


bool hohlova::operator==(const Polygon& firstpolygon, const Polygon& secondpolygon)
{
    if (firstpolygon.points.size() != secondpolygon.points.size())
        return false;
    for (size_t i = 0; i < firstpolygon.points.size(); ++i)
    {
        if (firstpolygon.points[i].x != secondpolygon.points[i].x || firstpolygon.points[i].y != secondpolygon.points[i].y)
        {
            return false;
        }
    }

    return true;
}
