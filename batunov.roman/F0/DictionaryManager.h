#ifndef DICTIONARYMANAGER_H
#define DICTIONARYMANAGER_H
#include "Dictionary.h"

class DictionaryManager {
public:

  void help() const {

    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    std::cout << "Доступные команды:\n"
          << "help - вывод списка доступных команд.\n"
          << "list - вывод названий всех существующих словарей.\n"
          << "create <dictionary1> - создание нового словаря.\n"
          << "delete <dictionary1> - удаление существующего словаря.\n"
          << "combine <dictionary1> <dictionary2> <dictionary3> - создать новый словарь, содержащий слова из существующих.\n"
          << "add <dictionary1> <word1> - добавить слово в словарь.\n"
          << "definition <dictionary1> <word1> <слово1> - добавить перевод слова.\n"
          << "remove <dictionary1> <word1> - удалить слово из словаря.\n"
          << "translate <dictionary1> <word1> - вывод переводов слова.\n"
          << "size <dictionary1> - вывод количества слов в словаре.\n"
          << "show <dictionary1> - вывод всех слов в словаре.\n"
          << "random <dictionary1> - вывод случайного слова из словаря.\n";
  }

  void list() const {
    for (const auto& dict : dictionaries) {
      std::cout << dict.first << std::endl;
    }
  }

  void create(const std::string& name) {
    if (dictionaries.find(name) != dictionaries.end()) {
      throw std::runtime_error("Такой словарь уже существует");
    }
    dictionaries[name] = Dictionary();
  }

  void remove(const std::string& name) {
    if (dictionaries.erase(name) == 0) {
      throw std::runtime_error("Такого словаря не существует");
    }
  }

  void combine(const std::string& dict1, const std::string& dict2, const std::string& newDict) ;

  void add(const std::string& dictName, const std::string& word) {
    if (dictionaries.find(dictName) == dictionaries.end()) {
      throw std::runtime_error("Такого словаря не существует");
    }
    dictionaries[dictName].addWord(word);
  }

  void definition(const std::string& dictName, const std::string& word, const std::string& translation) {
    if (dictionaries.find(dictName) == dictionaries.end()) {
      throw std::runtime_error("Такого словаря не существует");
    }
    dictionaries[dictName].addDefinition(word, translation);
  }

  void removeWord(const std::string& dictName, const std::string& word) {
    if (dictionaries.find(dictName) == dictionaries.end()) {
      throw std::runtime_error("Такого словаря не существует");
    }
    dictionaries[dictName].removeWord(word);
  }

  void translate(const std::string& dictName, const std::string& word) const ;

  void size(const std::string& dictName) const {
    if (dictionaries.find(dictName) == dictionaries.end()) {
      throw std::runtime_error("Такого словаря не существует");
    }
    std::cout << dictionaries.at(dictName).size() << std::endl;
  }

  void show(const std::string& dictName) const {
    if (dictionaries.find(dictName) == dictionaries.end()) {
      throw std::runtime_error("Такого словаря не существует");
    }
    dictionaries.at(dictName).show();
  }

  void random(const std::string& dictName) const {
    if (dictionaries.find(dictName) == dictionaries.end()) {
      throw std::runtime_error("Такого словаря не существует");
    }
    auto wordPair = dictionaries.at(dictName).randomWord();
    std::cout << wordPair.first << ": " << wordPair.second << std::endl;
  }

private:
  std::map<std::string, Dictionary> dictionaries;
};

#endif
