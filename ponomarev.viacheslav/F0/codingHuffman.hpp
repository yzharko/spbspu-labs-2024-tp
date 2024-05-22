#ifndef CODING_HUFFMAN_HPP
#define CODING_HUFFMAN_HPP

#include <map>
#include <vector>
#include <queue>
#include <string>

namespace ponomarev
{
  struct MinHeapNode
  {
    MinHeapNode(char data, int freq);

    char data;
    int freq;
    MinHeapNode *left, *right;
  };

  struct Compare
  {
    bool operator()(MinHeapNode* l, MinHeapNode* r);
  };

  class HuffmanCode
  {
  public:
    HuffmanCode();

    void putText(std::string data);

    std::map<char, std::string> codes;
    std::map<char, int> freq;
    std::string text;
    std::string decodingText;
    std::priority_queue<MinHeapNode*, std::vector<MinHeapNode*>, Compare> minHeap;
  };

  void printCodes(MinHeapNode* root, std::string str);
  void storeCodes(MinHeapNode* root, std::string str, HuffmanCode & data);
  void createTree(HuffmanCode & data);
  void calcFreq(std::string str, HuffmanCode & data);
  std::string decodeFile(struct MinHeapNode* root, std::string s);
  void makeEncode(HuffmanCode & data);
}

#endif
