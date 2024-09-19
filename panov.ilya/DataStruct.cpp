#include "DataStruct.h"
#include <regex>
#include <sstream>
#include <cstdio>

namespace panov {
  std::complex<double> parseComplex(const std::string& str)
  {
    double real, imag;
    std::sscanf(str.c_str(), "#c(%lf %lf)", &real, &imag);
    return { real, imag };
  }
  std::pair<long long, unsigned long long> parseRational(const std::string& str)
  {
    long long numerator;
    unsigned long long denominator;
    std::sscanf(str.c_str(), "(:N %lld:D %llu:)", &numerator, &denominator);
    return { numerator, denominator };
  }
  std::istream& operator>>(std::istream& is, DataStruct& data)
  {
    std::string line;
    if (!std::getline(is, line))
    {
      return is;
    }
    if (line.front() != '(' || line.back() != ')')
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    line = line.substr(1, line.size() - 2);
    std::regex key1Regex(R"(key1\s+#c\([-+]?[\d]*\.?[\d]+ [-+]?[\d]*\.?[\d]+\))");
    std::regex key2Regex(R"(key2\s+\(:N [-+]?[\d]+:D [\d]+:\))");
    std::regex key3Regex(R"(key3\s+\"[^\"]*\")");
    std::smatch match;
    if (std::regex_search(line, match, key1Regex))
    {
      data.key1 = parseComplex(match.str().substr(5));
    }
    if (std::regex_search(line, match, key2Regex))
    {
      data.key2 = parseRational(match.str().substr(5));
    }
    if (std::regex_search(line, match, key3Regex))
    {
      data.key3 = match.str().substr(6);
      data.key3.pop_back();
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const DataStruct& data)
  {
    os << "(key1 #c(" << data.key1.real() << " " << data.key1.imag() << "):"
      << "key2 (:N " << data.key2.first << ":D " << data.key2.second << "):"
      << "key3 \"" << data.key3 << "\":)";
    return os;
  }
}
