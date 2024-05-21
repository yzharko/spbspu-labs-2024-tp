#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "HuffmanTree.hpp"
#include <string>

class HuffmanApp {
public:
  HuffmanApp() = default;
  void showHelp();
  void input();
  void genRandom();
  void encode();
  void data();
  void showEncoded();
  void showFreq();
private:
  std::string text_;
  std::string encodedText_;
  HuffmanTree tree_;
};
#endif
