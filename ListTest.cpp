/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA5
 * * ListTest.cpp
 * * Test file for List ADT 
 * *********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
   List L;
   cout << "L length: " << L.length() << endl;

   try {
      cout << "L front: " << L.front() << endl;
   } catch (std::length_error& e) {
      cout << e.what() << endl;
      cout << "   continuing without interruption\n" << endl;
   }
   try {
      cout << "L back: " << L.back() << endl;
   } catch (std::length_error& e) {
      cout << e.what() << endl;
      cout << "   continuing without interruption\n" << endl;
   }
   try {
      cout << "L cursor next: " << L.peekNext() << endl;
   } catch (std::range_error& e) {
      cout << e.what() << endl;
      cout << "   continuing without interruption\n" << endl;
   }
   try {
      cout << "L cursor prev: " << L.peekPrev() << endl;
   } catch (std::range_error& e) {
      cout << e.what() << endl;
      cout << "   continuing without interruption\n" << endl;
   }

   cout << "empty L: " << L.to_string() << endl;
   cout << "inserted 3 and 2 after cursor, inserted 1 before cursor" << endl;
   L.insertAfter(3);
   L.insertBefore(1);
   L.insertAfter(2);
   int moveover = L.moveNext();
   cout << "moved over " << moveover << endl;
   moveover = L.moveNext();
   cout << "moved over " << moveover << "\ninserted 4 after cursor" << endl;
   L.insertAfter(4);
   cout << L.to_string() << endl;

   cout << "L length: " << L.length() << endl;
   cout << "L front: " << L.front() << endl;
   cout << "L back: " << L.back() << endl;
   cout << "L pos_cursor: " << L.position() << endl;

   L.moveFront();
   cout << "\nfindNext tests" << endl;
   int found = L.findNext(3);
   cout << "index of 3? " << found << endl;
   found = L.findNext(69);
   cout << "index of 69? " << found << endl;

   cout << "\nfindPrev tests" << endl;
   found = L.findPrev(1);
   cout << "index of 1? " << found << endl;
   found = L.findPrev(420);
   cout << "index of 420? " << found << endl;

   List copy = List(L);
   cout << "\ncopying List L" << endl;
   cout << "copy = " << copy.to_string() << endl;
   cout << "copy length: " << L.length() << endl;
   cout << "copy front: " << L.front() << endl;
   cout << "copy back: " << L.back() << endl;
   cout << "copy pos_cursor: " << L.position() << endl;

   cout << "concatenating L and copy" << endl;
   cout << "copy = " << copy.to_string();
   cout << "L = " << L.to_string();
   List c = L.concat(copy);
   cout << "L is now: " << c.to_string() << endl;
   
   cout << "\nequals tests" << endl;
   cout << "are " << L.to_string() << " and" << copy.to_string() << " equal?";
   if (L.equals(copy) && L == copy) {
      cout << "yes" << endl;
   } else {
      cout << "nope" << endl;
   }
   
   cout << "are " << L.to_string() << " and" << c.to_string() << " equal? ";
   if (L.equals(c) && L == c) {
      cout << "yes" << endl;
   } else {
      cout << "nope" << endl;
   }

   cout << "L length: " << L.length() << ", c length: " << c.length() << endl;

   L.eraseBefore();
   L.eraseBefore();
   L.eraseBefore();
   L.eraseBefore();
   cout << "erased before 4 times" << endl;
   cout << "L = " << L.to_string() << endl;
   cout << "L length: " << L.length() << endl;
   cout << "L pos_cursor: " << L.position() << endl;
   L.clear();
   cout << "L after clear: " << L.to_string() << endl;

   List cleanupL;
   cleanupL.insertBefore(3);
   cleanupL.insertBefore(1);
   cleanupL.insertBefore(1);
   cleanupL.insertBefore(3);
   cleanupL.insertBefore(2);
   cleanupL.insertAfter(3);
   cleanupL.insertAfter(2);
   cleanupL.insertAfter(1);
   cleanupL.insertAfter(2);

   // assignment operator tests
   List A;
   A = cleanupL;
   cout << "assign L = A -> " << A << endl;

   cout << "\ncleanup tests ------------------------" << endl;

   cout << "cleanup L = " << cleanupL << endl;
   cout << "cleanup L length: " << cleanupL.length() << endl;
   cout << "cleanup L front: " << cleanupL.front() << endl;
   cout << "cleanup L back: " << cleanupL.back() << endl;
   cout << "cleanup L pos_cursor: " << cleanupL.position() << endl;

   cleanupL.cleanup();
   cout << "after cleanup: " << cleanupL << endl;
   cout << "\tlength: " << cleanupL.length() << endl;
   cout << "\tL front: " << cleanupL.front() << endl;
   cout << "\tL back: " << cleanupL.back() << endl;
   cout << "\tL pos_cursor: " << cleanupL.position() << endl;

   cleanupL.moveFront();
   cout << "peekNext cleanup list;" << endl;
   cleanupL.moveFront();
   while (cleanupL.position() < cleanupL.length()) {
      cout << "index: " << cleanupL.position() << " has value: " << cleanupL.peekNext() << endl;
      cleanupL.moveNext();
   }

   cout << "peekPrev cleanup list;" << endl;
   cleanupL.moveBack();
   while (cleanupL.position() > 0) {
      cout << "index: " << cleanupL.position() << " has value: " << cleanupL.peekPrev() << endl;
      cleanupL.movePrev();
   }

   cleanupL.moveFront();
   while (cleanupL.position() < cleanupL.length()) {
      cleanupL.setAfter(0);
      cleanupL.moveNext();
   }
   cout << "set list to all 0s: " << cleanupL << endl;
   cleanupL.moveBack();
   while (cleanupL.position() > 0) {
      cleanupL.setBefore(-1);
      cleanupL.movePrev();
   }
   cout << "set list to all -1s: " << cleanupL << endl;
   cleanupL.eraseAfter();
   cleanupL.eraseAfter();
   cleanupL.eraseAfter();
   cout << "deleting list nodes: " << cleanupL << endl;
   return(EXIT_SUCCESS);
}

