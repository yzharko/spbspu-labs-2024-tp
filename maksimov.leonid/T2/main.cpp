#include <iostream>
#include <string>

namespace maksimov
{
  std::string makeStr(std::istream& is)
  {
    char c = 0;
    std::string str = "";
    is >> std::noskipws;
    while (is.peek() != ':' && is.peek() != ')')
    {
      is >> c;
      str += c;
    }
    is >> std::skipws;
    return str;
  }

  struct ElementI
  {
    size_t key;
    std::string elem;
  };

  std::istream& operator>>(std::istream& is, ElementI& exp)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
    std::string str = makeStr(is);
    exp.key = str[3] - '0';
    exp.elem = (str.find(' ') != std::string::npos) ? str.substr(str.find(' ') + 1, str.length()) : "";
    return is;
  }

  struct DelimiterI
  {
    char expected;
  };

  std::istream& operator>>(std::istream& is, DelimiterI&& exp)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
    char c = 0;
    is >> c;
    if (c != exp.expected)
    {
      is.setstate(std::ios::failbit);
    }
    return is;
  }

  struct MyStruct
  {
  public:
    MyStruct(int a, int b) :
      key1(a),
      key2(b)
    {};
    double getKey1() const
    {
      return key1;
    }
    unsigned long long getKey2() const
    {
      return key2;
    }
    std::string getKey3() const
    {
      return key3;
    }
  private:
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& is, MyStruct& value)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
    using del = DelimiterI;
    using elem = ElementI;
    elem a{ 0, "" };
    elem b{ 0, "" };
    elem c{ 0, "" };
    is >> del{ '(' } >> del{ ':' } >> a;
    is >> del{ ':' } >> b;
    is >> del{ ':' } >> c >> del{ ')' };
    if (is)
    {
      std::cout << "(:key" << a.key << ' ' << a.elem;
      std::cout << ":key" << b.key << ' ' << b.elem;
      std::cout << ":key" << c.key << ' ' << c.elem << ")\n";
    }
    return is;
  }

  std::ostream& operator<<(std::ostream& out, const MyStruct& value)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    out << "(" << value.getKey1() << ";" << value.getKey2() << ")";
    return out;
  }
}

int main()
{
  maksimov::MyStruct newStruct(0, 0);
  if (!(std::cin >> newStruct))
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    if (!(std::cin >> newStruct))
    {
      std::cerr << "Error\n";
    }
  }
  std::cout << newStruct << "\n";
  return 0;
}