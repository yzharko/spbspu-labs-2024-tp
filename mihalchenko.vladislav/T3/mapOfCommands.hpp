#ifndef MAPOFCOMMANDS_HPP
#define MAPOFCOMMANDS_HPP

#include <map>
#include <functional>
#include <vector>
// #include <string>
#include "functions.hpp"

namespace mihalchenko
{
  using argString = std::function<void(const std::vector< Polygon > &, std::ostream &)>;
  using argDigit = std::function<void(const std::vector< Polygon > &, int, std::ostream &)>;
  using argDigitWithPolygon = std::function<void(const std::vector< Polygon > &, std::ostream &, const Polygon &)>;

  std::map<std::string, argString> cmdWithStrings;
  std::map<std::string, argDigit> cmdwithStringAndDigit;
  std::map<std::string, argDigitWithPolygon> cmdwithPolygon;

  void doCmdWithStrings(const std::string &cmd,
                        const std::vector< Polygon > &data,
                        std::ostream &out);

  void doCmdWithStringAndDigit(const std::string &cmd,
                               const std::vector< Polygon > &data,
                               int num,
                               std::ostream &out);

  void doCmdWithDigitAndPolygon(const std::string &cmd,
                                const std::vector< Polygon > &data,
                                const Polygon &pol,
                                std::ostream &out);
}

#endif
