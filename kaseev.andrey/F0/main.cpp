#include <iostream>
#include <map>
#include <functional>
#include <fstream>
#include <vector>
#include "functions.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <vector file> <command history file>" << std::endl;
    return 1;
  }
  std::string vector_filename = argv[1];
  std::ofstream vector_file(vector_filename, std::ios::app);
  if (!vector_file.is_open()) {
    std::cerr << "Error: Could not open file " << vector_filename << " for writing." << std::endl;
    return 1;
  }
  std::string history_filename = argv[2];
  std::ofstream history_file(history_filename, std::ios::app);
  if (!history_file.is_open()) {
    std::cerr << "Error: Could not open file " << history_filename << " for writing." << std::endl;
    return 1;
  }
  std::vector<kaseev::par> data;
  std::map<std::string, std::function<void(std::vector<kaseev::par>&)>> m;
  m["HELP"] = [&](std::vector<kaseev::par>&) {
    kaseev::help();
    history_file << "HELP command executed\n";
  };
  m["MULTIPLY"] = [&](std::vector<kaseev::par>& data) {
    kaseev::multiply(data);
    history_file << "MULTIPLY command executed\n";
  };
  m["SUM"] = [&](std::vector<kaseev::par>& data) {
    kaseev::sum(data);
    history_file << "SUM command executed\n";
  };
  m["POP"] = [&](std::vector<kaseev::par>&) {
    std::string name;
    std::cout << "Enter name to pop: ";
    std::cin >> name;
    kaseev::pop(data, name);
    history_file << "POP command executed on " << name << "\n";
  };
  m["CHANGE"] = [&](std::vector<kaseev::par>&) {
    std::string old_name, new_name;
    std::cout << "Enter old name: ";
    std::cin >> old_name;
    std::cout << "Enter new name: ";
    std::cin >> new_name;
    kaseev::change(data, old_name, new_name);
    history_file << "CHANGE command executed: " << old_name << " -> " << new_name << "\n";
  };
  m["CLEAR"] = [&](std::vector<kaseev::par>& data) {
    kaseev::clear(data);
    history_file << "CLEAR command executed\n";
  };
  m["READFILE"] = [&](std::vector<kaseev::par>& data) {
    kaseev::readfile(data);
    history_file << "READFILE command executed\n";
  };
  m["INPUT"] = [&](std::vector<kaseev::par>& data) {
    kaseev::input(data);
    history_file << "INPUT command executed\n";
  };
  m["SAVE"] = [&](std::vector<kaseev::par>& data) {
    kaseev::save(data, vector_filename);
    history_file << "SAVE command executed to " << vector_filename << "\n";
  };
  std::string command;
  while (true) {
    std::cout << "Enter command: ";
    std::cin >> command;
    if (command == "EXIT") {
      history_file << "EXIT command executed\n";
      break;
    }
    if (auto it = m.find(command); it != m.end()) {
      it->second(data);
    } else {
      std::cout << "Unknown command!" << std::endl;
      history_file << "Unknown command entered: " << command << "\n";
    }
  }
  vector_file.close();
  history_file.close();

  return 0;
}
