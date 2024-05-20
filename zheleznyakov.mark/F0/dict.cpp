#include "dict.hpp"

size_t zheleznyakov::getWordsCount(std::string s)
{
  size_t count = 0;
  bool inWord = false;
  for (char c : s) {
    if (std::isalpha(c)) {
      if (!inWord) {
        count++;
        inWord = true;
      }
    } else {
      inWord = false;
    }
  }
  return count;
}
