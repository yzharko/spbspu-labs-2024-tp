#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <cstdlib>
#include "HuffmanTree.hpp"
#include "command.hpp"

void taskaev::HuffmanApp::showHelp() {
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

void taskaev::HuffmanApp::input()
{
  std::cout << "Enter text: ";
  std::getline(std::cin, text_);
}

void taskaev::HuffmanApp::file()
{
  std::string filename;
  std::cin >> filename;
  std::cin.ignore();
  std::ifstream inFile(filename);
  if (!inFile)
  {
    std::cerr << "Error: Cannot open file" << filename << "\n";
    return;
  }
  text_.assign((std::istreambuf_iterator< char > (inFile)), std::istreambuf_iterator< char >());
}

void taskaev::HuffmanApp::genRandom()
{
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  const size_t maxLength = 100;
  text_.clear();
  for (size_t i = 0; i < maxLength; ++i) {
    text_ += charset[rand() % (sizeof(charset) - 1)];
  }
  std::cout << "Generated string in 100 size: " << text_ << '\n';
}

void taskaev::HuffmanApp::encode()
{
  if (text_.empty()) {
    std::cerr << "Error: No text to encode\n";
    return;
  }
  tree_.build(text_);
  encodedText_ = tree_.encode(text_);
}

void taskaev::HuffmanApp::data()
{
  tree_.codeTable(std::cout);
}

void taskaev::HuffmanApp::showEncoded()
{
  if (encodedText_.empty()) {
    std::cerr << "Error: No encoded data to display\n";
    return;
  }
  std::cout << "Encoded text: " << encodedText_ << '\n';
}

void taskaev::HuffmanApp::saveEncoded()
{
  std::string filename;
  std::cin >> filename;
  std::cin.ignore();
  std::ofstream outFile(filename);
  if (!outFile)
  {
    std::cerr << "Error: Cannot open file " << filename << "\n";
    return;
  }
  outFile << encodedText_;
}

void taskaev::HuffmanApp::saveCodeTable()
{
  std::string filename;
  std::cin >> filename;
  std::cin.ignore();
  std::ofstream outFile(filename);
  if (!outFile)
  {
    std::cerr << "Error: Cannot open file " << filename << "\n";
    return;
  }
  tree_.codeTable(outFile);
}

void taskaev::HuffmanApp::showFreq()
{
  tree_.freqTable(std::cout);
}

void taskaev::HuffmanApp::mergeFiles()
{
  std::string filenameOne, filenameTwo;
  std::cin >> filenameOne >> filenameTwo;
  std::cin.ignore();
  std::ifstream fileOne(filenameOne);
  std::ifstream fileTwo(filenameTwo);
  if (!fileOne || !fileTwo)
  {
    std::cerr << "Error: Cannot open one of the files " << filenameOne << " or " << filenameTwo << "\n";
    return;
  }
  std::string mergeFilename = "merge_" + filenameOne + "_" + filenameTwo;
  std::ofstream outFile(mergeFilename);
  if (!outFile)
  {
    std::cerr << "Error: Cannot create file " << mergeFilename << "\n";
    return;
  }
  outFile << fileOne.rdbuf() << fileTwo.rdbuf();
}
