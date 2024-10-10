#include <iostream>
#include <sstream>
#include <regex>
#include <vector>

class Point {
public:
    int x, y;
};

class Polygon {
public:
    std::vector<Point> points;
};

std::istream& operator>>(std::istream& in, Point& point) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in; // Stream is in a bad state
    }
    
    std::string str;
    in >> str;
    if (!isPoint(str)) {
        in.setstate(std::ios_base::failbit);
        return in;
    }
    
    char ch;
    std::stringstream ss(str);
    ss >> ch >> point.x >> ch >> point.y >> ch;
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in; // Stream is in a bad state
    }
    
    poly.points.clear();
    std::size_t n;
    in >> n;
    if (in.fail() || n < 3) {
        in.setstate(std::ios_base::failbit);
        return in;
    }
    
    poly.points.resize(n);
    for (auto& p : poly.points) {
        if (in.peek() == '\n') {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        in >> p;
    }
    
    if (in.peek() != '\n') {
        in.setstate(std::ios_base::failbit);
    }
    
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point) {
    return (out << '(' << point.x << ';' << point.y << ')');
}

bool isPoint(const std::string& str) {
    std::regex pattern("\\(-?[0-9]+;-?[0-9]+\\)");
    return std::regex_match(str, pattern);
}
