#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <string>
#include <functional>
#include "command.hpp"

class CmdTree
{
public:
  CmdTree();

  void doCommand(const std::string& cmd, dictOfDicts& ref, std::string&) const;

  void doCommand(const std::string& cmd, dictOfDicts& ref, std::string, std::ostream&) const;

  void doCommand(const std::string& cmd, dictOfDicts& ref, std::string, std::string, std::ostream&) const;
  void doCommand(const std::string& cmd, dictOfDicts& ref, std::string str, std::string str2, std::string str3);
  void doCommand(const std::string& cmd, dictOfDicts& ref, std::ostream& out);

  using typeF = std::function< void(dictOfDicts& ref, std::string) >;
  using typeS = std::function< void(dictOfDicts& ref, std::string, std::ostream&) >;
  using typeT = std::function< void(dictOfDicts& ref, std::string, std::string, std::ostream&) >;
  using typeFo = std::function< void(dictOfDicts& ref, std::string, std::string, std::string) >;
  using typeFi = std::function< void(dictOfDicts& ref, std::ostream& out) >;

  std::map< std::string, typeF > cmdsOne;
  std::map< std::string, typeS > cmdsTwo;
  std::map< std::string, typeT > cmdsThree;
  std::map< std::string, typeFo > cmdsFour;
  std::map< std::string, typeFi > cmdsFive;
};

std::ostream& printInvCmd(std::ostream& out);
void skipUntilNewLine(std::istream& in);

#endif
