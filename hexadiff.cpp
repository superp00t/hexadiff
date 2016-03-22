/*
hexadiff: a command line utility for detecting homographical attacks i.e. unicode abuse.
*/

#include <iostream>
#include <string>
#include <cstdio>

#define RESET   "\033[0m"
#define RED     "\033[31m"

using namespace std;

void hexadec(string input_string) {
   cout << input_string << " --> ";
   for (int x = 0; x < input_string.length(); x++) {
	  printf("0x%x ", input_string[x]);
   }
   cout << endl;
}

void diff(string stre1, string stre2) {
   hexadec(stre1);
   cout << stre2 << " --> ";
   for (int x = 0; x < stre2.length(); x++) {
	  if (stre1[x] != stre2[x]) {
		 cout << RED;
		 printf("0x%x ", stre2[x]);
		 cout << RESET;
	  }
	  else {
		 printf("0x%x ", stre2[x]);
	  }
   }
   cout << endl;
}

int main(int argc, char *argv[]) {
   int minp = argc - 1;
   if (minp == 1) {
	  hexadec(argv[1]);
   }
   else if (minp == 2) {
	  diff(argv[1], argv[2]);
   }
}

