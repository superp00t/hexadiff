#ifndef HEXADIFF_H
#define HEXADIFF_H

#include <string>
#include <iostream>
#include <cstdio>
#include <cstdint> 
#include <vector>
#include <sstream>

#define RESET "\033[0m"
#define RED "\033[31m"

// first byte of a 2-byte encoding starts 110 and carries 5 bits of data
#define b2Lead 0xC0 // 1100 0000
#define b2Mask 0x1F // 0001 1111

// first byte of a 3-byte encoding starts 1110 and carries 4 bits of data
#define b3Lead 0xE0 // 1110 0000
#define b3Mask 0x0F // 0000 1111

// first byte of a 4-byte encoding starts 11110 and carries 3 bits of data
#define b4Lead 0xF0 // 1111 0000
#define b4Mask 0x07 // 0000 0111

// non-first bytes start 10 and carry 6 bits of data
#define mbLead 0x80 // 1000 0000
#define mbMask 0x3F // 0011 1111

class UString {
public:
  std::vector<uint32_t> m_glyphs;

  UString(std::string input);
  std::string to_string() const;
  std::uint32_t& operator[](size_t index)
  {
    return m_glyphs[index];
  }
  size_t length()
  {
    return m_glyphs.size();
  }
};

std::ostream & operator<<(std::ostream & os, const UString & ustr)
{
  os << ustr.to_string();
  return os;
}

void viewHex(std::string input_string);
void viewDiff(std::string stre1, std::string stre2);

#endif
