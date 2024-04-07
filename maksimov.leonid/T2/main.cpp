#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <iterator>

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
    MyStruct(ElementI a, ElementI b, ElementI c)
    {
      std::vector <ElementI> arr = {a, b, c};
      for (size_t i = 0; i < 3; ++i)
      {
        switch (arr[i].key)
        {
          case 1:
            key1 = stod(arr[i].elem);
            break;
          case 2:
            key2 = stol(arr[i].elem);
            break;
          case 3:
            key3 = arr[i].elem.substr(1, arr[i].elem.length() - 2);
            break;
        default:
          break;
        }
      }
    };

    MyStruct(int a, int b, int c) :
      key1(0),
      key2(0),
      key3("")
    {};

    MyStruct() = default;

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
      value = MyStruct{ a, b, c };
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
    out << "(:key1 " << std::setprecision(2) << std::scientific << value.getKey1();
    out << ":key2 0" << value.getKey2();
    out << ":key3 \"" << value.getKey3() << "\")";
    return out;
  }
}

int main()
{
  std::vector< maksimov::MyStruct > data;
  if (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< maksimov::MyStruct >{std::cin},
      std::istream_iterator< maksimov::MyStruct >{},
      std::back_inserter(data)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<maksimov::MyStruct>(std::cout, "\n")
  );
  return 0;
}
