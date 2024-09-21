#include "Dictionary.h"

void Dictionary::addWord(const std::string &word) {
  words[word];
}

void Dictionary::addDefinition(const std::string &word, const std::string &definition) {
  if (words.find(word) == words.end()) {
    throw std::runtime_error("Такого слова не существует");
  }
  words[word].push_back(definition);
}

void Dictionary::removeWord(const std::string &word) {
  if (words.erase(word) == 0) {
    throw std::runtime_error("Такого слова не существует");
  }
}

std::vector<std::string> Dictionary::translate(const std::string &word) const {
  auto it = words.find(word);
  if (it == words.end()) {
    throw std::runtime_error("Такого слова не существует");
  }
  return it->second;
}

void Dictionary::show() const {
  for (const auto& entry : words) {
    std::cout << entry.first << ": ";
    for (const auto& translation : entry.second) {
      std::cout << translation << "; ";
    }
    std::cout << std::endl;
  }
}

std::pair<std::string, std::string> Dictionary::randomWord() const {
  if (words.empty()) {
    throw std::runtime_error("Словарь пуст");
  }
  auto it = words.begin();
  std::advance(it, std::rand() % words.size());
  return { it->first, it->second.front() };
}
