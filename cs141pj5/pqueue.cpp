//
// Author: Changjae Han UIC 2021 CS 141 Project05 part 2
// April 10, 2021


#include "list.h"
#include "pqueue.h"

using namespace std;

//
// pq_init
//
// Initializes list to empty; must be called before list can 
// be used with other queue functions.
//
void pq_init(List& L)
{
    L.Head = nullptr;
    L.Count = 0;
}

//
// pq_print
// 
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void pq_print(List L)
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
// pq_front
//
// Returns the ID at the front of the priority queue. Throws 
// an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_front: queue empty");
//
int pq_front(List L)
{
    int storeValue;
    if (L.Count == 0) // when the queue is empty
    {
        throw invalid_argument("pq_front: queue empty");
    }
    else
    {
        Node* cur = L.Head;        
        storeValue = cur->Data.ID;       
    }
    
    return storeValue;
}

//
// pq_dequeue
//
// Removes the data element at the front of the queue, removing the
// node as well and freeing this memory. Nothing is returned.
// Throws an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_dequeue: queue empty");
//
void pq_dequeue(List& L)
{
    if (L.Count == 0) // when the queue is empty
    {
        throw invalid_argument("pq_dequeue: queue empty");
    }
    else
    {
        Node* cur = L.Head;
        Node* prev = nullptr;
        prev = cur;
        cur = cur->Next;
        delete prev;
        L.Head = cur;
        L.Count = L.Count - 1;
    }
    
}


//
// pq_enqueue
//
// Inserts the given (ID,priority) pair into the queue based on
// the priority, ordered low to high. If elements already exist with
// the same priority, this new element comes after those elements.
// Example: suppose the queue currently contains the following 
// (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to enqueue (79,25) yields the following result:
//
//   (10,19) (84,25) (79,25) (21,50)
//
// If the ID is already in the queue, then the pair is repositioned 
// based on the new priority. For example, suppose the queue is as
// shown above, and we enqueue (84,50). The result is now
//
//   (10,19) (79,25) (21,50) (84,50)
//
void pq_enqueue(List& L, int ID, int priority) 
{
    int IDsearch = search_list(L, ID);
    
    if (IDsearch != -1) // when found the same ID
    {
        remove_from_list(L, IDsearch);
    }    
    
    int position = pq_search(L, priority);
    
    if (position == 0) // 1) consider position = 0
    {
        Node* newN = new Node();
        newN->Data.ID = ID;
        newN->Data.Priority = priority;
        newN->Next = L.Head;
    
        L.Head = newN;
        L.Count++; 
    }
    else if (position == L.Count) // 2) consider position = L.Count
    {
       Node* indicator = L.Head;
       Node* prev = nullptr;

       while (indicator != nullptr) // loop to define prev, indicator
       {      
          prev = indicator;
          indicator = indicator -> Next;
       }
        Node* newN = new Node();
        newN -> Data.ID = ID;
        newN -> Data.Priority = priority;
        newN -> Next = nullptr;
        prev -> Next = newN;
        L.Count++;
    }
    else // 3) consider other cases
    {       
        Node* newN = new Node();
        Node* cur = L.Head;
        Node* prev = nullptr;
        int count = 0;
        while (cur != nullptr) // loop to check whether position is equal to count
        {
            if (position == count)
            {
                break;               
            }
            count++;
            prev = cur;
            cur = cur->Next;
        }
        newN->Data.ID = ID;
        newN->Data.Priority = priority;
        newN->Next = prev->Next;
        prev->Next = newN;
        L.Count++;
    }    
}



//
// pq_nudge
// 
// Nudges the element with the given ID forward one element in the
// queue. The element takes on the same priority as the element
// that now follows it.  Example: suppose the queue currently contains
// the following (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to "nudge" 21 forward produces this result:
//
//   (10,19) (21,25) (84,25)
//
// If the ID is already at the front of the queue, nothing happens.
// If the ID is not in the queue, throws "invalid_argument" exception, i.e.
// throw invalid_argument("pq_nudge: ID not found");
//
void pq_nudge(List& L, int ID)
{
    int IDsearch = search_list(L, ID);
    int number = 0;
    if (IDsearch == -1)
    {
        throw invalid_argument("pq_nudge: ID not found");
    }
    else if (IDsearch == 0)
    {
        number = number; // nothing happens
    }
    else
    {        
        Node* cur = L.Head;
        Node* prev = nullptr;
        Node* prev2 = nullptr;
        
        while (cur != nullptr) // loop and cases are divided based on number
        {
            if (number == IDsearch)
            {
                if (number == 1)
                {
                    prev->Next = cur->Next;
                    cur->Next = prev;
                    L.Head = cur;
                    cur->Data.Priority = prev->Data.Priority;
                    break;
                }
                else
                {
                    prev->Next = cur->Next;
                    cur->Next = prev;
                    prev2->Next = cur;
                    cur->Data.Priority = prev->Data.Priority;
                    break;
                }
                                
            }
            else
            {
                number++;                
                prev2 = prev;
                prev = cur;
                cur = cur->Next;
            }            
        }
    }    
}

//
// pq_clear
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void pq_clear(List& L)
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
// pq_duplicate
//
// Makes a complete copy of the given list L and returns this duplicate.
// A "deep" copy is made, meaning all nodes and data are duplicated in 
// the new, returned list.
//
List pq_duplicate(List L)
{    
    List T;
    init_list(T);
    Node* cur = L.Head;  
    
    while (cur!= nullptr) // loop to duplicate list
    {        
       NodeData d;
       d.ID = cur->Data.ID;
       d.Priority = cur->Data.Priority;
        
       push_back_list(T, d); // duplicate L to T
        
       cur = cur->Next;
    }  
    
    return T;
}



//
// pq_search
// 
// search list and return appropriate position.  
// This function considers three cases:
// 1) when num is smaller than given Priority
// 2) when num is equal to given Priority
// 3) other cases
//
int pq_search(List L, int num)
{
   int pos = 0;
   if (L.Count == 0)
   {
       return pos;
   }
    
   Node* cur = L.Head;   
   while (cur != nullptr) // loop to search based on three cases
   {
      if (num < cur->Data.Priority) // 1) first case
      {
         return pos;
      }
      else if (num == cur->Data.Priority) // 2) second case
      {
          pos++;
          cur = cur->Next;          
      }
      else // 3) other cases
      {
         pos++;
         cur = cur->Next;
      }
   }
   return L.Count;
}
