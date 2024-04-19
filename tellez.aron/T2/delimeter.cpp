#include "delimeter.hpp"

std::istream& tellez::operator>>(std::istream& in, Delimeterchar&& exp)
{
  std::istream::sentry guard(in);
  char current_char = 0;
  in >> current_char;
  if (current_char != exp.expected)
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
    if (std::isalpha(exp.expected[i]))
    {
      in >> Delimeterpair{ exp.expected[i++] };
    }
    else
    {
      in >> Delimeterchar{ exp.expected[i++] };
    }
  }
  return in;
}

std::istream& tellez::operator>>(std::istream& in, Delimeterpair&& exp)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char current_char = 0;
    in >> current_char;
    current_char = std::tolower(c);
    if (current_char != exp.expected)
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}
