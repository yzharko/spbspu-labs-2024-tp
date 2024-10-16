#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>

#include "Graph.hpp"

void invalidCommandMessage();
bool convertToSize(const std::string& str, int& value);
bool process(const std::string& cmd_string, Graph& data);

#endif
