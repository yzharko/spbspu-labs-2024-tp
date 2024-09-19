#include "commands.hpp"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <limits>

std::ostream & panov::help(std::istream & in, std::ostream & out)
{
  in.clear();
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  return out << "help - prints out all commands\n"
    << "create <name> - create dictionary\n"
    << "add <word, name> - add word to dictionary\n"
    << "change <name> <key> <translation> - change translation\n"
    << "delete <word> <name> - delete word from dictionary\n"
    << "reset <name> - clear dictionary\n"
    << "print <name> - print dictionary contents\n"
    << "add <line> <word> - add line number to word\n"
    << "get <print> <name> <line> - get words from line\n"
    << "intersection <new_name> <name> - create new dictionary new_name from name\n"
    << "search <letter> <name> - search words by first letter\n";
}

std::ostream & panov::create(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  std::string name;
  in >> name;
  if (dicts.find(name) != dicts.end())
  {
    out << "Dict exists\n";
    throw std::logic_error("");
  }
  dict_t dict;
  dicts[name] = dict;
  return out;
}

std::ostream & panov::add(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  std::string word;
  in >> word;
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  auto it = std::find_if(
    dicts.at(name).begin(),
    dicts.at(name).end(),
    [& word](const word_t & entry)
    {
      return entry.first == word;
    }
  );
  if (it != dicts.at(name).end())
  {
    out << "Word already exists in the dictionary\n";
    throw std::logic_error("");
  }
  dicts.at(name).emplace_back(word, "");
  return out;
}

std::ostream & panov::deleteWord(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  std::string word;
  in >> word;
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  auto it = std::remove_if(
    dicts.at(name).begin(),
    dicts.at(name).end(),
    [& word](const word_t & entry)
    {
      return entry.first == word;
    }
  );
  if (it == dicts.at(name).end())
  {
    out << "Word not found in the dictionary\n";
    throw std::logic_error("");
  }
  dicts.at(name).erase(it, dicts.at(name).end());
  return out;
}

std::ostream & panov::change(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  std::string word;
  in >> word;
  std::string name;
  in >> name;
  std::string translation;
  in >> translation;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  auto it = std::find_if(
    dicts.at(name).begin(),
    dicts.at(name).end(),
    [& word](const word_t & entry)
    {
      return entry.first == word;
    }
  );
  if (it == dicts.at(name).end())
  {
    out << "Word not found in the dictionary\n";
    throw std::logic_error("");
  }
  it->second = translation;
  return out;
}

std::ostream & panov::reset(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  dicts.at(name).clear();
  return out;
}

std::ostream & panov::print(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("Dictionary not found");
  }
  dict_t sorted = dicts.at(name);
  std::sort(
    sorted.begin(),
    sorted.end(),
    [](const word_t & a, const word_t & b)
    {
      return a.first < b.first;
    }
  );
  std::transform(
    sorted.begin(),
    sorted.end(),
    std::ostream_iterator< std::string >(out, "\n"),
    [](const word_t & entry)
    {
      return entry.first + " : " + entry.second;
    }
  );
  return out;
}

std::ostream & panov::intersection(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  std::string newName;
  in >> newName;
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  if (dicts.find(newName) != dicts.end())
  {
    out << "Dictionary with this name already exists\n";
    throw std::logic_error("Dictionary already exists");
  }
  dicts[newName] = dicts.at(name);
  return out;
}

std::ostream & panov::search(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  char letter;
  in >> letter;
  std::string name;
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  dict_t filteredWords;
  std::copy_if(
    dicts.at(name).begin(),
    dicts.at(name).end(),
    std::back_inserter(filteredWords),
    [letter](const word_t & entry)
    {
      return !entry.first.empty() && entry.first[0] == letter;
    }
  );
  std::transform(
    filteredWords.begin(),
    filteredWords.end(),
    std::ostream_iterator<std::string>(out, "\n"),
    [](const word_t & entry)
    {
      return entry.first + " : " + entry.second;
    }
  );
  return out;
}

std::ostream & panov::get(dicts_t & dicts, std::istream & in, std::ostream & out)
{
  std::string name;
  in >> name;
  in.ignore();
  std::string line;
  std::getline(in, line);
  if (dicts.find(name) == dicts.end())
  {
    out << "Dict doesn't exist\n";
    throw std::logic_error("");
  }
  dict_t currentDict = dicts.at(name);
  out << name << '\n';
  out << line << '\n';
  dict_t filteredWords;
  std::copy_if(
    currentDict.cbegin(),
    currentDict.cend(),
    std::back_inserter(filteredWords),
    [line](const word_t & entry)
    {
      return line.find(entry.first) != std::string::npos;
    }
  );
  std::transform(
    filteredWords.begin(),
    filteredWords.end(),
    std::ostream_iterator<std::string>(out, "\n"),
    [](const word_t & entry)
    {
      return entry.first + " : " + entry.second;
    }
  );
  return out;
}

void splitWords(const std::string & str, std::vector< std::string > & words, size_t pos = 0)
{
  size_t nextSpace = str.find(' ', pos);
  if (nextSpace == std::string::npos)
  {
    words.push_back(str.substr(pos));
  }
  else
  {
    words.push_back(str.substr(pos, nextSpace - pos));
    splitWords(str, words, nextSpace + 1);
  }
}

std::ostream & panov::addline(std::istream & in, std::ostream & out)
{
  std::string word;
  in >> word;
  in.ignore();
  std::string line;
  std::getline(in, line);
  std::vector< std::string > words;
  splitWords(line, words);
  std::vector<int> indices;
  std::transform(
    words.begin(),
    words.end(),
    std::back_inserter(indices),
    [&](const std::string & w)
    {
      return (w == word) ? &w - &words[0] : -1;
    }
  );
  indices.erase(std::remove(indices.begin(), indices.end(), -1), indices.end());
  std::copy(indices.begin(), indices.end(), std::ostream_iterator<int>(out, " "));
  out << '\n';
  return out;
}
