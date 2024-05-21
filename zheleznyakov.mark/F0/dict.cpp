#include "dict.hpp"

size_t zheleznyakov::getWordsCount(std::string s)
{
  size_t count = 0;
  bool inWord = false;
  for (char c : s)
  {
    if (std::isalpha(c))
    {
      if (!inWord)
      {
        count++;
        inWord = true;
      }
    }
    else
    {
      inWord = false;
    }
  }
  return count;
}

zheleznyakov::wordpairs_t zheleznyakov::getDict(const std::string & str)
{
  wordpairs_t wordMap;
  std::string word = "";
  size_t line = 1;
  size_t position = 1;

  for (char c : str)
  {
    if (c == '\n')
    {
      line++;
      position = 1;
      continue;
    }

    if (c == ' ')
    {
      if (!word.empty())
      {
        wordMap[word].push_back(std::make_pair(line, position));
        word.clear();
      }
      position++;
    }
    else
    {
      word += c;
    }
  }

  if (!word.empty())
  {
    wordMap[word].push_back(std::make_pair(line, position));
  }

  return wordMap;
}
