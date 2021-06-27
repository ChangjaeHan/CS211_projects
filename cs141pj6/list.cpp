/*list.cpp*/

//
// Author: Changjae Han, U. of I. Chicago, Spring 2021
// 
// Implements a one-way linked-list with optimized insertion at
// head and tail of list. The nodes contain 2 data values, a string
// and an integer.
//

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>


#include "list.h"


using namespace std;



//
// private member functions:
//

//
// inits this list then makes deep copy of other
//
// Time complexity: O(N)
//
void List::initAndDeepCopy(const List& other)
{
 
    this->Head = nullptr;
    this->Count = 0;
    
    Node* cur = other.Head;  //point to other
    
    while (cur!= nullptr) // loop to duplicate list
    {        
      
       string Value1 = cur->Data.Value1; 
       int Value2 = cur->Data.Value2;
        
       this->push_back(Value1, Value2); // duplicate 
        
       cur = cur->Next;
    }  
}


// 
// free the nodes in the list and resets to empty
//
// Time complexity: O(N)
//
void List::freeAndReset()
{
  
    Node* cur = this->Head;
   
    while (cur != nullptr)  // free the nodes:
    {
       Node* temp = cur->Next;
       delete cur; 
       cur = temp;
    }
   
    this->Head = nullptr;  // reset to empty:
    this->Count = 0;

}



//
// public member functions:
//

//
// default constructor
//
// Initializes the list to empty.
// 
// Time complexity: O(1)
//
List::List()
{
   this->Head = nullptr;
   this->Tail = nullptr;
   this->Count = 0;
}

//
// copy constructor
//
// Makes a deep copy of the other list into this list.
// 
// Time complexity: O(N)
//
List::List(const List& other)
{
   this->initAndDeepCopy(other);
}

//
// destructor
//
// Frees all memory related to this list, and then resets to empty.
// 
// Time complexity: O(N)
//
List::~List()
{
   this->freeAndReset();
}

//
// assignment operator (e.g. L2 = L;)
//
// Makes a deep copy of the other list into this list; since this
// list already exists, the existing elements of this list are freed
// before the copy is made.
// 
// Time complexity: O(N)
//
List& List::operator=(const List& other)
{
   if (this == &other)  // special case: check for L = L;
      return *this;     // do nothing and just return THIS object back

   //
   // This is different from a copy constructor, because "this" list
   // exists and contains nodes.  So we have to free "this" list before
   // we copy the "other" list:
   //
   this->freeAndReset();
   this->initAndDeepCopy(other);

   return *this;  // done, return THIS object back
}

//
// size
//
// Returns the # of elements in the list.
//
// Time complexity: O(1)
//
int List::size()
{   
    
   return this->Count;
   
}

//
// empty
//
// Returns true if empty, false if not.
//
// Time complexity: O(1)
//
bool List::empty()
{
    
   if (this->Count == 0) //check whether list is empty or not
   {
       return true;
   }    
   else
   {
       return false;  
   }
    
}

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
int List::search(string value)
{
    
   int number = 0;
   Node* cur = this->Head;
   while (cur != nullptr) // loop to search list; two cases 
   {                      // 1) given value is the same with input value,  2) other cases
      if (cur->Data.Value1 == value)
      {
         return number;
      }
      else 
      {
         number++;
         cur = cur->Next;
      }
   }
   return -1; 
    
}

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
void List::retrieve(int pos, string& value1, int& value2) //////////////////////////Work
{
  
    if (pos >= this->Count || pos < 0 || this->Count == 0) // position is invalid
    {
        throw invalid_argument("List::retrieve: invalid position");
    }    
    else
    {
        Node* cur = this->Head;
    
        int number = 0;
        while (cur != nullptr) // loop to save data
        {
            if (number == pos)
            {
                value1 = cur->Data.Value1;
                value2 = cur->Data.Value2;
            }
            cur = cur->Next;
            number++;        
        }
    }    
    
}

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
void List::insert(int pos, string value1, int value2)
{
  
    if (pos > this->Count || pos < 0) // position is invalid
    {
        throw invalid_argument("List::insert: invalid position");
    }           
    else
    {
        if (pos == 0) // at first node; call the push_front
        {
            
            this->push_front(value1, value2);
            
        }
        else if (pos == this->Count) // at last node; call the push_back
        {
            
            this->push_back(value1, value2);
            
        }
        else // node in between; set prev to loop and assign
        {
            Node* newN = new Node();
          
            Node* cur = this->Head;
            Node* prev = nullptr;
            int count = 0;
            while (cur != nullptr) 
            {
                if (pos == count)
                {
                    break;               
                }
                count++;
                prev = cur;
                cur = cur->Next;
            }
            newN->Data.Value1 = value1; // linked to each other
            newN->Data.Value2 = value2;
            newN->Next = prev->Next;
            prev->Next = newN;
            this->Count++;
         }
    }
}

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
void List::remove(int pos)
{
   
    if (pos >= this->Count || pos < 0 || this->Count == 0) // position is invalid
    {
        throw invalid_argument("List::remove: invalid position");
    }
    
    else
    {
        if (pos == 0) // at first node
        {
            Node* cur = this->Head;
            Node* prev = nullptr;
            prev = cur;
            cur = cur->Next;
            delete prev; 
            this->Head = cur;
            this->Count = this->Count - 1;
        }
        else if (pos == this->Count-1) // at last node
        {
            Node* cur = this->Tail;            
            delete cur;
            
            this->Count = this->Count - 1;
        }
        else // node in between
        {
            Node* cur = this->Head;
            for (int i = 0; i<pos; i++)
            {
                cur = cur->Next;
            }
            
            Node* temp = nullptr;
            temp = cur->Next; 
            cur->Next = cur->Next->Next; // linked to each other
            delete[] temp;
            this->Count = this->Count-1;
            
        }
   
    }
   
}

//
// front
//
// Returns the data from the first node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::front: empty list");
// 
// Time complexity: O(1)
//
void List::front(string& value1, int& value2) 
{
  
    if (this->Count == 0) // when the list is empty
    {
        throw runtime_error("List::front: empty list");
    }
    else
    {
        Node* cur = this->Head;        
        value1 = cur->Data.Value1;
        value2 = cur->Data.Value2;
    }
     
}

//
// back
//
// Returns the data from the last node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::back: empty list");
// 
// Time complexity: O(1)
//
void List::back(string& value1, int& value2)
{

    if (this->Count == 0) // when the list is empty
    {
        throw runtime_error("List::front: empty list");
    }
    else
    {
        Node* cur = this->Tail;        
        value1 = cur->Data.Value1;
        value2 = cur->Data.Value2;
    }
}

//
// push_front
//
// Inserts the given data at the front of the list.
// 
// Time complexity: O(1)
//
void List::push_front(string value1, int value2)
{
    
    Node* newN = new Node();
    newN->Data.Value1 = value1;
    newN->Data.Value2 = value2;
    newN->Next = this->Head;
    
    this->Head = newN;
    this->Count++;
    
    if (this->Count == 1) // assign Tail
    {
        this->Tail = newN;
    }
      
}

//
// push_back
//
// Inserts the given data at the back of the list.        
// 
// Time complexity: O(1)
//
void List::push_back(string value1, int value2)
{
    
    if (this->Count == 0) // when the list is empty
    {
        this->push_front(value1, value2);       
    }
    else
    {
        Node* newN = new Node();
        newN->Data.Value1 = value1;
        newN->Data.Value2 = value2;
        newN->Next = nullptr;

        this->Tail->Next = newN;
        this->Tail = newN;
        this->Count++;
    }
    
}

