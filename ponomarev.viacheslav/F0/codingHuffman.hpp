#ifndef CODING_HUFFMAN_HPP
#define CODING_HUFFMAN_HPP

#include <map>
#include <vector>

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

  private:
    map<char, string> codes;
    map<char, int> freq;
    std::string text;
    std::string decodingText;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, Compare> minHeap;
  }

    void printCodes(MinHeapNode* root, std::string str);
    void storeCodes(MinHeapNode* root, std::string str, HuffmanCode & data);
    void createTree(int size, HuffmanCode & data);
    void calcFreq(std::string str, int n, HuffmanCode & data);
    string decodeFile(struct MinHeapNode* root, std::string s);
    void makeEncode(HuffmanCode & data);
}

#endif
