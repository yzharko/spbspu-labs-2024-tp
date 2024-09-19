#ifndef HUFFMANCODE_HPP
#define HUFFMANCODE_HPP
#include <iostream>
#include <queue>
#include <map>

namespace redko
{
  class HuffmanCode
  {
  public:
    HuffmanCode();
    explicit HuffmanCode(const std::string & src);
    HuffmanCode(const std::string & res, const std::map< char, std::string > & alph);

    std::string getEncoded();
    std::string getDecoded();

    std::map< char, std::string > getEncoding();

    void encode();
    void decode();

  private:
    struct HuffmanNode
    {
      HuffmanNode(unsigned long frequency = 0, char c = '0', HuffmanNode * lPtr = nullptr, HuffmanNode * rPtr = nullptr):
        freq(frequency),
        data(c),
        left(lPtr),
        right(rPtr)
      {}

      unsigned long freq;
      char data;
      HuffmanNode * left;
      HuffmanNode * right;
    };

    struct HuffmanComp
    {
      bool operator()(const HuffmanNode * lhs, const HuffmanNode * rhs)
      {
        return lhs->freq > rhs->freq;
      }
    };

    void countFreq();
    void makeCharCode(HuffmanNode * node, const std::string & str);
    void makeCodeTree();

    std::map< char, unsigned long > charsFreq_;
    std::map< char, std::string > charsCode_;
    std::string sourseText_;
    std::string encodedText_;
    HuffmanNode * root_;
  };

  bool isBinary(const std::string & str);
  std::istream & operator>>(std::istream & in, HuffmanCode & obj);
}

#endif
