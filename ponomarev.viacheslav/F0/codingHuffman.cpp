#include "codingHuffman.hpp"
#include <iterator>
#include <iostream>
#include <fstream>
#include "accessoryFunctions.hpp"

ponomarev::MinHeapNode::MinHeapNode(char data, int freq)
{
  left = right = nullptr;
  this->data = data;
  this->freq = freq;
}

bool ponomarev::Compare::operator()(MinHeapNode * l, MinHeapNode * r)
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

void ponomarev::printCodes(MinHeapNode * root, std::string str)
{
    if (!root)
    {
      return;
    }

    if (root->data != '$')
    {
      char symbol = root->data;
      if (symbol == '\n')
      {
        std::cout << "\\" << "n";
        std::cout << ": " << str << "\n";
      }
      else
      {
        std::cout << root->data << ": " << str << "\n";
      }
    }

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void ponomarev::storeCodes(MinHeapNode * root, std::string str, HuffmanCode & data)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data != '$')
    {
        data.codes[root->data] = str;
    }

    storeCodes(root->left, str + "0", data);
    storeCodes(root->right, str + "1", data);
}

void ponomarev::createTree(HuffmanCode & data)
{
    MinHeapNode * left, * right, * top;

    for (std::map< char, int >::iterator v = data.freq.begin(); v != data.freq.end(); v++)
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

    storeCodes(data.minHeap.top(), "", data);
}

void ponomarev::calcFreq(std::string str, HuffmanCode & data)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        data.freq[str[i]]++;
    }
}

void ponomarev::decodeFile(HuffmanCode & data)
{
    MinHeapNode * root = data.minHeap.top();
    MinHeapNode * curr = root;
    std::string s = data.decodingText;
    std::string ans = "";

    for (size_t i = 0; i < s.size(); i++)
    {
      if (s[i] == '0')
      {
        curr = curr->left;
      }
      else
      {
        curr = curr->right;
        if ((curr->left == nullptr) && (curr->right == nullptr))
        {
          ans += curr->data;
          curr = root;
        }
      }
    }

    data.text = ans;
}

void ponomarev::makeEncode(HuffmanCode & data)
{
  std::string str = data.text;

  if (str.empty())
  {
    ponomarev::printInvalidEncodeMessage(std::cout);
  }
  else
  {
    ponomarev::calcFreq(str, data);
    ponomarev::createTree(data);
    std::string encodedString = "";

    for (char i : str)
    {
      encodedString += data.codes[i];
    }

    ponomarev::printSuccessfullyEncodeMessage(std::cout);
  }
}

void ponomarev::fillFreq(std::string parameter, HuffmanCode & data)
{
  std::ifstream input(parameter);

  if (!input)
  {
    throw std::logic_error("can't open the file");
  }

  std::string str = "";

  while (input >> str)
  {
    char symbol = cutType(str)[0];
    int freq = std::stoi(str);
    data.freq[symbol] = freq;
  }

  ponomarev::printSuccessfullyFrequenceInput(std::cout);
}




