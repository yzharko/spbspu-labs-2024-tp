#ifndef WORDS_DICT_HPP
#define WORDS_DICT_HPP

#include <iosfwd>

#include <map>
#include <vector>
#include <string>

struct WordsDict
{
  std::vector<std::string> lines;
  std::map<std::string, std::vector<size_t>> dict;

  void addWord(std::string word, size_t line_idx);

  friend std::ostream& operator<<(std::ostream&, const WordsDict&);

private:
  size_t max_word_length_ = 0;
};

std::ostream& operator<<(std::ostream& out, const WordsDict& wd);

#endif
