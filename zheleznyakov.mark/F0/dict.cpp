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

zheleznyakov::wordpairs_t zheleznyakov::getDict(const std::string & str) {
  zheleznyakov::wordpairs_t wordMap;
  std::string word = "";
  for (char c : str) {
    if (c == '\n')
    {
      continue;
    }
    if (c == ' ')
    {
      if (!word.empty()) {
        wordMap[word]++;
        word.clear();
      }
    } else {
      word += c;
    }
  }
  if (!word.empty()) {
      wordMap[word]++;
  }
  return wordMap;
}
