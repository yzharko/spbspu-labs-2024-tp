#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <map>
#include <vector>
class Dictionary {
public:
  void addWord(const std::string& word);

  void addDefinition(const std::string& word, const std::string& definition) ;

  void removeWord(const std::string& word) ;

  std::vector<std::string> translate(const std::string& word) const ;

  size_t size() const {
    return words.size();
  }
  std::map<std::string, std::vector<std::string>> getWords() {
    return words;
  }
  void show() const ;

  std::pair<std::string, std::string> randomWord() const ;

private:
  std::map<std::string, std::vector<std::string>> words;
};

#endif
