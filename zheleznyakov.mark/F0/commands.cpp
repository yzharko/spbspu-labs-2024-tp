#include "commands.hpp"
#include <iostream>
#include <iterator>
#include <fstream>
#include <limits>

std::string zheleznyakov::statusString(std::string msg, std::string status)
{
  return "[" + status + "] " + msg;
}

std::string zheleznyakov::prompt(std::string active)
{
  return active == "" ? "menu> " : "(" + active + ")> ";
}

std::ostream & zheleznyakov::commands::help(std::istream & in, std::ostream & out)
{
  if (in.peek() != '\n')
  {
    throw std::logic_error(statusString("No additional args allowed\n", "warn"));
  }

  return out << "F0 - Cross-references\n"
  << "\n"
  << "Available menu commands:\n"
  << "  help                        List available commands\n"
  << "  list                        List saved strings\n"
  << "  create < title >            Create an empty string\n"
  << "  rm < title >                Remove the string\n"
  << "  cmp < title1 > < title2 >   Compare two strings, and list simular words\n"
  << "  diff < title1 > < title2 >  Compare two strings, and list different words\n"
  << "  enter < title >             Switch to the 'string' mode\n"
  << "\n"
  << "Available string commands:\n"
  << "  read (-f < filename >)      Reads string from stdin or a file\n"
  << "  table (-f < filename >)     Writes a word table to an stdout or a file\n"
  << "  info < word >               Prints an info for a word: count in the present string and its coordinates\n"
  << "  stats                       Print an overall string stats: total words count and an unique words count\n"
  << "  quit                        Quit from a 'string' mode\n";
}

std::ostream & zheleznyakov::commands::list(strings_t & strings, std::istream & in, std::ostream & out)
{
  if (in.peek() != '\n')
  {
    throw std::logic_error(statusString("No additional args allowed\n", "warn"));
  }

  out << "Total: " << strings.size() << "\n";
  if (!strings.empty())
  {
    out << "\nNames:\n";
    std::transform(
      strings.begin(),
      strings.end(),
      std::ostream_iterator<std::string>(out, "\n"),
      extractKeyFromString
    );
  }
  return out;
}

std::ostream & zheleznyakov::commands::rm(strings_t & strings, std::istream & in, std::ostream & out)
{
  std::string keyToDelete = "";
  in >> keyToDelete;
  if (strings.find(keyToDelete) == strings.end())
  {
    throw std::logic_error(statusString("Key not found\n", "warn"));
  }
  strings.erase(keyToDelete);
  return out;
}

std::ostream & zheleznyakov::commands::create(strings_t & strings, std::istream & in, std::ostream & out)
{
  std::string keyToCreate = "";
  in >> keyToCreate;
  if (strings.find(keyToCreate) != strings.end())
  {
    throw std::logic_error(statusString("Key is already in the list\n", "warn"));
  }
  string_t data;
  strings.insert(std::make_pair(keyToCreate, data));
  return out;
}

std::ostream & zheleznyakov::commands::cmp(strings_t & strings, std::istream & in, std::ostream & out)
{
  std::string l1 = "";
  in >> l1;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  if (strings.find(l1) == strings.end())
  {
    throw std::logic_error(statusString("Key 1 is not found\n", "error"));
  }
  std::string l2 = "";
  in >> l2;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  if (strings.find(l2) == strings.end())
  {
    throw std::logic_error(statusString("Key 2 is not found\n", "error"));
  }
  wordpairs_t s1 = strings.at(l1).second;
  wordpairs_t s2 = strings.at(l2).second;
  std::vector < std::string > matches;
  for (auto i = s1.begin(); i != s1.end(); i++)
  {
    if (s2.find(i->first) != s2.end())
    {
      out << i->first << '\n';
    }
  }
  return out;
}

std::ostream & zheleznyakov::commands::diff(strings_t & strings, std::istream & in, std::ostream & out)
{
  std::string l1 = "";
  in >> l1;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  if (strings.find(l1) == strings.end())
  {
    throw std::logic_error(statusString("Key 1 is not found\n", "error"));
  }
  std::string l2 = "";
  in >> l2;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  if (strings.find(l2) == strings.end())
  {
    throw std::logic_error(statusString("Key 2 is not found\n", "error"));
  }
  wordpairs_t s1 = strings.at(l1).second;
  wordpairs_t s2 = strings.at(l2).second;
  std::vector < std::string > matches;
  out << "Only in '" << l1 << "':\n";
  for (auto i = s1.begin(); i != s1.end(); i++)
  {
    if (s2.find(i->first) == s2.end())
    {
      out << i->first << '\n';
    }
  }
  out << "\nOnly in '" << l2 << "':\n";
  for (auto i = s2.begin(); i != s2.end(); i++)
  {
    if (s1.find(i->first) == s1.end())
    {
      out << i->first << '\n';
    }
  }
  return out;
}

