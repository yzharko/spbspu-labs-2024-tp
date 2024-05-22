#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "HuffmanTree.hpp"
#include <string>

namespace taskaev
{
  class HuffmanApp
  {
  public:
    HuffmanApp() = default;
    void showHelp();
    void input();
    void file()
    void genRandom();
    void encode();
    void data();
    void showEncoded();
    void saveEncoded()
    void saveCodeTable()
    void showFreq();
    void mergeFiles()
  private:
    std::string text_;
    std::string encodedText_;
    HuffmanTree tree_;
  };
}
#endif
