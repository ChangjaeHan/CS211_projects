/*list.h*/

//
// Author: Prof. Hummel, U. of I. Chicago, Spring 2021
// 
// Implements a one-way linked-list with optimized insertion at
// head and tail of list. The nodes contain 2 data values, a string
// and an integer.
//

#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;


class List
{
private:
   class NodeData
   {
   public:
      string  Value1;
      int     Value2;
   };

   class Node
   {
   public:
      NodeData Data;
      Node*    Next;
   };

   //
   // data members:
   //
   Node* Head;
   Node* Tail;
   int   Count;

   //
   // private member functions:
   //
   void initAndDeepCopy(const List& other);  // inits this list then makes deep copy of other
   void freeAndReset();  // free the nodes in this list and then resets to empty

public:
   //
   // default constructor
   //
   // Initializes the list to empty.
   // 
   // Time complexity: O(1)
   //
   List();

   //
   // copy constructor
   //
   // Makes a deep copy of the other list into this list.
   // 
   // Time complexity: O(N)
   //
   List(const List& other); 

   //
   // destructor
   //
   // Frees all memory related to this list, and then resets to empty.
   // 
   // Time complexity: O(N)
   //
   ~List(); 

   //
   // assignment operator (e.g. L2 = L;)
   //
   // Makes a deep copy of the other list into this list; since this
   // list already exists, the existing elements of this list are freed
   // before the copy is made.
   // 
   // Time complexity: O(N)
   //
   List& operator=(const List& other);  

   //
   // size
   //
   // Returns the # of elements in the list.
   //
   // Time complexity: O(1)
   //
   int size();

   //
   // empty
   //
   // Returns true if empty, false if not.
   //
   // Time complexity: O(1)
   //
   bool empty();

   //
   // search
   //
   // Search the list for the first occurence of the string value.
   // If found, its position in the list is returned. Positions are 
   // 0-based, meaning the first node is position 0. If the value is
   // not found, -1 is returned.
   //
   // Time complexity: on average O(N)
   //
   int search(string value);

   //
   // retrieve
   //
   // Retrieve's the data from node at the given position; the list 
   // remains unchanged. Positions are 0-based, meaning the first node
   // is position 0. Throws an "invalid_argument" exception if the 
   // position is invalid, i.e. 
   // throw invalid_argument("List::retrieve: invalid position");
   //
   // Time complexity: on average O(N)
   //
   void retrieve(int pos, string& value1, int& value2);

   //
   // insert
   //
   // Inserts the given data in the list such that after
   // the insertion, the value is now at the given
   // position.
   //
   // Positions are 0-based, which means a position of 0 
   // denotes the data will end up at the head of the list,
   // and a position of N (where N = the size of the list)
   // denotes the data will end up at the tail of the list.
   // If the position is invalid, throws an exception, i.e.
   // throw invalid_argument("List::insert: invalid position");
   //
   // Time complexity: on average O(N)
   //
   void insert(int pos, string value1, int value2);

   //
   // remove
   //
   // Removes and deletes the node at the given position; no data is
   // returned. Positions are 0-based, meaning the first node
   // is position 0. Throws an "invalid_argument" exception if the 
   // position is invalid, i.e. 
   // throw invalid_argument("List::remove: invalid position");
   //
   // Time complexity: on average O(N)
   //
   void remove(int pos);

   //
   // front
   //
   // Returns the data from the first node in the list. Throws an 
   // exception if the list is empty, i.e.
   // throw runtime_error("List::front: empty list");
   // 
   // Time complexity: O(1)
   //
   void front(string& value1, int& value2);

   //
   // back
   //
   // Returns the data from the last node in the list. Throws an 
   // exception if the list is empty, i.e.
   // throw runtime_error("List::back: empty list");
   // 
   // Time complexity: O(1)
   //
   void back(string& value1, int& value2);

   //
   // push_front
   //
   // Inserts the given data at the front of the list.
   // 
   // Time complexity: O(1)
   //
   void push_front(string value1, int value2);

   //
   // push_back
   //
   // Inserts the given data at the back of the list.
   // 
   // Time complexity: O(1)
   //
   void push_back(string value1, int value2);
   
};
