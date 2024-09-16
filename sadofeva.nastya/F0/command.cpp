#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "command.hpp"

namespace sadofeva
{
  void createDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;
    Dictionary dict;
    if (!searchDict(dictionaries, dict_name))
    {
      dictionaries.emplace(dict_name, dict);
      out << "Dictionary \"" << dict_name << "\" has been created.\n";
    }
    else
    {
      out << "Dictionary \"" << dict_name << "\" already exists.\n";
    }
  }

  void deleteDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    auto place = dictionaries.find(dict_name);
    dictionaries.erase(place);
    out << "Dictionary \"" << dict_name << "\" was deleted.\n";
  }

  void readTextIntoDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name;
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string line;
    in.ignore();
    std::getline(in, line);

    const std::string delimiters = " \n\r\t,.;:!?'\"-";

    size_t start = line.find_first_not_of(delimiters);
    size_t end;

    while (start != std::string::npos)
    {
      end = line.find_first_of(delimiters, start + 1);
      if (end == std::string::npos)
      {
        end = line.length();
      }

      std::string word = line.substr(start, end - start);

      word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
      std::transform(word.begin(), word.end(), word.begin(), tolower);
      ++dictionaries[dict_name][word];

      start = line.find_first_not_of(delimiters, end + 1);
    }

    out << "Added text to dictionary \"" << dict_name << "\".\n";
  }

  void readFile(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string file_name = "";
    in >> file_name;
    std::ifstream file(file_name);
    if (!file.is_open())
    {
      throw std::runtime_error("File didn't open");
    }

    std::string word;
    while (file >> word)
    {
      word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
      std::transform(word.begin(), word.end(), word.begin(), tolower);
      ++dictionaries[dict_name][word];
    }

    out << "File \"" << file_name << "\" has been read into the dictionary \"" << dict_name << "\".\n";
  }

  void findWord(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string word = "";
    in >> word;
    if (searchWrd(dictionaries[dict_name], word))
    {
      out << "Word \"" << word << "\" exists in dictionary \"" << dict_name << "\" with frequency "
        << dictionaries[dict_name][word] << ".\n";
    }
    else
    {
      dictionaries[dict_name][word] = 1;
      out << "Word \"" << word << "\" does not exist in dictionary \"" << dict_name << "\".\n";
    }
  }

  void deleteWord(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string word = "";
    in >> word;
    if (searchWrd(dictionaries[dict_name], word))
    {
      dictionaries[dict_name].erase(word);
      out << "Word \"" << word << "\" has been deleted from dictionary \"" << dict_name << "\".\n";
    }
    else
    {
      out << "Word \"" << word << "\" does not exist in dictionary \"" << dict_name << "\".\n";
    }
  }

  void getWordCount(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    out << "Count of words in dictionary \"" << dict_name << "\" is " << dictionaries[dict_name].size() << ".\n";
  }

  void getFrequency(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string word = "";
    in >> word;
    if (searchWrd(dictionaries[dict_name], word))
    {
      out << "Word \"" << word << "\" has frequency " << dictionaries[dict_name][word] << " in dictionary \""
        << dict_name << "\".\n";
    }
    else
    {
      out << "Word \"" << word << "\" does not exist in dictionary \"" << dict_name << "\".\n";
    }
  }

  void getMostUseWord(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    size_t n;
    in >> n;

    std::vector< std::pair< std::string, size_t > > items(dictionaries[dict_name].begin(),
      dictionaries[dict_name].end());
    std::sort(items.begin(), items.end(), compareFrequency);

    out << "Most used words in dictionary \"" << dict_name << "\":\n";
    for (size_t i = 0; i < std::min(n, items.size()); ++i)
    {
      out << items[i].first << " with frequency of " << items[i].second << "\n";
    }
  }

  void clearDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    dictionaries[dict_name].clear();
    out << "All words in the dictionary \"" << dict_name << "\" have been deleted.\n";
  }

  void removeText(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string text = "";
    std::getline(in, text);

    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (auto& dict: dictionaries)
    {
      size_t start = 0;
      while ((start = text.find_first_of(alphabet, start)) != std::string::npos)
      {
        size_t end = text.find_first_not_of(alphabet, start);
        std::string word = text.substr(start, end - start);
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (searchWrd(dict.second, word))
        {
          if (dict.second[word] > 1)
          {
            dict.second[word]--;
            out << "Decreased the counter for word \"" << word << "\" in the \"" << dict.first << "\" dictionary.\n";
          }
          else
          {
            dict.second.erase(word);
            out << "Word \"" << word << "\" has been deleted from dictionary \"" << dict.first << "\".\n";
          }
        }
        start = end;
      }
    }
  }

  void complementDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string new_dict_name, dict_name1, dict_name2;
    in >> new_dict_name >> dict_name1 >> dict_name2;
    if (!searchDict(dictionaries, dict_name1) || !searchDict(dictionaries, dict_name2))
    {
      out << "One or both dictionaries do not exist.\n";
      return;
    }

    Dictionary new_dict;

    for (const auto& word: dictionaries[dict_name1])
    {
      if (!searchWrd(dictionaries[dict_name2], word.first))
      {
        new_dict[word.first] = word.second;
      }
      else
      {
        if (word.second > dictionaries[dict_name2][word.first])
        {
          new_dict[word.first] = word.second - dictionaries[dict_name2][word.first];
        }
      }
    }

    dictionaries[new_dict_name] = new_dict;
    out << "New dictionary \"" << new_dict_name << "\" has been created.\n";
  }

  void intersectDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string new_dict_name, dict_name1, dict_name2;
    in >> new_dict_name >> dict_name1 >> dict_name2;
    if (!searchDict(dictionaries, dict_name1) || !searchDict(dictionaries, dict_name2))
    {
      out << "One or both dictionaries do not exist.\n";
      return;
    }

    Dictionary new_dict;

    for (const auto& word: dictionaries[dict_name1])
    {
      if (searchWrd(dictionaries[dict_name2], word.first))
      {
        new_dict[word.first] = std::min(word.second, dictionaries[dict_name2][word.first]);
      }
    }

    dictionaries[new_dict_name] = new_dict;
    out << "New dictionary \"" << new_dict_name << "\" has been created.\n";
  }

  void unionDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string new_dict_name, dict_name1, dict_name2;
    in >> new_dict_name >> dict_name1 >> dict_name2;
    if (!searchDict(dictionaries, dict_name1) || !searchDict(dictionaries, dict_name2))
    {
      out << "One or both dictionaries do not exist.\n";
      return;
    }

    Dictionary new_dict;

    for (const auto& word: dictionaries[dict_name1])
    {
      new_dict[word.first] = word.second;
    }

    for (const auto& word: dictionaries[dict_name2])
    {
      new_dict[word.first] += word.second;
    }

    dictionaries[new_dict_name] = new_dict;
    out << "New dictionary \"" << new_dict_name << "\" has been created.\n";
  }

  void printHelp(dictionaryOfNames&, std::istream& in, std::ostream& out)
  {
    out << "Select which command you need: \n";
    out << "Write down \"All\" to get full info: \n";
    out << "Write down \"Skip\" to skip this function: \n";

    std::string tmp = "";
    in >> tmp;

    if (tmp == "Skip")
    {
      return;
    }
    else if (tmp == "All")
    {
      out << "1. create \"name\" - Create a new dictionary with the given name.\n";
      out << "2. deleteWord \"dictionary name\" \"word\" - Delete a word from a specified dictionary.\n";
      out << "3. deleteDataset \"name\" - Delete the specified dictionary.\n";
      out << "4. findWord \"dictionary name\" \"word\" - Check if the word exists in the specified dictionary.\n";
      out << "5. getWordCount \"dictionary name\" - Get the total count of words in the specified dictionary.\n";
      out << "6. readFile \"dictionary name\" \"file name\" - Load words from a file into the specified dictionary.\n";
      out << "7. readText \"dictionary name\" - Load words from a single line of text into the specified dictionary.\n";
      out << "8. clear \"dictionary name\" - Remove all words from the specified dictionary.\n";
      out << "9. getFrequency \"dictionary name\" \"word\" - Get the frequency of the word in the specified dictionary.\n";
      out << "10. getMostUseWord \"dictionary name\" \"n\" - Get the top n words in terms of usage from the specified "
        "dictionary.\n";
      out << "11. remove \"text\" - Remove given text from all dictionaries.\n";
      out << "12. complement \"new_dict\" \"dict1\" \"dict2\" - Create new dictionary that includes words from dict1 that "
        "do not exist in dict2.\n";
      out << "13. intersect \"new_dict\" \"dict1\" \"dict2\" - Create new dictionary that includes words that exist in "
        "both dict1 and dict2.\n";
      out << "14. union \"new_dict\" \"dict1\" \"dict2\" - Create new dictionary that includes all words from dict1 and "
        "dict2.\n";
      out << '\n';
    }
    else
    {
      throw std::logic_error("Wrong input");
    }
  }
}

