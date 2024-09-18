#include <iostream>
#include "DictionaryManager.h"
#include <iterator>
#include <time.h>
#include <ctime>
#include <sstream>
#include <locale.h>

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  DictionaryManager manager;
  std::string command;

  while (true) {
    std::cout << "> ";
    std::getline(std::cin, command);
    if (command == "exit") break;

    try {
      std::istringstream iss(command);
      std::vector<std::string> args((std::istream_iterator<std::string>(iss)),
                      std::istream_iterator<std::string>());
      if (args.empty()) continue;

      if (args[0] == "help") {
        manager.help();
      } else if (args[0] == "list") {
        manager.list();
      } else if (args[0] == "create" && args.size() == 2) {
        manager.create(args[1]);
      } else if (args[0] == "delete" && args.size() == 2) {
        manager.remove(args[1]);
      } else if (args[0] == "combine" && args.size() == 4) {
        manager.combine(args[1], args[2], args[3]);
      } else if (args[0] == "add" && args.size() == 3) {
        manager.add(args[1], args[2]);
      } else if (args[0] == "definition" && args.size() == 4) {
        manager.definition(args[1], args[2], args[3]);
      } else if (args[0] == "remove" && args.size() == 3) {
        manager.removeWord(args[1], args[2]);
      } else if (args[0] == "translate" && args.size() == 3) {
        manager.translate(args[1], args[2]);
      } else if (args[0] == "size" && args.size() == 2) {
        manager.size(args[1]);
      } else if (args[0] == "show" && args.size() == 2) {
        manager.show(args[1]);
      } else if (args[0] == "random" && args.size() == 2) {
        manager.random(args[1]);
      } else {
        std::cout << "Неверная команда\n";
      }
    } catch (const std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }
  }
}
