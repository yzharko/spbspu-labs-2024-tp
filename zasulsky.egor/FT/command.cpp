#include "command.hpp"
#include <map>
#include <sstream>

void add(dictOfDicts& ref, std::string name, std::string word, std::string value)
{
  auto it = ref.find(name);
  if (it != ref.end())
  {
    std::vector<std::string> vec;
    vec.push_back(value);
    it->second.insert(make_pair(word, vec));
  }
  else
  {
    throw std::logic_error("dictionary doesn't exist");
  }
}

void build(dictOfDicts& ref, std::string name, std::ostream& out)
{
  dict newDict;
  ref.insert(make_pair(name, newDict));
  out << "The dictionary has been successfully created, now you can start working with it\n";
}

void create(dictOfDicts& ref, std::string name)
{
  dict newDict;
  ref.insert(make_pair(name, newDict));
}

void translate(dictOfDicts& ref, std::string name, std::string word, std::ostream& out)
{
  auto it = ref.find(name);
  if (it != ref.end())
  {
    auto interIt = it->second.find(word);
    out << interIt->first;
    out << '-';
    out << interIt->second.back();
  }
}

void calculate(dictOfDicts& ref, std::string name, std::ostream& out)
{
  auto it = ref.find(name);
  if (it != ref.end())
  {
    out << it->second.size() << '\n';
  }
  else
  {
    throw std::logic_error("dictionary doesn't exist");
  }
}

void count(dictOfDicts& ref, std::ostream& out)
{
  out << ref.size() << '\n';
}

void translation(dictOfDicts& ref, std::string name, std::string word, std::string translation)
{
  auto it = ref.find(name);
  if (it != ref.end())
  {
    auto interIt = it->second.find(word);
    interIt->second.push_back(translation);
  }
  else
  {
    throw std::logic_error("dictionary doesn't exist");
  }
}

void search(dictOfDicts& ref, std::string name, std::string substr, std::ostream& out)
{
  auto it = ref.find(name);
  if (it != ref.end())
  {
    for (auto p : it->second)
    {
      if (p.first.find(substr) != std::string::npos)
      {
        out << p.first << '-';
        for (auto it = p.second.begin(); it != p.second.end(); ++it)
        {
          out << *it;
          if (it != std::prev(p.second.end()))
          {
            out << ',';
          }
          else
          {
            out << '\n';
          }
        }
      }
    }
  }
  else
  {
    throw std::logic_error("dictionary doesn't exist");
  }
}

void print(dictOfDicts& ref, std::string name, std::ostream& out)
{
  auto it = ref.find(name);
  if (it != ref.end())
  {
    for (auto p : it->second)
    {
      out << p.first << '-';
      for (auto it = p.second.begin(); it != p.second.end(); ++it)
      {
        out << *it;
        if (it != std::prev(p.second.end()))
        {
          out << ',';
        }
        else
        {
          out << '\n';
        }
      }
    }
  }
  else
  {
    throw std::logic_error("dictionary doesn't exist");
  }
}

void help(dictOfDicts& ref, std::ostream& out)
{
  if (ref.empty())
  {
    out << "no dictionary has been created yet\n";
    out << "to create a new dictionary use the command \"BUILD\"\n";
  }
  out << "TRANSLATE:   output of the first word of a given word\n";
  out << "CALCULATE:   displaying the number of words in a given dictionary\n";
  out << "COUNT:       displaying the number of dictionaries in the program\n";
  out << "TRANSLATION: adding a new translation for a given word\n";
  out << "SEARCH:      output words containing a given substring in a given dictionary\n";
  out << "ADD:         adding a word with a leading word to a given dictionary\n";
  out << "BUILD:       creating a new dictionary with a given name\n";
  out << "PRINT:       output dictionary contents\n";
  out << "COMBINATION: creating a dictionary with a given name containing the data of the transferred dictionaries\n";
  out << "CROSS:       creating a dictionary with a given name containing the intersection of the passed dictionaries\n";
  out << "HELP:        output description of command functionality\n";
  out << "TAG:         adding a list of words with their translations to the dictionary\n";
}

Parser::Parser(std::string toparse) :
  parsable_(toparse),
  current_(toparse.find_first_not_of(" "))
{}

