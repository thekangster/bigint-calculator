/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA6
 * * List.cpp
 * * Implementation file for List ADT 
 * *********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor

// Node constructor
List::Node::Node(ListElement x) {
   data = x;
   next = prev = nullptr;
}

// Class Constructors & Destructors

// Creates a new List in the empty state
List::List() {
   frontDummy = new Node(133769);
   backDummy = new Node(691337);
   frontDummy->prev = backDummy;
   backDummy->next = frontDummy;

   beforeCursor = frontDummy;
   afterCursor = backDummy;

   pos_cursor = 0;
   num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
   frontDummy = new Node(133769);
   backDummy = new Node(691337);
   frontDummy->prev = backDummy;
   backDummy->next = frontDummy;

   beforeCursor = frontDummy;
   afterCursor = backDummy;

   pos_cursor = 0;
   num_elements = 0;

   if (L.length() != 0) {
      Node* N = nullptr;
      for (N = L.frontDummy->next; N != L.backDummy; N = N->next) {
         insertBefore(N->data);
      }
   }
   moveFront();
}

List::~List() {
   clear();
   delete frontDummy;
   delete backDummy;
}

int List::length() const {
   return num_elements;
}

ListElement List::front() const {
   if (length() == 0) {
      throw std::length_error("List: front(): empty List");
   }
   return frontDummy->next->data;
}

ListElement List::back() const {
   if (length() == 0) {
      throw std::length_error("List: back(): empty List");
   }
   return backDummy->prev->data;
}

int List::position() const {
   return pos_cursor;
}
   
ListElement List::peekNext() const {
   if (pos_cursor >= length()) {
      throw std::range_error("List: peekNext(): pos_cursor is at end of list");
   }
   return afterCursor->data;
}

ListElement List::peekPrev() const {
   if (pos_cursor == 0) {
      throw std::range_error("List: peekPrev(): pos_cursor is at start of list");
   }
   return beforeCursor->data;
}

void List::clear() {
   moveFront();
   while (length() > 0) {
      eraseAfter();
   }
}

void List::moveFront() {
   if (length() == 0) {
      afterCursor = backDummy;
      beforeCursor = frontDummy;
   } else {
      afterCursor = frontDummy->next;
      beforeCursor = frontDummy;
   }
   pos_cursor = 0;
}

void List::moveBack() {
   if (length() == 0) {
      afterCursor = backDummy;
      beforeCursor = frontDummy;
   } else {
      afterCursor = backDummy;
      beforeCursor = backDummy->prev;
   }
   pos_cursor = length();
}

ListElement List::moveNext() {
   if (position() >= length()) {
      throw std::range_error("List: moveNext(): pos_cursor is at end of list");
   }
   Node* temp = afterCursor;
   afterCursor = afterCursor->next;
   beforeCursor = temp;
   pos_cursor++;
   return temp->data;
}

ListElement List::movePrev() {
   if (position() == 0) {
      throw std::range_error("List: movePrev(): pos_cursor is at start of list");
   }
   Node* temp = beforeCursor;
   beforeCursor = beforeCursor->prev;
   afterCursor = temp;
   pos_cursor--;
   return temp->data;
}

void List::insertAfter(ListElement x) {
   Node* N = new Node(x);
   N->next = afterCursor;
   N->prev = beforeCursor;
   beforeCursor->next = N;
   afterCursor->prev = N;
   afterCursor = N;
   num_elements++;
}

void List::insertBefore(ListElement x) {
   Node* N = new Node(x);
   N->next = afterCursor;
   N->prev = beforeCursor;
   beforeCursor->next = N;
   afterCursor->prev = N;
   beforeCursor = N;
   num_elements++;
   pos_cursor++;
}

void List::setAfter(ListElement x) {
   if (position() >= length()) {
      throw std::range_error("List: setAfter(): pos_cursor is at end of list"); 
   }
   afterCursor->data = x;
}

void List::setBefore(ListElement x) {
   if (position() == 0) {
      throw std::range_error("List: setBefore(): pos_cursor is at start of list"); 
   }
   beforeCursor->data = x;
}

void List::eraseAfter() {
   if (length() > 0 && pos_cursor < length()) {
      Node* N = afterCursor;
      afterCursor = afterCursor->next;
      beforeCursor->next = afterCursor;
      afterCursor->prev = beforeCursor;
      num_elements--;
      delete N;
   }
}

void List::eraseBefore() {
   if (length() > 0 && pos_cursor > 0) {
      Node* N = beforeCursor;
      beforeCursor = beforeCursor->prev;
      afterCursor->prev = beforeCursor;
      beforeCursor->next = afterCursor;
      num_elements--;
      pos_cursor--;
      delete N;
   }
}

int List::findNext(ListElement x) {
   ListElement find;
   if (pos_cursor < length()) {
      find = moveNext();
   } else {
      return -1;
   }

   while (find != x && pos_cursor < length()) {
      find = moveNext();
      if (find == x) {
         return pos_cursor;
      }
   }
   return -1;
}

int List::findPrev(ListElement x) {
   ListElement find;
   if (pos_cursor > 0) {
      find = movePrev();
   } else {
      return -1;
   }
   while (find != x && pos_cursor > 0) {
      find = movePrev();
      if (find == x) {
         return pos_cursor;
      }
   }
   return -1;
}

void List::cleanup() {
   int inner_node;
   int outer = 0;
   Node* ptr1 = frontDummy->next;
   Node* ptr2;
   Node* nextN;
   while (ptr1 != backDummy) {
      ptr2 = ptr1->next;
      inner_node = outer+1;
      while (ptr2 != backDummy) {
         if (ptr1->data == ptr2->data) {
            if (ptr2 == beforeCursor) {
               beforeCursor = beforeCursor->prev;
            }
            if (ptr2 == afterCursor) {
               afterCursor = afterCursor->next;
            }
            if (inner_node < pos_cursor) {
               inner_node--;
               pos_cursor--;
            }
            nextN = ptr2->next;
            ptr2->prev->next = ptr2->next;
            ptr2->next->prev = ptr2->prev;
            delete ptr2;
            num_elements--;
         } else {
            nextN = ptr2->next;
         }
         ptr2 = nextN;
         inner_node++;
      }
      ptr1 = ptr1->next;
      outer++;
   }
}

List List::concat(const List& L) const {
   List C;
   Node* N = this->frontDummy->next;
   Node* M = L.frontDummy->next;
   while (N != this->backDummy) {
      C.insertBefore(N->data);
      N = N->next;
   }
   while (M != L.backDummy) {
      C.insertBefore(M->data);
      M = M->next;
   }
   C.moveFront();
   return C;
}

std::string List::to_string() const {
   Node* N = nullptr;
   std::string s = "(";

   if (length() == 0) {
      return "()";
   }
   
   for (N = frontDummy->next; N != backDummy; N = N->next) {
      if (N->next != backDummy) {
         s += std::to_string(N->data)+", ";
      } else {
         s += std::to_string(N->data)+")";
      }
   }
   return s;
}

bool List::equals(const List& R) const {
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = this->num_elements == R.num_elements;
   N = this->frontDummy->next;
   M = R.frontDummy->next;
   while (eq && N != backDummy) {
      eq = N->data == M->data;
      N = N->next;
      M = M->next;
   }
   return eq;
}

std::ostream& operator<<( std::ostream& stream, const List& L ) {
   stream << L.to_string();
   return stream;
}

bool operator==( const List& A, const List& B ) {
   return A.equals(B);
}

List& List::operator=( const List& L ) {
   if (this != &L) {
      List temp = L;

      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
   }
   return *this;
}

