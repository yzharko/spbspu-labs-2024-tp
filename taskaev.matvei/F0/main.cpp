#include <iostream>
#include <functional>
#include <string>
#include <map>
#include "command.hpp"

int main()
{
  taskaev::HuffmanApp app;
  std::cout << "hello in Huffman code, please work:\n";
  std::map< std::string, std::function< void() > > cmds;
  cmds["help"] = std::bind(&taskaev::HuffmanApp::showHelp, &app);
  cmds["input"] = std::bind(&taskaev::HuffmanApp::input, &app);
  cmds["generic"] = std::bind(&taskaev::HuffmanApp::genRandom, &app);
  cmds["encode"] = std::bind(&taskaev::HuffmanApp::encode, &app);
  cmds["data"] = std::bind(&taskaev::HuffmanApp::data, &app);
  cmds["stats"] = std::bind(&taskaev::HuffmanApp::showFreq, &app);
  cmds["print"] = std::bind(&taskaev::HuffmanApp::showEncoded, &app);
  cmds["file"] = std::bind(&taskaev::HuffmanApp::file, &app);
  cmds["output"] = std::bind(&taskaev::HuffmanApp::saveEncoded, &app);
  cmds["table"] = std::bind(&taskaev::HuffmanApp::saveCodeTable, &app);
  cmds["merge"] = std::bind(&taskaev::HuffmanApp::mergeFiles, &app);
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
