//
// Author: Changjae Han UIC 2021 CS 141 Project05 part 1
// April 8, 2021


#include "list.h"


using namespace std;

// 
// init_list
//
// Initializes list to empty; must be called before list can 
// be used with other functions.
//
void init_list(List& L)
{
    L.Head = nullptr;
    L.Count = 0;
}


//
// print_list
//
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void print_list(List L)
{
    Node* cur = L.Head;    
    cout << "List: ";
    while (cur != nullptr) // loop to print list
    {        
        cout << "(" << cur->Data.ID << "," << cur->Data.Priority << ") ";
        cur = cur->Next;
    }
    cout << endl;
}

//
// push_back_list
//
// Pushes the data onto the end of the list.
//
void push_back_list(List& L, NodeData d)
{
    cout << "push back!!!!" << endl;
   if (L.Count == 0) // when the list is empty
   {
       push_front_list(L, d);       
   }
   else
   {
       Node* indicator = L.Head;
       Node* prev = nullptr;

       while (indicator != nullptr) // loop to push back list
       {      
          prev = indicator;
          indicator = indicator -> Next;
       }
        Node* newN = new Node();
        newN -> Data = d;
        newN -> Next = nullptr;
        prev -> Next = newN;
        L.Count++;
   }
   
}


//
// push_front_list
//
// Pushes the data onto the front of the list.
//
void push_front_list(List& L, NodeData d)
{
    Node* newN = new Node();
    newN->Data = d;
    newN->Next = L.Head;
    
    L.Head = newN;
    L.Count++;
}

//
// free_list
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void free_list(List& L)
{
    Node* cur = L.Head;
    Node* temp = nullptr;
    while (cur != nullptr) // loop to free list
    {
        temp = cur;
        cur = cur -> Next;
        delete temp;        
    }
    init_list(L);
}

//
// search_list
//
// Search the list for the first occurrence of the given ID. If found,
// its position in the list is returned; positions are 0-based,
// meaning the first node is position 0. If not found, -1 is
// returned.
//
int search_list(List L, int ID)
{
   int number = 0;
   Node* cur = L.Head;
   while (cur != nullptr) // loop to search list; two cases 1) given ID is the same with input ID,  2) other cases
   {
      if (cur->Data.ID == ID)
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
// retrieve_from_list
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("retrieve_from_list: invalid position");
//
NodeData retrieve_from_list(List L, int pos)
{
    NodeData nodedata;
    if (pos >= L.Count || pos < 0 || L.Count == 0) // position is invalid
    {
        throw invalid_argument("retrieve_from_list: invalid position");
    }    
    else
    {
        Node* cur = L.Head;
    
        int number = 0;
        while (cur != nullptr) // loop to save data in nodedata
        {
            if (number == pos)
            {
                nodedata = cur->Data;
            }
            cur = cur->Next;
            number++;        
        }
    }    
    return nodedata;
}

//
// remove_from_list
//
// Removes and frees the node at the given position, returning 
// the node's data. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("remove_from_list: invalid position");
//
NodeData remove_from_list(List& L, int pos)
{
    NodeData storeValue;
    if (pos >= L.Count || pos < 0 || L.Count == 0) // position is invalid
    {
        throw invalid_argument("remove_from_list: invalid position");
    }
    else if (pos == 0) // if position is 0
    {
        Node* cur = L.Head;
        Node* prev = nullptr;
        prev = cur;
        storeValue = prev->Data;
        cur = cur->Next;
        delete prev;
        L.Head = cur;
        L.Count = L.Count - 1;
    }
    
    else if (pos == L.Count-1) // if position is equal to L.Count-1; cases are divided
    {
            
       Node* cur = L.Head;
       Node* prev = nullptr;
       Node* prev2 = nullptr;

       while (cur != nullptr) // loop to define cur, prev, prev2
       {
          prev2 = prev;
          prev = cur;
          cur = cur -> Next;
       }    

       if (L.Count == 1) // if L.Count is 1 then delete prev2
       {
          storeValue = prev->Data;
          
          delete prev2;
          L.Head = nullptr;
       }
       else 
       {
          storeValue = prev->Data; 
          prev2->Next = nullptr;
       }
       delete prev;
       delete cur;
       L.Count = L.Count - 1;
       
    }
    else // other cases
    {
        Node* cur = L.Head;
        Node* prev = nullptr;
        
        int number = 0;
        while (cur != nullptr) // loop to save data in storeValue
        {
            if (number == pos)
            {
                storeValue = cur->Data;
                break;
            }
            prev = cur;
            cur = cur->Next;
            number++;       
        }
        prev->Next = cur->Next;
        delete cur;
        L.Count = L.Count - 1;     
    }
    
    return storeValue;
}


