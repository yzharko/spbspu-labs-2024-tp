#include "commands.hpp"
#include <fstream>

void litsinger::printCommands(std::ostream& out)
{
  out << " 1. help - ������� ��� ��������� �������\n";
  out << " 2. create - �������� ������� � ������ name\n";
  out << " 3. add_word <word, name> - ���������� ����� � ������� � ������ name\n";
  out << " 4. delete_word <word, name> - �������� ����� �� ������� � ������ name\n";
  out << " 5. reset - ������� ���� ������� name ���������\n";
  out << " 6. print - ����� ����� ������� name � ���������� �������\n";
  out << " 7. add_line <word, name, line> - � ������, ���� ����� ��� ���� � "
      "������� c ��������� name, "
 "�������� ������ �����, � ������� ��� ����� ������������, ���� ��� �� ����� ���������� "
      "�������� ��������\n";
  out << " 8. get_print <name, line> - ����� ���� ���� �� ������� name, "
      "������������ �� ������ line\n";
  out << " 9. get_intersection <new_name, name> - �������� ������� new_name ��"
      "������� �� ������� name\n";
  out << " 10. search_letter <letter, name> ����� ����, ������� ���������� "
      "�� ����� letter � ������� name\n";
}

void litsinger::creatDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  std::map< std::string, std::vector< size_t > > dictionary;
  mapDictionaries.emplace(name, dictionary);
  out << "������� ��������" << "\n";
}

void litsinger::addWord(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";

  in >> word >> name;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    auto wordInDict = dictIter->second.find(word);
    if (wordInDict == dictIter->second.end())
    {
      dictIter->second.emplace(word, 0);
      out << " ����� '" << word << "' ������� ��������� � ������� '" << name << "'\n";
    }
    else
    {
      out << " ����� '" << word << "' ��� ���������� � ������� '" << name << "'\n";
    }
  }
  else
  {
    out << " ������� � ��������� '" << name << "' �� ����������" << "\n";
  }
}

void litsinger::deleteWord(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";

  in >> word >> name;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    if (dictIter->second.erase(word))
    {
      out << " ����� '" << word << "' ������� �������" << "\n";
    }
    else
    {
      out << " ����� '" << word << "' �� ����������" << "\n";
    }
  }
  else
  {
    out << " ������� � ��������� '" << name << "' �� ����������" << "\n";
  }
}

void litsinger::resetDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";

  in >> name;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    dictIter->second.clear();
    out << " ������� '" << name << "' ������� ������" << "\n";
  }
  else
  {
    out << " ������� � ��������� '" << name << "' �� ������" << "\n";
  }
}

void litsinger::printDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";

  in >> name;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    size_t count = 0;
    bool firstLine = false;
    for (auto it = dictIter->second.begin(); it != dictIter->second.end(); ++it) {
      out << ++count << ". " << it->first << " {";
      for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
      {
        if (firstLine)
        {
          out << ",";
        }
        else
        {
          firstLine = true;
        }
        out << *iter;
      }
      firstLine = false;
      out << "}\n";
    }
  }
  else
  {
    out << " ������� � ��������� '" << name << "' �� ������" << "\n";
  }
}

void litsinger::addLine(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";
  std::size_t line = 0;

  in >> word >> name >> line;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    auto wordInDict = dictIter->second.find(word);
    if (wordInDict != dictIter->second.end())
    {
      auto it = wordInDict->second.begin();
      for (it = wordInDict->second.begin(); it != wordInDict->second.end(); ++it)
      {
        if (*it == line)
        {
          break;
        }
      }
      if (it == wordInDict->second.end())
      {
        wordInDict->second.push_back(line);
        out << " ����� ������ ������� �������� � ����� '" << word << "'\n";
      }
      else
      {
        out << " ������ ����� ������ ��� ���������� � ����� '" << word << "'\n";
      }
    }
    else
    {
      out << " ����� '" << word << "' �� ���������� � ������� '" << name << "'\n";
    }
  }
  else
  {
    out << " ������� � ��������� '" << name << "' �� ����������" << "\n";
  }
}

void litsinger::getPrint(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";
  std::size_t line = 0;
  std::map< std::string, size_t > listOfWords;

  in >> name >> line;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    for (auto iterWords = dictIter->second.begin(); iterWords != dictIter->second.end(); ++iterWords)
    {
      for (auto iterLines = iterWords->second.begin(); iterLines != iterWords->second.end(); ++iterLines)
      {
        if (*iterLines == line)
        {
          listOfWords.emplace(iterWords->first, 0);
        }
      }
    }
    size_t count = 0;
    for (auto it = listOfWords.begin(); it != listOfWords.end(); ++it)
    {
      out << ++count << ". " << it->first << "\n";
    }
  }
  else
  {
    out << " ������� � ��������� '" << name << "' �� ����������" << "\n";
  }
}

void litsinger::getIntersection(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string newname = "";
  std::string name = "";

  in >> newname >> name;

  if (newname != name)
  {
    auto newDictionaryIter = mapDictionaries.find(newname);
    auto existDictionaryIter = mapDictionaries.find(name);

    if (newDictionaryIter == mapDictionaries.end() && existDictionaryIter != mapDictionaries.end())
    {
      std::map< std::string, std::vector< size_t > > newDict = existDictionaryIter->second;
      for (auto it = existDictionaryIter->second.begin(); it != existDictionaryIter->second.end(); ++it) {
        newDict.emplace(it->first, it->second);
      }
      mapDictionaries.emplace(newname, newDict);
      out << " ������� '" << name << "' ������� ���������� � ������� '" << newname << "'\n";
    }
    else
    {
      out << " ������: ������� '" << name << "' �� ����������, ����'" << newname << "'�����\n";
    }
  }
  else
  {
    out << "�������� ������� � ������ ������� ���������, ������� ������ ��������"
        "������ �������\n";
  }
}

void litsinger::searchLetter(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  char letter;
  std::string name = "";

  in >> letter >> name;

  auto dictIter = mapDictionaries.find(name);

  if (dictIter != mapDictionaries.end())
  {
    std::map< std::string, std::vector< size_t > > newDict;

    for (auto it = dictIter->second.begin(); it != dictIter->second.end(); ++it) {
      if (letter == it->first.at(0))
      {
        newDict.emplace(it->first, it->second);
      }
    }

    if (!newDict.empty())
    {
      size_t count = 0;
      bool firstLine = false;
      for (auto it = newDict.begin(); it != newDict.end(); ++it) {
        out << ++count << ". " << it->first << " {";
        for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
        {
          if (firstLine)
          {
            out << ",";
          }
          else
          {
            firstLine = true;
          }
          out << *iter;
        }
        firstLine = false;
        out << "}\n";
      }
    }
    else
    {
      out << " ������� '" << name << "' �� ����� ���� � ������ ������ '" << letter << "'\n";
    }
  }
  else
  {
    out << " ������� '" << name << "' �� ������\n";
  }
}
