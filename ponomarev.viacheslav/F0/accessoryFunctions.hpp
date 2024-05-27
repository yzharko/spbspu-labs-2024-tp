#ifndef ACCESSORY_FUNCTIONS_HPP
#define ACCESSORY_FUNCTIONS_HPP

#include <iostream>
#include "codingHuffman.hpp"

namespace ponomarev
{
  std::string cutType(std::string & line);

  bool isNum(const std::string & str);

  void getText(std::istream & input, HuffmanCode & data);
  void cutTextInFile(long long n, long long k, HuffmanCode & data, std::istream & input);
  void deleteFile(const std::string parameter);
  void deleteTextInFile(long long n, long long k, const std::string parameter);

  std::ostream & printInvalidCommandMessage(std::ostream & out);
  std::ostream & printWelcomeMessage(std::ostream & out);
  std::ostream & printInvalidEncodeMessage(std::ostream & out);
  std::ostream & printSuccessfullyEncodeMessage(std::ostream & out);
  std::ostream & printSuccessfullyInputMessage(std::ostream & out);
  std::ostream & printSuccessfullyWriteMessage(std::ostream & out);
  std::ostream & printSuccessfullyFrequenceInput(std::ostream & out);
}

#endif
