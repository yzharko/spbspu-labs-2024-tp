#include "codingHuffman.hpp"
#include <iterator>

ponomarev::HuffmanCode::HuffmanCode():
  codes(),
  freq(),
  text(),
  decodingText(),
  minHeap()
{}

void ponomarev::HuffmanCode::printCodes(MinHeapNode* root, string str)
{
    if (!root)
    {
        return;
    }
    if (root->data != '$')
    {
        cout << root->data << ": " << str << "\n";
    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void ponomarev::HuffmanCode::storeCodes(MinHeapNode* root, string str)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->data != '$')
    {
        codes[root->data] = str;
    }
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

void ponomarev::HuffmanCode::createTree(int size)
{
    MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
    {
        minHeap.push(new MinHeapNode(v->first, v->second));
    }
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}

void ponomarev::HuffmanCode::calcFreq(string str, int n)
{
    for (int i = 0; i < str.size(); i++)
    {
        freq[str[i]]++;
    }
}

string ponomarev::HuffmanCode::decodeFile(MinHeapNode* root, string s)
{
    string ans = "";
    MinHeapNode* curr = root;
    for (int i = 0; i < s.size(); i++)
    {
      if (s[i] == '0')
      {
        curr = curr->left;
      }
      else
      {
        curr = curr->right;
        if (curr->left == nullptr && curr->right == nullptr)
        {
          ans += curr->data;
          curr = root;
        }
      }
    }
    return ans + '\0';
}
