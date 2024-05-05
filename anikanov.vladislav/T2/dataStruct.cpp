#include "dataStruct.hpp"
#include <iostream>
#include <bitset>
#include <string>

std::istream &anikanov::operator>>(std::istream &in, anikanov::DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (std::tolower(c) != std::tolower(dest.exp))) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::UllLitIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  in >> dest.ref >> anikanov::DelimiterIO{'u'} >> anikanov::DelimiterIO{'l'} >> anikanov::DelimiterIO{'l'};
  if (!in) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::UllBinIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> anikanov::DelimiterIO{'0'} >> anikanov::DelimiterIO{'b'} >> dest.ref;
  if (!in) {
    in.setstate(std::ios::failbit);
  }
  dest.ref = std::bitset<64>(dest.ref).to_ullong();
  return in;
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> anikanov::DelimiterIO{'"'}, dest.ref, '"');
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::DelStrIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  size_t i = 0;
  while (dest.exp[i] != '\0') {
    in >> anikanov::DelimiterIO({dest.exp[i++]});
  }
  return in;
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  using del = anikanov::DelimiterIO;
  using delStr = anikanov::DelStrIO;
  using lit = anikanov::UllLitIO;
  using bin = anikanov::UllBinIO;
  using str = anikanov::StringIO;

  anikanov::DataStruct input;

  in >> delStr({"(:"});
  int number = 0;

  for (size_t i = 0; i < 3; i++) {
    in >> delStr({"key"}) >> number;

    switch (number) {
      case 1:
        in >> lit{input.key1};
        break;
      case 2:
        in >> bin {input.key2} >> std::dec;
        in >> std::dec;
        break;
      case 3:
        in >> str{input.key3};
        break;
      default:
        in.setstate(std::ios::failbit);
        break;
    }

    in >> del{':'};
  }

  in >> del{')'};

  if (in) {
    dest = input;
  }
  return in;
}

std::ostream &anikanov::operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  anikanov::iofmtguard fmtguard(out);

  out << "(:key1 " << src.key1 << "ull";

  std::string bin = std::bitset<sizeof(unsigned long long) * 8>(src.key2).to_string();
  long unsigned int pos = 0;
  while (bin[pos] == '0' && pos < bin.length() - 1) {
    pos++;
  }

  bin = bin.substr(pos);

  out << ":key2 0b" << bin;
  out << ":key3 \"" << src.key3 << "\":)";
  return out;
}

anikanov::iofmtguard::iofmtguard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{
}

anikanov::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
