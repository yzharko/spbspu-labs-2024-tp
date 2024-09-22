#include "DictionaryManager.h"

void DictionaryManager::combine(const std::string &dict1, const std::string &dict2, const std::string &newDict) {
  if (dictionaries.find(newDict) != dictionaries.end()) {
    throw std::runtime_error("Такой словарь уже существует");
  }
  if (dictionaries.find(dict1) == dictionaries.end() || dictionaries.find(dict2) == dictionaries.end()) {
    throw std::runtime_error("Такого словаря не существует");
  }

  Dictionary combined;
  for (const auto& entry : dictionaries[dict1].getWords()) {
    combined.addWord(entry.first);
    for (const auto& translation : entry.second) {
      combined.addDefinition(entry.first, translation);
    }
  }
  for (const auto& entry : dictionaries[dict2].getWords()) {
    combined.addWord(entry.first);
    for (const auto& translation : entry.second) {
      combined.addDefinition(entry.first, translation);
    }
  }
  dictionaries[newDict] = combined;
}

void DictionaryManager::translate(const std::string &dictName, const std::string &word) const {
  if (dictionaries.find(dictName) == dictionaries.end()) {
    throw std::runtime_error("Такого словаря не существует");
  }
  auto translations = dictionaries.at(dictName).translate(word);
  std::cout << word << ": ";
  for (const auto& translation : translations) {
    std::cout << translation << "; ";
  }
  std::cout << std::endl;
}
