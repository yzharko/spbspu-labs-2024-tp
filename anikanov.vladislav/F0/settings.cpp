#include "settings.hpp"

#include <iostream>

anikanov::Settings::Settings()
{
  inputMatrix = true;
  outputMatrix = true;
  saveOutput = false;
}

std::ostream &anikanov::operator<<(std::ostream &out, const anikanov::Settings &settings)
{
  out << "Settings:\n";
  out << "Input matrix: " << (settings.inputMatrix ? "matrix" : "graph") << "\n";
  out << "Output matrix: " << (settings.outputMatrix ? "matrix" : "graph") << "\n";
  out << "Save output: " << (settings.saveOutput ? "Yes" : "No") << "\n";
  return out;
}
