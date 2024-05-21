#include <iostream>
#include <functional>
#include <map>
#include <string>
#include "Command.h"

int main() 
{
  HuffmanApp app;
  std::cout << "hello in Huffman code, please work:\n";
  std::map< std::string, std::function< void() > > cmds;
  cmds["help"] = std::bind(&HuffmanApp::showHelp, &app);
  cmds["input"] = std::bind(&HuffmanApp::input, &app);
  cmds["generic"] = std::bind(&HuffmanApp::genRandom, &app);
  cmds["encode"] = std::bind(&HuffmanApp::encode, &app);
  cmds["data"] = std::bind(&HuffmanApp::data, &app);
  cmds["stats"] = std::bind(&HuffmanApp::showFreq, &app);
  cmds["print"] = std::bind(&HuffmanApp::showEncoded, &app);
  std::string command;
  while (true) {
    std::cout << "> ";

    if (!(std::cin >> command))
    {
      break;
    }
    std::cin.ignore();
    if (cmds.find(command) != cmds.end())
    {
      cmds[command]();
    }
    else
    {
      std::cerr << "Invalid command. Type 'help' for a list of commands.\n";
    }
  }
  std::cout << "Good bue!\n";
  return 0;
}
