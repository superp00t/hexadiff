/*
hexadiff: a command line utility for detecting homographical attacks i.e. unicode abuse.
*/

#include "hexadiff.h"

using namespace std;

#define readByte(ptr) ptr = *input++; 

uint32_t readGlyph(uint8_t *input, size_t &offset)
{
   uint8_t header, b1, b2, b3;

   readByte(header);

   if (header < mbLead)
   {
      offset++;
      return header;
   }

   if (header < b3Lead)
   {
      offset += 2;
      readByte(b1);
      return (uint32_t)(header & b2Mask) << 6 | (uint32_t)(b1 & mbMask);
   }

   if (header < b4Lead)
   {
      offset += 3;
      readByte(b1);
      readByte(b2);
      return (uint32_t)(header & b3Mask) << 12 | (uint32_t)(b1 & mbMask) << 6 | (uint32_t)(b2 & mbMask);
   }

   offset += 4;
   readByte(b1);
   readByte(b2);
   readByte(b3);

   return (uint32_t)(header & b4Mask) << 18 | (uint32_t)(b1 & mbMask) << 12 | (uint32_t)(b2 & mbMask) << 6 | (uint32_t)(b3 & mbMask);
}

UString::UString(string inputString) : m_glyphs()
{
   uint32_t glyph = 0;
   size_t   offset = 0;

   while (offset < inputString.length())
   {
      uint8_t *readAddr = (uint8_t *)inputString.c_str() + offset;
      m_glyphs.push_back(readGlyph(readAddr, offset));
   }
}

void writeGlyph(uint32_t glyph, string& output)
{
   if (glyph < mbLead)
   {
      output.push_back((char)glyph);
      return;
   }
   else if (glyph <= 1 << 11 - 1)
   {
      output.push_back(b2Lead | (char)glyph >> 6);
      output.push_back(mbLead | (char)glyph & mbMask);
   }
   else if (glyph <= 1 << 16 - 1)
   {
      output.push_back(b3Lead | (char)glyph >> 12);
      output.push_back(mbLead | (char)glyph >> 6 & mbMask);
      output.push_back(mbLead | ((char)glyph) & mbMask);
   }
   else
   {
      output.push_back(b4Lead | (char)glyph >> 16);
      output.push_back(mbLead | ((char)glyph >> 12) & mbMask);
      output.push_back(mbLead | ((char)glyph >> 6) & mbMask);
      output.push_back(mbLead | ((char)glyph) & mbMask);
   }
}

string UString::to_string() const
{
   string output;

   for (auto glyph : m_glyphs)
      writeGlyph(glyph, output);

   return output;
}

void viewHex(UString input_string)
{
   cout << input_string << " --> ";
   for (int x = 0; x < input_string.length(); x++)
   {
      cout << "0x" << hex << input_string[x] << " ";
   }
   cout << endl;
}

void viewDiff(UString stre1, UString stre2)
{
   viewHex(stre1);
   cout << stre2 << " --> ";
   for (int x = 0; x < stre2.length(); x++)
   {
      if (stre1[x] != stre2[x])
      {
         cout << RED;
         cout << "0x" << hex << stre2[x];
         cout << RESET;
      }
      else
      {
         cout << "0x" << hex << stre2[x];
      }
      cout << " ";
   }
   cout << endl;
}

int main(int argc, char *argv[])
{
   setbuf(stdout, nullptr);
   int minp = argc - 1;
   if (minp == 1)
   {
      viewHex(UString(argv[1]));
   }
   else if (minp == 2)
   {
      viewDiff(UString(argv[1]), UString(argv[2]));
   }
}
