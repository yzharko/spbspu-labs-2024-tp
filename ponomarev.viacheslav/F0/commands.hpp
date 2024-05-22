#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>

namespace ponomarev
{
  void outputInfoAboutCommands(const std::string & parameters, HuffmanCode &);
  void makeInput(std::string & parameters, HuffmanCode & data);
  void makeEncode(std::string & parameters, HuffmanCode & data);
}

#endif
