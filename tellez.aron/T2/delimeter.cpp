#include "delimeter.hpp"

std::istream& tellez::operator>>(std::istream& in, Delimeterchar&& exp)
{
  std::istream::sentry guard(in);
  char c = 0;
  in >> c;
  if (guard && in.get(c) && c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& tellez::operator>>(std::istream& in, Delimeterstring&& exp)
{
  size_t i = 0;
  while (exp.expected[i] != '\0')
  {
    char current_char = exp.expected[i];
    if (std::isalpha(current_char))
    {
      in >> Delimeterpair{ current_char };
    }
    else
    {
      in >> Delimeterchar{ current_char };
    }
    ++i;
  }
  return in;
}

std::istream& tellez::operator>>(std::istream& in, Delimeterpair&& exp)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = 0;
    in >> c;
    c = std::tolower(c);
    if (c != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
