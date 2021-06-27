/*pqueue.h*/

//
// Author: Prof. Hummel, U. of Illinois Chicago, Spring 2021
//
// This library builds upon list library to implement a Priority Queue.
//

#pragma once

#include "list.h"

using namespace std;


//
// pq_init
//
// Initializes list to empty; must be called before list can 
// be used with other queue functions.
//
void pq_init(List& L);

//
// pq_print
// 
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void pq_print(List L);

//
// pq_front
//
// Returns the ID at the front of the priority queue. Throws 
// an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_front: queue empty");
//
int pq_front(List L);

//
// pq_dequeue
//
// Removes the data element at the front of the queue, removing the
// node as well and freeing this memory. Nothing is returned.
// Throws an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_dequeue: queue empty");
//
void pq_dequeue(List& L);

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
void pq_enqueue(List& L, int ID, int priority);

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
void pq_nudge(List& L, int ID);

//
// pq_clear
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void pq_clear(List& L);

//
// pq_duplicate
//
// Makes a complete copy of the given list L and returns this duplicate.
// A "deep" copy is made, meaning all nodes and data are duplicated in 
// the new, returned list.
//
List pq_duplicate(List L);



//
// pq_search
// 
// search list and return appropriate position.  
// This function considers three cases:
// 1) when num is smaller than given Priority
// 2) when num is equal to given Priority
// 3) other cases
//
int pq_search(List L, int num);