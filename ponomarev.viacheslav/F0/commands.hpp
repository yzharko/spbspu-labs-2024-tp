#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include "codingHuffman.hpp"

namespace ponomarev
{
  void outputInfoAboutCommands(const std::string & parameters, HuffmanCode &);
  void makeInput(std::string & parameters, HuffmanCode & data);
  void chooseEncode(std::string & parameters, HuffmanCode & data);
  void writeTextIntoFile(std::string & parameters, HuffmanCode & data);
  void setDecode(std::string & parameters, HuffmanCode & data);
  void combineFiles(std::string & parameters, HuffmanCode &);
  void showTable(std::string & parameters, HuffmanCode & data);
}

#endif
