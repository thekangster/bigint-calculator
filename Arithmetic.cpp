/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA6
 * * BigIntegerTest.cpp
 * * Test file for BigInteger ADT 
 * *********************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(int argc, char **argv) {
   ifstream in;
   ofstream out;
   string line;
   int linecount = 0;
   BigInteger A;
   BigInteger B;

   if (argc != 3) {
      cerr << "Usage: " << argv[0] << "<input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   in.open(argv[1]);
   if (!in.is_open()) {
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }
   out.open(argv[2]);
   if (!out.is_open()) {
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   
   while (getline(in, line)) {
      linecount++;
      if (linecount == 1) {
         A = BigInteger {line};
      } else if (linecount == 3) {
         B = BigInteger {line};
      }
   }
  /* 
   cout << "A string: " << A << endl;
   cout << "B string: " << B << endl;
   cout << A+B << endl;
*/
   out << A << endl << endl;
   out << B << endl << endl;
   out << A + B << endl << endl;
   out << A - B << endl << endl;
   out << A - A << endl << endl;
   out << BigInteger {"3"} * A - BigInteger {"2"} * B << endl << endl;
   out << A * B << endl << endl;
   out << A * A << endl << endl;
   out << B * B << endl << endl;
   out << BigInteger {"9"} * (A * A * A * A) + BigInteger{"16"} * (B * B * B * B * B) << endl << endl;
   in.close();
   out.close();
   return(EXIT_SUCCESS);
}
