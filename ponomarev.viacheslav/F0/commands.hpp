#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include "codingHuffman.hpp"

namespace ponomarev
{
  void outputInfoAboutCommands(const std::string & parameters, HuffmanCode &);
  void makeInput(std::string & parameters, HuffmanCode & data);
  void chooseEncode(std::string & parameters, HuffmanCode & data);
}

#endif
