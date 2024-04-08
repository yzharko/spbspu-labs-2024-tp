#ifndef DATASTRUST
#define DATASTRUCT
#include <string>
#include <utility>
#include <iostream>

namespace kovshikov
{
  struct DataStruct
  {
  public:
    DataStruct():
    key1_('a'),
    key2_(27, 2005),
    key3_("nikita")
    {};
    DataStruct(char ch, long long pairFirst, unsigned long long pairSecond, std::string str):
    key1_(ch),
    key2_(pairFirst, pairSecond),
    key3_(str)
    {};
    char getKey1() const
    {
      return key1_;
    }
    long long getFirstKey2() const
    {
      return key2_.first;
    }
    unsigned long long getSecondKey2() const
    {
      return key2_.second;
    }
    std::string getKey3() const
    {
      return key3_;
    }
  private:
    char key1_;
    std::pair<long long, unsigned long long> key2_;
    std::string key3_;
  };
  std::istream & operator>>(std::istream &is, DataStruct &value)
  {
    //для ввода использовать delimetr;
    std::istream::sentry guard(is);
    if(!guard)
    {
      return is;
    }
    char ch = ' ';
    long long pairFirst = 0;
    unsigned long long pairSecond;
    std::string str = "";
    //записать в cin учитывая беспорядочность ключей на потоке ввода;
    is >> ch >> pairFirst >> pairSecond >> str;
    if(is)
    {
      value = DataStruct(ch, pairFirst, pairSecond, str);
    }
    //учесть игнорирование неправильного ввода;
    return is;
  }
  std::ostream & operator<<(std::ostream & out, const DataStruct &value)
  {
    std::ostream::sentry guard(out);
    if(!guard)
    {
      return out;
    }
    out << "(:key1 " << value.getKey1() << ":key2 (:N " << value.getFirstKey2()
    << ":D " << value.getSecondKey2() << ":):key3 " << value.getKey3() << ":)";
    return out;
  }
}

#endif