std::string Parser::operator ()()
{
  if (current_ > parsable_.length())
  {
    return "";
  }
  size_t start = current_;
  size_t end = 0;
  auto che = parsable_.substr(current_).find_first_of(" ");
  if (che == std::string::npos)
  {
    end = parsable_.length();
  }
  else
  {
    end = current_ + parsable_.substr(current_).find_first_of(" ");
  }
  current_ = 1 + end;
  return parsable_.substr(start, end - start);
}


void intersect(dictOfDicts& ref, std::string str)
{
  std::vector<std::string> vec;
  Parser pars(str);
  for (auto i = pars(); !i.empty(); i = pars())
  {
    vec.push_back(i);
  }
  if (vec.size() < 3)
  {
    throw std::invalid_argument("not enough arg");
  }
  std::string name = vec.front();
  auto it = ref.find(vec.front());
  vec.erase(vec.begin());
  auto it2 = ref.find(vec.front());
  vec.erase(vec.begin());
  if (it2 == ref.end())
  {
    throw std::invalid_argument("dictionary is empty");
  }
  std::map<std::string, std::vector< std::string > > res;
  std::map<std::string, std::vector< std::string > > result;
  if (it != ref.end())
  {
    it->second.clear();
    if (it2 != ref.end())
    {
      it->second = it2->second;
    }
    else
    {
      throw std::logic_error("dictionary is empty");
    }
  }
  res = it2->second;
  for (int i = 0; i < vec.size(); i++)
  {
    auto it3 = ref.find(vec[i]);
    if (it3 != ref.end())
    {
      for (const auto& el : res)
      {
        auto it4 = it3->second.find(el.first);
        if (it4 != it3->second.end())
        {
          result.insert(el);
        }
      }
    }
    else
    {
      throw std::logic_error("dictionary is empty");
    }
  }
  if (it != ref.end())
  {
    it->second = result;
  }
  else
  {
    create(ref, name);
    auto resIt = ref.find(name);
    resIt->second = result;
  }
}

void combination(dictOfDicts& ref, std::string str)
{
  std::vector<std::string> vec;
  Parser pars(str);
  for (auto i = pars(); !i.empty(); i = pars())
  {
    vec.push_back(i);
  }
  std::string name = vec.front();
  auto it = ref.find(vec.front());
  vec.erase(vec.begin());
  auto it2 = ref.find(vec.front());
  vec.erase(vec.begin());
  if (it2 == ref.end())
  {
    throw std::invalid_argument("dictionary is empty");
  }
  std::map<std::string, std::vector< std::string > > res;
  std::map<std::string, std::vector< std::string > > result;
  if (it != ref.end())
  {
    it->second.clear();
    if (it2 != ref.end())
    {
      it->second = it2->second;
    }
    else
    {
      throw std::logic_error("dictionary is empty");
    }
  }
  res = it2->second;
  for (int i = 0; i < vec.size(); i++)
  {
    auto it3 = ref.find(vec[i]);
    if (it3 != ref.end())
    {
      for (const auto& el : res)
      {
        result.insert(el);
      }
      for (const auto& el : it3->second)
      {
        auto it4 = res.find(el.first);
        if (it4 == res.end())
        {
          result.insert(el);
        }
      }
    }
    else
    {
      throw std::logic_error("dictionary is empty");
    }
  }
  if (it != ref.end())
  {
    it->second = result;
  }
  else
  {
    create(ref, name);
    auto resIt = ref.find(name);
    resIt->second = result;
  }
}

void tag(dictOfDicts& ref, std::string str)
{
  size_t fPos = str.find_first_of(" ");
  size_t pos = str.find(" ", fPos + 1);
  std::string fName = str.substr(0, pos);
  std::string name = fName.substr(1);
  std::string words = str.substr(pos + 1);
  auto it = ref.find(name);
  if (it == ref.end())
  {
    throw std::logic_error("dictionary is empty");
  }
  std::stringstream ss(words);
  std::string pair;
  while (std::getline(ss, pair, ';'))
  {
    std::stringstream ss_pair(pair);
    std::string word;
    std::string translation;
    std::getline(ss_pair, word, '-');
    std::getline(ss_pair, translation, '-');
    it->second[word].push_back(translation);
  }
}