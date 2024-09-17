#include "HuffmanCode.hpp"
#include <string>
#include <algorithm>
#include "delimiter.hpp"

redko::HuffmanCode::HuffmanCode():
  charsFreq_(),
  charsCode_(),
  sourseText_(),
  encodedText_(),
  root_(nullptr)
{}

redko::HuffmanCode::HuffmanCode(const std::string & src):
  charsFreq_(),
  charsCode_(),
  sourseText_(src),
  encodedText_(),
  root_(nullptr)
{}

redko::HuffmanCode::HuffmanCode(const std::string & res, const std::map< char, std::string > & alph):
  charsFreq_(),
  charsCode_(alph),
  sourseText_(),
  encodedText_(res),
  root_(nullptr)
{}

std::string redko::HuffmanCode::getEncoded()
{
  return encodedText_;
}

std::string redko::HuffmanCode::getDecoded()
{
  return sourseText_;
}

std::map< char, std::string > redko::HuffmanCode::getEncoding()
{
  return charsCode_;
}

void redko::HuffmanCode::encode()
{
  countFreq();
  makeCodeTree();
  makeCharCode(root_, "");
  for (auto i : sourseText_)
  {
    encodedText_ += charsCode_.find(i)->second;
  }
}

void redko::HuffmanCode::decode()
{
  root_ = new HuffmanNode();

  for (auto i : charsCode_)
  {
    HuffmanNode * curr = root_;
    for (auto j : i.second)
    {
      if (j == '0')
      {
        if (!curr->left)
        {
          curr->left = new HuffmanNode();
        }
        curr = curr->left;
      }
      else
      {
        if (!curr->right)
        {
          curr->right = new HuffmanNode();
        }
        curr = curr->right;
      }
    }
    curr->data = i.first;
  }

  HuffmanNode * curr = root_;
  for (auto i : encodedText_)
  {
    if (i == '0' && curr->left)
    {
      curr = curr->left;
    }
    else if (i == '1' && curr->right)
    {
      curr = curr->right;
    }

    if (!curr->left && !curr->right)
    {
      sourseText_ += curr->data;
      curr = root_;
    }
  }
}

void redko::HuffmanCode::countFreq()
{
  for (auto i : sourseText_)
  {
    auto it = charsFreq_.find(i);
    if (it == charsFreq_.end())
    {
      charsFreq_.insert({ i, 1 });
    }
    else
    {
      ++(it->second);
    }
  }
}

void redko::HuffmanCode::makeCharCode(HuffmanNode * node, const std::string & str)
{
  if (node->left || node->right)
  {
    if (node->left)
    {
      makeCharCode(node->left, str + "0");
    }
    if (node->right)
    {
      makeCharCode(node->right, str + "1");
    }
  }
  else
  {
    charsCode_.insert({ node->data, str });
  }
}

void redko::HuffmanCode::makeCodeTree()
{
  std::priority_queue< HuffmanNode *, std::vector< HuffmanNode * >, HuffmanComp > nodes;
  HuffmanNode * tmp = nullptr;
  for (auto i : charsFreq_)
  {
    tmp = new HuffmanNode(i.second, i.first);
    nodes.push(tmp);
  }
  if (nodes.size() == 1)
  {
    tmp = nodes.top();
    root_ = new HuffmanNode(nodes.top()->freq, '0', nodes.top(), nullptr);
  }
  else
  {
    while (nodes.size() > 1)
    {
      HuffmanNode * left = nodes.top();
      nodes.pop();
      HuffmanNode * right = nodes.top();
      nodes.pop();
      tmp = new HuffmanNode(left->freq + right->freq, '0', left, right);
      nodes.push(tmp);
    }
    root_ = nodes.top();
  }
}

bool redko::isBinary(const std::string & str)
{
  return std::all_of(str.begin(), str.end(), [](char i){ return i == '0' || i == '1'; });
}

std::istream & redko::operator>>(std::istream & in, HuffmanCode & obj)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string encodedText = "";
  in >> encodedText;
  if (!isBinary(encodedText))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::map< char, std::string > encoding;
  char c;
  std::string code = "";
  while (in >> code && code != "end" && !in.eof())
  {
    if (!isBinary(code))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in >> DelimiterIO{ ':' };
    in.get(c);
    encoding.insert({ c, code });
  }
  if (in.eof() || code == "end")
  {
    in.get();
    obj = HuffmanCode(encodedText, encoding);
  }
  return in;
}
