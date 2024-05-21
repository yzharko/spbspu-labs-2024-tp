#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <cstdlib>
#include "HuffmanTree.hpp"
#include "Command.hpp"

void HuffmanApp::showHelp() {
  std::cout << "Commands:\n"
    << "help - Show commands\n"
    << "input - Input text from keyboard\n"
    << "file <filename> - Input text from file\n"
    << "generic - Generate random string\n"
    << "encode - Encode text\n"
    << "data - Show encoded text\n"
    << "table <filename> - Save code table\n"
    << "stats - Show frequency table\n"
    << "print - Show encoded text\n"
    << "output <filename> - Save encoded text\n"
    << "merge <file1> <file2> - Merge two files\n";
}

void HuffmanApp::input()
{
  std::cout << "Enter text: ";
  std::getline(std::cin, text_);
}

void HuffmanApp::genRandom()
{
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  const size_t maxLength = 100;
  text_.clear();
  for (size_t i = 0; i < maxLength; ++i) {
    text_ += charset[rand() % (sizeof(charset) - 1)];
  }
  std::cout << "Generated string in 100 size: " << text_ << '\n';
}

void HuffmanApp::encode()
{
  if (text_.empty()) {
    std::cerr << "Error: No text to encode\n";
    return;
  }
  tree_.build(text_);
  encodedText_ = tree_.encode(text_);
}

void HuffmanApp::data()
{
  tree_.codeTable(std::cout);
}

void HuffmanApp::showEncoded()
{
  if (encodedText_.empty()) {
    std::cerr << "Error: No encoded data to display\n";
    return;
  }
  std::cout << "Encoded text: " << encodedText_ << '\n';
}

void HuffmanApp::showFreq()
{
  tree_.freqTable(std::cout);
}
