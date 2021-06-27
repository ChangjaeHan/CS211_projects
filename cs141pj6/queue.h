/*queue.h*/

//
// Author: ???
// 
// Implements a standard queue for netids. A standard queue is 
// unordered, with operations to insert at the end and remove from
// the front. The underlying data structure is a one-way linked-list.
//

#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "list.h"

using namespace std;


class Queue
{
private:
   List Elements;

public:
   Queue();
   ~Queue();

   // NOTE: copy constructor not needed because underlying data provide copy constructor.
   // NOTE: operator= not needed because underlying data provide operator=.

   int    size();
   bool   empty();

   string front();
   void   dequeue();
   void   enqueue(string netid);

   int    search(string netid);
   void   retrieve(int pos, string& netid);
   void   remove(int pos);
};
