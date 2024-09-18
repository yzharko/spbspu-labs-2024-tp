#ifndef COMMANDS_HPP
#define COMMANDS_HPP

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
  void makeDecode(std::string & parameters, HuffmanCode & data);
  void makeClean(std::string & parameters, HuffmanCode & data);
  void makeDelete(std::string & parameters, HuffmanCode &);
  void makeSave(std::string & parameters, HuffmanCode & data);
}

#endif
