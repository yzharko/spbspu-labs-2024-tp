#include "functions.hpp"
#include <iostream>

namespace kaseev {

  void help()
  {
    std::cout << "help - shows a list of commands\n"
                 "multiply - multiplies numbers by column\n"
                 "sum - sums numbers in a column\n"
                 "pop - Removes a line from the list by name\n"
                 "change - changes a line from a list by name\n"
                 "clear - deletes the entire list\n"
                 "readfile - displays the entire list on the screen\n"
                 "input - adds a row to the list\n"
                 "save - saves the list to a file\n"
                 "exit - stop program";
  }
}
