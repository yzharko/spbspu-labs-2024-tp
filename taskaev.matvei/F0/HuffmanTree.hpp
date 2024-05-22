#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <cstdlib>

namespace taskaev
{
  class HuffmanTree
  {
    public:
      void build(const std::string& text);
      std::string encode(const std::string& text);
      void freqTable(std::ostream& out);
      void codeTable(std::ostream& out);
    private:
      struct Node
      {
        char symbol_;
        int freq_;
        Node* left_;
        Node* right_;
        Node(char symbol, int freq, Node* left = nullptr, Node* right = nullptr):
          symbol_(symbol), freq_(freq), left_(left), right_(right) {}
      };
      struct Compare
      {
        bool operator()(Node* left, Node* right)
        {
          return left->freq_ > right->freq_;
        }
      };
      void genCode(Node* node, const std::string& code);
      Node* root_;
      std::map<char, int> freq_;
      std::map<char, std::string> codes_;
  };
}
#endif
