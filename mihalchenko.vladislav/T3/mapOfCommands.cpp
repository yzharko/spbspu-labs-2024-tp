#include "mapOfCommands.hpp"
// #include "figures.hpp"

void mihalchenko::doCmdWithStrings(const std::string &cmd,
                                   const std::vector<Polygon> &data,
                                   std::ostream &out)
{
  argString function = cmdWithStrings.at(cmd);
  function(data, out);
}

void mihalchenko::doCmdWithStringAndDigit(const std::string &cmd,
                                          const std::vector<Polygon> &data,
                                          int num,
                                          std::ostream &out)
{
  argDigit function = cmdwithStringAndDigit.at(cmd);
  function(data, num, out);
}

void mihalchenko::doCmdWithDigitAndPolygon(const std::string &cmd,
                                           const std::vector<Polygon> &data,
                                           const Polygon &pol,
                                           std::ostream &out)
{
  argDigitWithPolygon function = cmdwithPolygon.at(cmd);
  function(data, out, pol);
}
