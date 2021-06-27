/*pqueue.h*/

//
// Author: ???
// 
// Implements a priority queue for (netid,priority) pairs. The
// queue is ordered by increasing priority. The underlying data
// structure is a one-way linked-list.
//

#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "list.h"

using namespace std;


class PQueue
{
private:
   List Elements;

public:
   PQueue();
   ~PQueue();

   // NOTE: copy constructor not needed because underlying data provide copy constructor.
   // NOTE: operator= not needed because underlying data provide operator=.

   int    size();
   bool   empty();

   string front();
   void   dequeue();
   void   enqueue(string netid, int priority);

   int    search(string netid);
   void   retrieve(int pos, string& netid, int& priority);
   void   remove(int pos);
};
