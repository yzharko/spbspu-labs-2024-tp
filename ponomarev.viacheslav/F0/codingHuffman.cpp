#include "codingHuffman.hpp"
#include <iterator>

ponomarev::MinHeapNode::MinHeapNode(char data, int freq)
{
  left = right = nullptr;
  this->data = data;
  this->freq = freq;
}

bool ponomarev::Compare::operator()(MinHeapNode* l, MinHeapNode* r)
{
  return (l->freq > r->freq);
}

ponomarev::HuffmanCode::HuffmanCode():
  codes(),
  freq(),
  text(),
  decodingText(),
  minHeap()
{}

void ponomarev::HuffmanCode::putText(std::string data)
{
  text = data;
}


void ponomarev::printCodes(MinHeapNode* root, std::string str)
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

void ponomarev::storeCodes(MinHeapNode* root, std::string str, HuffmanCode & data)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->data != '$')
    {
        data.codes[root->data] = str;
    }
    storeCodes(root->left, str + "0", HuffmanCode & data);
    storeCodes(root->right, str + "1", HuffmanCode & data);
}

void ponomarev::createTree(int size, HuffmanCode & data)
{
    MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v = data.freq.begin(); v != data.freq.end(); v++)
    {
        data.minHeap.push(new MinHeapNode(v->first, v->second));
    }
    while (data.minHeap.size() != 1)
    {
        left = data.minHeap.top();
        data.minHeap.pop();
        right = data.minHeap.top();
        data.minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        data.minHeap.push(top);
    }
    storeCodes(data.minHeap.top(), "", HuffmanCode & data);
}

void ponomarev::calcFreq(std::string str, int n, HuffmanCode & data)
{
    for (int i = 0; i < str.size(); i++)
    {
        data.freq[str[i]]++;
    }
}

std::string ponomarev::decodeFile(MinHeapNode* root, std::string s)
{
    std::string ans = "";
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

void ponomarev::makeEncode(HuffmanCode & data)
{
  std::string str = data.text;
  if (str.empty())
  {
    ponomarev::printInvalidEncodeMessage();
  }
  else
  {
    ponomarev::calcFreq(str, str.length(), data);
    ponomarev::createTree(str.length(), data);
    std:: string encodedString = "";
    for (auto i : str)
    {
      encodedString += data.codes[i];
    }
    ponomarev::printSuccessfullyEncodeMessage();
  }
}
