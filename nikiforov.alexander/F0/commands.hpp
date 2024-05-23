#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iomanip>
#include <map>
#include <algorithm>

using mapDictionaries_t = std::map< std::string, std::map< std::string, size_t > >;
using invertedMap_t = std::multimap< size_t, std::string >;

namespace nikiforov
{
  std::string cutNameFile(std::string& str);

  void createDictionary(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string mkdir);
  std::map<std::string, size_t> getDictionary(std::istream& in);
  void deleteDelimeters(std::string& str);
  bool checkAlpha(std::string& str);

  void open(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void deleteDictionary(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void printNamesDictionaries(const mapDictionaries_t& mapDictionaries, std::ostream& out);

  void add(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void unite(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void rename(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void clear(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void save(const mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void writingDictionaries(const mapDictionaries_t& mapDictionaries, std::string nameMkdir,std::ofstream& fout);

  void printWordAndFrequency(std::map< std::string, size_t >::iterator iterPair, std::ostream& out);
  void printWordAndFrequency(std::reverse_iterator < std::map< size_t, std::string >::iterator> iterPair, std::ostream& out);
  void printWordAndFrequency(std::pair< std::string, size_t > pair, std::ostream& out);

  class ActionsOnTheDictionary
  {
  public:
    ActionsOnTheDictionary() : nameSelectedDictionary("") {}

    void select(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
    void print(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
    void printMost(std::multimap< size_t, std::string > & invertedDictionary, std::istream& in, std::ostream& out);
    void find(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
    void erase(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

    bool isSelectedDictionary();

  private:
    std::string nameSelectedDictionary;
  };

  template<typename A, typename B>
  std::pair<B, A> invertedPair(const std::pair<A, B>& p);

  template<typename A, typename B>
  std::multimap<B, A> invertedMap(const std::map<A, B>& dictionary);
}

template<typename A, typename B>
std::pair<B, A> nikiforov::invertedPair(const std::pair<A, B>& p)
{
  return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> nikiforov::invertedMap(const std::map<A, B>& dictionary)
{
  std::multimap<B, A> invertedDictionary;
  std::transform(dictionary.begin(), dictionary.end(),
    std::inserter(invertedDictionary, invertedDictionary.begin()),
    invertedPair<A, B>
  );
  return invertedDictionary;
}

#endif