std::ostream & zheleznyakov::commands::enter(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  if (active != "")
  {
    throw std::logic_error(statusString("Already in string mode\n", "error"));
  }
  std::string toEnter = "";
  in >> toEnter;
  if (strings.find(toEnter) == strings.end())
  {
    throw std::logic_error(statusString("Key is not in the list\n", "error"));
  }
  active = toEnter;
  return out;
}

std::ostream & zheleznyakov::commands::read(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  if (active == "")
  {
    throw std::logic_error(statusString("Not in string mode\n", "error"));
  }
  if (in.peek() != '\n')
  {
    std::string flag = "";
    in >> flag;
    if (flag != "-f")
    {
      throw std::logic_error(statusString("No known flag is passed\n", "error"));
    }
    std::string filename = "";
    in >> filename;
    std::ifstream fin(filename);
    if (!fin)
    {
      throw std::logic_error(statusString("Unable to read the file\n", "error"));
    }
    std::string contents((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    wordpairs_t pairs = getDict(contents);
    string_t currentStruct{ contents, pairs };
    strings[active] = currentStruct;
  }
  else
  {
    std::string contents;
    std::string line;
    while (std::getline(std::cin, line)) {
      if (line == "end")
      {
        break;
      }
      contents += line + '\n';
    }
    wordpairs_t pairs = getDict(contents);
    string_t currentStruct{ contents, pairs };
    strings[active] = currentStruct;
  }
  return out;
}

std::ostream & zheleznyakov::commands::table(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  if (active == "")
  {
    throw std::logic_error(statusString("Not in string mode\n", "error"));
  }
  if (in.peek() != '\n')
  {
    std::string flag = "";
    in >> flag;
    if (flag != "-f")
    {
      throw std::logic_error(statusString("No known flag is passed\n", "error"));
    }
    std::string filename = "";
    in >> filename;
    std::ofstream fout(filename);
    const wordpairs_t pairs = strings.at(active).second;
    for (auto i = pairs.begin(); i != pairs.end(); i++)
    {
      fout << i->first << ':' << i->second.size() << '\n';
    }
  }
  else
  {
    const wordpairs_t pairs = strings.at(active).second;
    for (auto i = pairs.begin(); i != pairs.end(); i++)
    {
      out << i->first << ':' << i->second.size() << '\n';
    }
  }
  return out;
}

std::ostream & zheleznyakov::commands::info(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  std::string word = "";
  in >> word;
  auto currentString = strings.at(active);
  if (currentString.second.find(word) == currentString.second.end())
  {
    throw std::logic_error(statusString("Word is not found\n", "error"));
  }
  auto currentWord = currentString.second[word];
  out << word << '\n'
  << "Repeats: " << currentWord.size() << '\n'
  << "Coords:\n";
  for (auto i = currentWord.begin(); i != currentWord.end(); i++)
  {
    out << i->first << ';' << i->second << '\n';
  }
  return out;
}

std::ostream & zheleznyakov::commands::stats(strings_t & strings, std::string & active, std::istream & in, std::ostream & out)
{
  if (in.peek() != '\n')
  {
    throw std::logic_error(statusString("No additional args allowed\n", "warn"));
  }
  string_t currentString = strings.at(active);
  out << "Total words in dict: " << currentString.second.size() << '\n'
  << "Total chars: " << currentString.first.size() << "\n";
  return out;
}

std::ostream & zheleznyakov::commands::quit(std::string & active, std::istream & in, std::ostream & out)
{
  if (in.peek() != '\n')
  {
    throw std::logic_error(statusString("No additional args allowed\n", "warn"));
  }
  if (active == "")
  {
    throw std::logic_error(statusString("Already in menu\n", "error"));
  }
  active = "";
  return out;
}

const std::string& zheleznyakov::extractKeyFromString(const std::pair< std::string, string_t >& pair) {
  return pair.first;
}
