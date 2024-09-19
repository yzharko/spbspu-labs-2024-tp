#ifndef STRUCT_INPUT_SEPARATOR
#define STRUCT_INPUT_SEPARATOR

#include <iostream>

namespace smolyakov
{
  struct StructInputSeparator
  {
    char separatorCharacter;
  };

  std::istream& operator >> (std::istream& inputStream, StructInputSeparator& separator);
}

#endif
