#ifndef CODING_HUFFMAN_HPP
#define CODING_HUFFMAN_HPP

#include <map>
#include <vector>

namespace ponomarev
{
  class HuffmanCode
  {
  public:
    HuffmanCode();

    void printCodes(MinHeapNode* root, string str);
    void storeCodes(MinHeapNode* root, string str);
    void createTree(int size);
    void calcFreq(string str, int n)

    string decodeFile(struct MinHeapNode* root, string s);

  private:
    struct MinHeapNode
    {
      MinHeapNode(char data, int freq)
      {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
      }

      char data;
      int freq;
      MinHeapNode *left, *right;
    };

    struct Compare
    {
      bool operator()(MinHeapNode* l, MinHeapNode* r)
      {
        return (l->freq > r->freq);
      }
    };

    map<char, string> codes;
    map<char, int> freq;
    std::string text;
    std::string decodingText;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, Compare> minHeap;
}

#endif
