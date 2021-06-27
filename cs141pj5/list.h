/*list.h*/

//
// Author: Prof. Hummel, U. of Illinois Chicago, Spring 2021
//
// This library implements a one-way linked-list.
//

#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;


//
// The data stored in each node:
//
struct NodeData
{
   int ID;
   int Priority;
};


//
// Node in a one-way linked-list:
//
struct Node
{
   NodeData Data;
   Node*    Next;
};


//
// List defines a linked-list:
//
struct List
{
   Node* Head;
   int   Count;
};


//
// Functions:
//

// 
// init_list
//
// Initializes list to empty; must be called before list can 
// be used with other functions.
//
void init_list(List& L);

//
// print_list
//
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void print_list(List L);

//
// push_back_list
//
// Pushes the data onto the end of the list.
//
void push_back_list(List& L, NodeData d);

//
// push_front_list
//
// Pushes the data onto the front of the list.
//
void push_front_list(List& L, NodeData d);

//
// free_list
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void free_list(List& L);

//
// search_list
//
// Search the list for the first occurrence of the given ID. If found,
// its position in the list is returned; positions are 0-based,
// meaning the first node is position 0. If not found, -1 is
// returned.
//
int search_list(List L, int ID);

//
// retrieve_from_list
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("retrieve_from_list: invalid position");
//
NodeData retrieve_from_list(List L, int pos);

//
// remove_from_list
//
// Removes and frees the node at the given position, returning 
// the node's data. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("remove_from_list: invalid position");
//
NodeData remove_from_list(List& L, int pos);
