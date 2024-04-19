#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <string>
#include <functional>
#include "command.hpp"

namespace zasulsky
{
  class CmdTree
  {
  public:
    CmdTree();

    void doCommand(const std::string& cmd,
      const polygons& data,
      std::ostream& out) const;

    void doCommand(const std::string& cmd,
      const polygons& data,
      int num,
      std::ostream& out) const;

    void doCommand(const std::string& cmd,
      const polygons& data,
      const Polygon& pol,
      std::ostream& out) const;

    using typeF = std::function< void(const polygons&, std::ostream&) >;
    using typeS = std::function< void(const polygons&, int, std::ostream&) >;
    using typeT = std::function< void(const polygons&, std::ostream&, const Polygon&) >;

    std::map< std::string, typeF > cmdsOne;
    std::map< std::string, typeS > cmdsTwo;
    std::map< std::string, typeT > cmdsThree;
  };
  bool isSimpleCmd(std::string name);
  std::ostream& printInvCmd(std::ostream& out);
}

zasulsky::Polygon stringToPolygon(const std::string& inputString);
#endif
