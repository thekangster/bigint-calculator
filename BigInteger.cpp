/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA6
 * * BigInteger.cpp
 * * Implementation file for BigInteger ADT 
 * *********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

const long base = 1000000000;
const int power = 9;

BigInteger::BigInteger() {
   signum = 0;
   digits.clear();
}

BigInteger::BigInteger(std::string s) {
   long n;
   char c = s.front();
   int start = 1;
   std::size_t invalid = s.find_last_not_of("0123456789");
   if (s.empty()) {
      throw std::invalid_argument("BigInteger: Constructor: empty string");
   }
   if (invalid != std::string::npos && invalid > 0) {
      throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   }
   if (s.length() == 1) {
      if (c == '+') {
         throw std::invalid_argument("Big Integer: Constructor: non-numeric string");
      } else if (c == '-') {
         throw std::invalid_argument("Big Integer: Constructor: non-numeric string");
      }
   }
   if (c == '-') {
      signum = -1;
   } else if (c == '+') {
      signum = 1;
   } else if (c == '0' && s.length() == 1) {
      signum = 0;
   } else {
      signum = 1;
      start = 0;
   }
   if (s[start] == '0') {
      while (s[start] == '0') {
         start++;
      }
   }

   int remainder = (s.length()-start) % power;
   for (int i = s.length(); i > start; i=i-power) {
      try {
         n = std::stol(s.substr(i-power, power), nullptr, 10);
      } catch (std::out_of_range&) {
         n = std::stol(s.substr(start, remainder), nullptr, 10);
      }
      if (n < 0) {
         digits.insertAfter(-1 * n);
      } else {
         digits.insertAfter(n);
      }
   }
   //std::cout << "list: " << digits << endl;
}

BigInteger::BigInteger(const BigInteger& N) {
   signum = N.signum;
   digits = List(N.digits);
}

int BigInteger::sign() const {
   return signum;
}

int BigInteger::compare(const BigInteger& N) const {
   if (this->signum > N.signum) {
      return 1;
   } else if (N.signum > this->signum) {
      return -1;
   } else if (this->signum == 0 && N.signum == 0) {
      return 0;
   }
   List thiscopy = List(this->digits);
   List Ncopy = List(N.digits);
   if (thiscopy.length() > Ncopy.length()) {
      return 1;
   } else if (thiscopy.length() < Ncopy.length()) {
      return -1;
   } else {
      thiscopy.moveFront();
      Ncopy.moveFront();
      while (thiscopy.position() < Ncopy.length()) {
         long this_msd = thiscopy.moveNext();
         long N_msd = Ncopy.moveNext();
         if (this_msd > N_msd) {
            return 1;
         } else if (N_msd > this_msd) {
            return -1;
         } else {
            continue;
         }
      }
   }
   return 0;
}

void BigInteger::makeZero() {
   digits.clear();
   signum = 0;
}

void BigInteger::negate() {
   if (signum == 1) {
      signum = -1;
   } else if (signum == -1) {
      signum = 1;
   }
}

void negateList(List& L) {
   L.moveFront();
   while (L.position() < L.length()) {
      L.setAfter(-1 * L.peekNext());
      L.moveNext();
   }
   L.moveFront();
}

int normalize(List& L) {
   ListElement num;
   int carry = 0;
   int sign = 1;
   if (L.length() == 0) {
      return 0;
   } else if (L.front() < 0) {
      sign = -1;
      negateList(L);
      normalize(L);
   } else {
      L.moveBack();
      while (L.position() > 0) {
         num = L.peekPrev();
         if (num < 0) {
            num += base + carry;
            L.setBefore(num);
            carry = -1;
         } else {
            num = L.peekPrev();
            num += carry;
            carry = 0;
            if (num >= base) {
               carry = num / base;
               num = num % base;
            }
            L.setBefore(num);
         }
         if (L.position() == 1 && carry != 0) {
            L.moveFront();
            L.insertAfter(carry);
            break;
         }
         L.movePrev();
      }
   }
   return sign;
}

void sumList(List& S, List A, List B, int sign) {
   S.clear();
   ListElement a, b;
   A.moveBack();
   B.moveBack();
   while (A.position() > 0 && B.position() > 0) {
      a = A.peekPrev();
      b = B.peekPrev();
      S.insertAfter(a + (sign * b));
      A.movePrev();
      B.movePrev();
   }
   while (A.position() > 0) {
      a = A.peekPrev();
      S.insertAfter(a);
      A.movePrev();
   }
   while (B.position() > 0) {
      b = B.peekPrev();
      S.insertAfter(sign * b);
      B.movePrev();
   }
}

