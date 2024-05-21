#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <cstdlib>
#include "HuffmanTree.hpp"

void HuffmanTree::build(const std::string& text)
{
  freq_ = std::accumulate(
    text.begin(),
    text.end(),
    freq_,
    [](std::map<char, int>& freq, char c)
    {
      freq[c]++;
      return freq;
    }
  );
  std::priority_queue<Node*, std::vector<Node*>, Compare> pq;
  std::for_each(
    freq_.begin(),
    freq_.end(),
    [&pq](const std::pair< char, int >& kv)
    {
      pq.push(new Node(kv.first, kv.second));
    }
  );
  while (pq.size() > 1)
  {
    Node* left = pq.top();
    pq.pop();
    Node* right = pq.top();
    pq.pop();
    pq.push(new Node('\0', left->freq_ + right->freq_, left, right));
  }
  root_ = pq.top();
  genCode(root_, "");
}

void HuffmanTree::genCode(Node* node, const std::string& code)
{
  if (!node) return;
  if (!node->left_ && !node->right_)
  {
    codes_[node->symbol_] = code.empty() ? "1" : code;
  }
  genCode(node->left_, code + "0");
  genCode(node->right_, code + "1");
}

std::string HuffmanTree::encode(const std::string& text)
{
  return std::accumulate(
    text.begin(),
    text.end(),
    std::string{},
    [this](std::string& encoded, char c)
    {
      encoded += codes_[c];
      return encoded;
    }
  );
}

void HuffmanTree::freqTable(std::ostream& out)
{
  for (const auto& kv : freq_)
  {
    out << kv.first << ": " << kv.second << '\n';
  }
}

void HuffmanTree::codeTable(std::ostream& out)
{
  for (const auto& kv : codes_)
  {
    out << kv.first << ": " << kv.second << '\n';
  }
}
