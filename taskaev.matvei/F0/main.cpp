#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <vector>

class Node
{
public:
  int a;
  char c;
  Node* left, * right;
  Node() { left = right = NULL; }
  Node(Node* L, Node* R)
  {
    left = L;
    right = R;
    a = L->a + R->a;
  }
};

struct MyCompare
{
  bool operator()(Node* l, Node* r) const
  {
    return l->a < r->a;
  }
};

std::vector<bool> code;
std::map<char, std::vector<bool>> table;

void BuildTable(Node* root, std::vector<bool>& current_code)
{
  if (root->left != NULL)
  {
    current_code.push_back(0);
    BuildTable(root->left, current_code);
    current_code.pop_back();
  }
  if (root->right != NULL)
  {
    current_code.push_back(1);
    BuildTable(root->right, current_code);
    current_code.pop_back();
  }
  if (root->left == NULL && root->right == NULL) table[root->c] = current_code;
}


void someFunction(const std::string& s)
{
  std::map<char, int> m;
  for (int i = 0; i < s.length(); i++)
  {
    char c = s[i];
    m[c]++;
  }

  std::list<Node*> t;
  std::map<char, int>::iterator i;
  for (std::map<char, int>::iterator itr = m.begin(); itr != m.end(); itr++)
  {

    Node* p = new Node;
    p->c = itr->first;
    p->a = itr->second;
    t.push_back(p);
  }

  while (t.size() != 1)
  {
    t.sort(MyCompare());

    Node* SonL = t.front();
    t.pop_front();
    Node* SonR = t.front();
    t.pop_front();

    Node* parent = new Node(SonL, SonR);
    t.push_back(parent);
  }

  Node* root = t.front();
  BuildTable(root, code);

  for (int i = 0; i < s.length(); i++)
  {
    char c = s[i];
    std::vector<bool> x = table[c];
    for (int n = 0; n < x.size(); n++)
    {
      std::cout << x[n];
    }
  }
  std::cout << std::endl;
  std::cout << "well done\n";
}

std::string inputData(std::istream& is)
{
  std::string str;
  getline(std::cin, str);
  return str;
}


int main()
{
  std::cout << "Hello World, huffman coding!\n";
  std::string s = "";
  std::string input_comand;
  const std::string END = "end";
  bool flag = true;
  while (flag)
  {
    std::cout << "Enter command (help, input, encode) :\n ";
    std::cin >> input_comand;
    if (input_comand == END)
    {
      flag = false;
      std::cout << "good bye\n";
    }
    else if (input_comand == "input")
    {
      std::getline(std::cin >> std::ws, s);
    }
    else if (input_comand == "encode")
    {
      someFunction(s);
      std::string s = "";
    }
    else if (input_comand == "help")
    {
      std::cout << "Available commands\n"
        "help - display available commands\n"
        "input - standard input\n"
        "encode - encode input data\n";
    }
    else
    {
      std::cout << "NOT COMMAND\n";
    }
  }
  return 0;
}