BigInteger BigInteger::add(const BigInteger& N) const {
   BigInteger sum;
   List sum_list;
   
   BigInteger thiscopy = BigInteger(*this);
   BigInteger Ncopy = BigInteger(N);
   if (thiscopy.digits.length() == 0 && Ncopy.digits.length() == 0) {
      return sum;
   }

   if (this->signum == N.signum) {
      sumList(sum_list, thiscopy.digits, Ncopy.digits, 1);
      sum.signum = this->signum;
   } else {
      if (this->signum == 1) {
         sumList(sum_list, thiscopy.digits, Ncopy.digits, -1);
      } else if (Ncopy.signum == 1) {
         sumList(sum_list, Ncopy.digits, thiscopy.digits, -1);
      } else {
         sumList(sum_list, thiscopy.digits, Ncopy.digits, -1);
      }
      sum_list.moveFront();
      while (sum_list.length() > 1 && sum_list.front() == 0) {
         sum_list.eraseAfter();
      }
      //cout << "before normalize = " << sum_list << endl;
      if (sum_list.front() < 0) {
         sum.signum = -1;
      } else if (sum_list.front() > 0) {
         sum.signum = 1;
      }
      /*
      if (this->signum == 1) {
         Ncopy.negate();
         if (thiscopy.compare(Ncopy) == 1) {
            sum.signum = 1;
         } else if (thiscopy.compare(Ncopy) == -1) {
            sum.signum = -1;
         }
      } else if (this->signum == -1) {
         thiscopy.negate();
         if (Ncopy.compare(thiscopy) == 1) {
            sum.signum = 1;
         } else if (Ncopy.compare(thiscopy) == -1) {
            sum.signum = -1;
         }
      } else {
         if (Ncopy.signum == 1) {
            sum.signum = 1;
         } else if (Ncopy.signum == -1) {
            sum.signum = -1;
         } else if (Ncopy.signum == 0) {
            sum.signum = 0;
         }
      }
      */
   }
   if (sum.digits.length() > 0 && sum.digits.front() < 0) {
      sum.digits.moveFront();
      sum.digits.setAfter(-1 * sum.digits.front());
   }
   
   
   normalize(sum_list);
   /*
   cout << "\n after normalize = " << sum_list << endl;
   if (sum_list.front() > 0) {
      cout << "signum should be 1" << endl;
   } else {
      cout << "signum should not be 1" << endl;
   }
   cout << "signum = " << sum.signum << endl;
   */
   sum.digits = sum_list;
   return sum;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
   BigInteger thiscopy = BigInteger(*this);
   BigInteger Ncopy = BigInteger(N);
   Ncopy.negate();
   return thiscopy.add(Ncopy);
}

List scalarMultList(List L, ListElement m) {
   List SM;
   L.moveFront();
   while (L.position() < L.length()) {
      ListElement x = L.moveNext();
      SM.insertBefore(m * x);
   }
   return SM;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
   BigInteger scalarMult;
   BigInteger product;
   BigInteger A;
   BigInteger B;
   ListElement b;

   if (this->digits.length() > N.digits.length()) {
      A = BigInteger(*this);
      B = BigInteger(N);
   } else {
      A = BigInteger(N);
      B = BigInteger(*this);
   }

   B.digits.moveBack();
   for (int i = 0; i < B.digits.length(); i++) {
      scalarMult.digits.clear();
      if (B.digits.position() > 0) {
         b = B.digits.movePrev();
         scalarMult.signum = A.signum;
         scalarMult.digits = scalarMultList(A.digits, b);
      }
      for (int j = 0; j < i; j++) {
         scalarMult.digits.moveBack();
         scalarMult.digits.insertAfter(0);
      }
      product = product.add(scalarMult);
   }
   product.signum = A.signum * B.signum;
   return product;
}

std::string BigInteger::to_string() {
   std::string s = "";
   if (signum == 0) {
      return "0";
   } else if (signum == -1) {
      s += "-";
   }
   
   digits.moveFront();
   while (digits.position() < digits.length()) {
      long N = digits.moveNext();
      std::string n = std::to_string(N);
      int nlen = n.length();
      if (digits.position() != 1) {
         while (nlen < power) {
            n.insert(0, "0");
            nlen = n.length();
         }
      }
      s += n;
   }
   digits.moveFront();
   //std::cout << digits << std::endl;
   return s;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
   stream << N.to_string();
   return stream;
}

bool operator==( const BigInteger& A, const BigInteger& B ) {
   if (A.digits.List::equals(B.digits) && A.signum == B.signum) {
      return true;
   }
   return false;
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
   if (B.compare(A) == 1) {
      return true;
   }
   return false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
   if (B.compare(A) == 1 || B.compare(A) == 0) {
      return true;
   }
   return false;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
   if (A.compare(B) == 1) {
      return true;
   }
   return false;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
   if (A.compare(B) == 1 || A.compare(B) == 0) {
      return true;
   }
   return false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
   return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
   A = A.add(B);
   return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
   return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
   A = A.sub(B);
   return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
   return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
   A = A.mult(B);
   return A;
}

