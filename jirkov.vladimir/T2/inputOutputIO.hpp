#ifndef INPUT_OUTPUT_IO_HPP
#define INPUT_OUTPUT_IO_HPP
#ifndef INPUT_OUTPUT_IO_HPP
#define INPUT_OUTPUT_IO_HPP
#include <string>
#include <utility>
#include <iostream>
#include "ScopeGuard.hpp"
#include "IOstructures.hpp"
namespace jirkov
{
  std::istream & operator>>(std::istream &in, DataStruct &value);
  std::ostream & operator<<(std::ostream & out, const DataStruct &value);
}

#endif
