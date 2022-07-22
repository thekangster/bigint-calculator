/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA6
 * * BigIntegerTest.cpp
 * * Test file for BigInteger ADT 
 * *********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main() {

   cout << "string constructor tests----------------------------------" << endl;
   try {
      BigInteger e1{"1234567891234567891234"};
      cout << "bigint: " << e1 << "\n\tsign: " << e1.sign() << endl;
   } catch (std::invalid_argument& e1) {
      cout << e1.what() << endl;
   }
   try {
      BigInteger test = BigInteger("1+0000123456789123456789");
      cout << "bigint: " << test << "\n\tsign: " << test.sign() << endl;
   } catch (std::invalid_argument& e1) {
      cout << e1.what() << endl;
   }
   try {
      BigInteger e1 = BigInteger("-0041085449");
      BigInteger copy = BigInteger(e1);
      cout << "bigint: " << copy << "\n\tsign: " << copy.sign() << endl;
   } catch (std::invalid_argument& e1) {
      cout << e1.what() << endl;
   }
   try {
      string s = "";
      BigInteger e2 = BigInteger(s);
   } catch (std::invalid_argument& e2) {
      cout << e2.what() << endl;
   }
   try {
      BigInteger e3 = BigInteger("+");
   } catch (std::invalid_argument& e3) {
      cout << e3.what() << endl;
   }
   try {
      BigInteger e3 = BigInteger("0");
      cout << "bigint: " << e3 << "\n\tsign: " << e3.sign() << endl;
   } catch (std::invalid_argument& e3) {
      cout << e3.what() << endl;
   }
   try {
      BigInteger e4 = BigInteger("-123456");
      cout << "bigint: " << e4 << "\n\tsign: " << e4.sign() << endl;
   } catch (std::invalid_argument& e4) {
      cout << e4.what() << endl;
   }
   try {
      BigInteger e4 = BigInteger("+654321");
      cout << "bigint: " << e4 << "\n\tsign: " << e4.sign() << endl;
      e4.negate();
      cout << "bigint: " << e4 << "\n\tsign: " << e4.sign() << endl;
   } catch (std::invalid_argument& e5) {
      cout << e5.what() << endl;
   }
   try {
      BigInteger test1 = BigInteger("-1+5"); 
      cout << "bigint: " << test1 << "\n\tsign: " << test1.sign() << endl;
   } catch (std::invalid_argument& e6) {
      cout << e6.what() << endl;
   }
   try {
      BigInteger test1 = BigInteger("6523485630758234007488392857982374523487612398700554");
      cout << "bigint: " << test1 << "\n\tsign: " << test1.sign() << endl;
   } catch (std::invalid_argument& e7) {
      cout << e7.what() << endl;
   }
   cout << "\ncompare tests---------------------------------------------" << endl;
   BigInteger compare1 {"2234"};
   BigInteger compare2 {"1235"};
   if (compare1.compare(compare2) == 1) {
      cout << "i will go to the party because ";
      cout << compare1 << " is bigger than " << compare2 << endl;
   } else {
      cout << "NO PARTY TODAY" << endl;
   }
   BigInteger compare3 {"1234"};
   BigInteger compare4 {"1235"};
   if (compare3.compare(compare4) == -1) {
      cout << "i will go to the party because ";
      cout << compare3 << " is smaller than " << compare4 << endl;
   } else {
      cout << compare3.compare(compare4) << " NO PARTY TODAY" << endl;
   }
   compare4.makeZero();
   if (compare4.compare(compare3) == -1) {
      cout << "i will go to the party because ";
      cout << compare4 << " is smaller than " << compare3 << endl;
   } else {
      cout << "NO PARTY TODAY" << endl;
   }
   if (compare4.compare(compare4) == 0) {
      cout << "i will go to the party because ";
      cout << compare4 << " is equal to " << compare4 << endl;
   } else {
      cout << "NO PARTY TODAY" << endl;
   }

   cout << "\nadd tests-------------------------------------------" << endl;
   BigInteger A {"882133"};
   BigInteger B {"659179"};
   cout << A << " + " << B << " = " << A.add(B) << endl;
   
   A = BigInteger {"149082"};
   B = BigInteger {"-355797"};
   cout << A << " + " << B << " = " << A.add(B) << endl;
   
   A = BigInteger {"355797"};
   B = BigInteger {"-149082"};
   cout << A << " + " << B << " = " << A.add(B) << endl;
   
   A = BigInteger {"-355797"};
   B = BigInteger {"149082"};
   cout << A << " + " << B << " = " << A.add(B) << endl;
   
   A = BigInteger {"-149082"};
   B = BigInteger {"355797"};
   cout << A << " + " << B << " = " << A.add(B) << endl;
   
   cout << "\nstarting sub tests-------------------------------------" << endl;
   A = BigInteger {"882133"};
   B = BigInteger {"659179"};
   cout << A << " - " << B << " = " << A.sub(B) << endl;
   
   A = BigInteger {"149082"};
   B = BigInteger {"-355797"};
   cout << A << " - " << B << " = " << A.sub(B) << endl;
   
   A = BigInteger {"355797"};
   B = BigInteger {"-149082"};
   cout << A << " - " << B << " = " << A.sub(B) << endl;
   
   A = BigInteger {"-355797"};
   B = BigInteger {"149082"};
   cout << A << " - " << B << " = " << A.sub(B) << endl;
   
   A = BigInteger {"-149082"};
   B = BigInteger {"355797"};
   cout << A << " - " << B << " = " << A.sub(B) << endl;

   A = BigInteger {"0"};
   B = BigInteger {"355797"};
   cout << A << " - " << B << " = " << A.sub(B) << endl;

   BigInteger testinglol;
   B = BigInteger {"998001"};
   cout << testinglol << " + " << B << " = " << testinglol.add(B) << endl;
   
   A = BigInteger {"0355797"};
   B = BigInteger {"0"};
   cout << A << " - " << B << " = " << A.sub(B) << endl;

   A = BigInteger {"0355797"};
   BigInteger H;
   cout << A << " + " << H << " = " << A.add(H) << endl;

   cout << "\noverload operator tests-------------------------------" << endl;
   A = BigInteger {"99"};
   B = BigInteger {"999"};
   if (!(A == B) && A < B && A <= B) {
      cout << A << " is less than or equal to " << B << endl;
   } else {
      cout << A << " is not less than or equal to " << B << endl;
   }
   A = BigInteger {"999"};
   B = BigInteger {"99"};
   if (!(A == B) && A > B && A >= B) {
      cout << A << " is greater than or equal to " << B << endl;
   } else {
      cout << A << " is not greater than or equal to " << B << endl;
   }

   A = BigInteger {"10"};
   B = BigInteger {"20"};
   cout << "+++" << endl;
   cout << "A: " << A << endl;
   cout << "B: " << B << endl;
   cout << "A" << " += " << "B" << " = ";
   A += B;
   cout << A << endl;
   cout << "A + B = " << A+B << endl;
   
   cout << "---" << endl;
   A = BigInteger {"10"};
   B = BigInteger {"20"};
   cout << "A: " << A << endl;
   cout << "B: " << B << endl;
   cout << "A" << " -= " << "B" << " = ";
   A -= B;
   cout << A << endl;
   cout << "A - B = " << A-B << endl;
   
   cout << "***" << endl;
   A = BigInteger {"10"};
   B = BigInteger {"20"};
   cout << "A: " << A << endl;
   cout << "B: " << B << endl;
   cout << "A" << " *= " << "B" << " = ";
   A *= B;
   cout << A << endl;

   cout << "\nmult tests--------------------------------------" << endl;
   A = BigInteger {"999"};
   B = BigInteger {"999"};
   cout << A << " * " << B << " = " << A.mult(B) << endl;

   cout << "\ngrading script stuff----------------------------------" << endl;
   A = BigInteger("+111122223333");
   B = BigInteger("-111122223333");
   B = BigInteger("-110122223333");
   BigInteger D = BigInteger("1000000000");
   BigInteger C = A + B;
   cout << A << " + " << B << " = " << C << endl;
   cout << C << " must be equal to " << D << endl;
   if (!(C == D)) {
      cout << "you failed" << endl;
   }

   A = BigInteger("111122223333");
   B = BigInteger("111122223333");
   C = BigInteger();
   D = BigInteger("12348148518469129628889"); 
   
   cout << endl << A << " * " << B << " = ";
   C = A * B;
   cout << endl << "what i got: " << C << endl;
   cout << " should be: " << D << endl << endl;

   B.negate();
   D.negate();
   C = A * B;
   if (C.sign() != -1) {
      cout << "C's sign: " << C.sign() << endl;
      cout << "i have lost" << endl;
   } else {
      cout << "C's sign: " << C.sign() << endl;
      cout << "i have won" << endl;
   }
   if (!(C == D)) {
      cout << "i have lost" << endl;
   } else { 
      cout << "i have won" << endl;
   }

   BigInteger Atest = BigInteger{"-41085449"};
   cout << " after A constructor" << endl;
   BigInteger Btest = BigInteger{"6402779357"};
   cout << " after B constructor" << endl;
   cout << Atest << " + " << Btest << " = " << Atest+Btest << endl;




   /*
   // scalarMultList tests

   List t1;
   t1.insertAfter(8);
   t1.insertAfter(2);
   t1.insertAfter(1);
   cout << t1 << endl;
   List t2;
   t2 = testingSM(t1, 2);
   cout << t2 << endl;

   cout << "\nnormalize tests----------------------------------" << endl;
   List Ntest;
   Ntest.insertAfter(-15);
   Ntest.insertAfter(33);
   Ntest.insertAfter(-21);

   cout << "normalized " << Ntest << " is "; 
   if (normalize(Ntest) == -1) {
      cout << "negative " << Ntest << endl;
   } else {
      cout << "positive " << Ntest << endl;
   }
   Ntest.clear();
   Ntest.insertAfter(-46);
   Ntest.insertAfter(-70);
   Ntest.insertAfter(23);
   cout << "normalized " << Ntest << " is "; 
   if (normalize(Ntest) == -1) {
      cout << "negative " << Ntest << endl;
   } else {
      cout << "positive " << Ntest << endl;
   }

   cout << "\nsumList tests----------------------------------" << endl;
   List sumtest;
   List listA;
   List listB;
   sumtest.insertBefore(-69);
   
   listA.insertBefore(88);
   listA.insertBefore(21);
   listA.insertBefore(33);
   listB.insertBefore(65);
   listB.insertBefore(91);
   listB.insertBefore(79);
   
   sumList(sumtest, listA, listB, 1);
   cout << listA << " + " << listB << " = " << normalize(sumtest) << sumtest << endl;
   sumList(sumtest, listA, listB, -1);
   cout << listA << " - " << listB << " = " << normalize(sumtest) << sumtest << endl;

   listA.insertBefore(5);
   listA.insertBefore(6);
   listA.insertBefore(7);
   sumList(sumtest, listA, listB, 1);
   cout << listA << " + " << listB << " = " << sumtest << endl;
   sumList(sumtest, listA, listB, 1);
   cout << listA << " - " << listB << " = " << sumtest << endl;
   */
   return(EXIT_SUCCESS);
}
