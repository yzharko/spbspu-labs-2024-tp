#include "WordsDict.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>

#include "ScopeGuard.hpp"

void WordsDict::addWord(std::string word, size_t line_idx)
{
  std::transform(word.begin(),
      word.end(),
      word.begin(),
      [](auto c)
      {
        return std::tolower(c);
      });
  dict[word].push_back(line_idx);

  max_word_length_ = std::max(max_word_length_, word.length());
}

std::ostream& operator<<(std::ostream& out, const WordsDict& wd)
{
  constexpr size_t title_length = 6;

  lisitsyna::iofmtguard sg{ out };

  out << std::setfill(' ') << std::setw(std::max(wd.max_word_length_, title_length)) << std::left << " Word ";
  out << "| Lines\n";
  out << std::setfill('-') << std::setw(std::max(wd.max_word_length_, title_length) + 10) << std::left << "-";
  out << '\n';

  for (auto&& v : wd.dict)
  {
    out << std::setfill(' ') << std::setw(std::max(wd.max_word_length_, title_length)) << std::left << v.first;
    out << " | ";
    for (auto&& l : v.second)
    {
      out << l << ' ';
    }
    out << '\n';
  }

  return out;
}
