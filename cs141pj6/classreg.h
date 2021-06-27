/*classreg.h*/

//
// Author: Prof. Hummel, U. of I. Chicago, Spring 2021
// 
// Implements class registration for one class, e.g. "CS141". 
// Supports the enrollment of students via netid, and a waitlist
// of students based on a priority; the lower the priority the 
// higher the chance of getting enrolled.
//
#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "queue.h"
#include "pqueue.h"

using namespace std;


class ClassReg
{
private:
   string  Name;      // class name
   int     Capacity;  // enrollment capacity for class
   Queue   Enrolled;  // ordinary queue of enrolled students, in enrollment order
   PQueue  Waitlist;  // priority queue of waiting students, in priority order (low to high)

public:
   //
   // default constructor
   //
   // Sets name to "", capacity to 0, and queues are empty.
   //
   ClassReg();

   //
   // parameterized constructor
   //
   // Sets name and capacity to the given values; queues are empty.
   //
   ClassReg(string name, int capacity);

   //
   // destructor
   //
   // Frees the memory related to the queues.
   //
   ~ClassReg();

   // NOTE: copy constructor not needed because underlying data provide copy constructor.
   // NOTE: operator= not needed because underlying data provide operator=.

   //
   // getName
   //
   // Returns the class name.
   //
   string getName();

   //
   // setName
   // 
   // Sets the class name to the given name.
   //
   void setName(string newName);

   //
   // getCapacity
   //
   // Returns the class enrollment capacity.
   //
   int getCapacity();

   //
   // setCapacity
   //
   // Sets the class enrollment capacity to the given value.
   // Note that new capacity cannot be less than the current 
   // capacity, otherwise an exception is throw, i.e.
   // throw invalid_argument("ClassReg::setCapacity: smaller");
   //
   void setCapacity(int newCapacity);

   //
   // numEnrolled
   //
   // Returns the # of students currently enrolled.
   //
   int numEnrolled();

   //
   // enrollStudent
   //
   // Enrolls the given student in the class by adding them
   // to the end of the Enrolled queue; if the student is already
   // enrolled, then nothing happens --- the Enrolled queue is
   // left as is.
   //
   // If the class is full, an exception is throw, i.e.
   // throw runtime_error("ClassReg::enrollStudent: full");
   //
   void enrollStudent(string netid);

   //
   // searchEnrolled
   //
   // Searches the Enrolled queue for the given student. If
   // found the student's position is returned; positions are
   // 0-based, meaning the first student has position 0. If
   // the student is not found, -1 is returned.
   //
   int searchEnrolled(string netid);

   //
   // retrieveEnrolledStudent
   //
   // Retrieves the student netid from the Enrolled queue at the  
   // given position. Positions are 0-based, meaning the first  
   // student has position 0. An exception is thrown if the position 
   // is invalid, i.e.
   // throw throw invalid_argument("ClassReg::retrieveEnrolledStudent: invalid position");
   //
   string retrieveEnrolledStudent(int pos);

   //
   // removeEnrolledStudent
   // 
   // Removes the student from the Enrolled queue at the given 
   // position. Positions are 0-based, meaning the first student 
   // has position 0. An exception is thrown if the position is 
   // invalid, i.e.
   // throw invalid_argument("ClassReg::removeEnrolledStudent: invalid position");
   //
   void removeEnrolledStudent(int pos);

   //
   // numWaitlisted
   //
   // Returns the # of students currently waitlisted.
   //
   int numWaitlisted();

   //
   // waitlistStudent
   //
   // Waitlists the given student in the class by adding them
   // to the Waitlisted queue; their position in the queue is
   // determined by the given priority. If the student is already
   // waitlisted, they are reomved and then re-inserted; this 
   // updates the student's position based on the new priority.
   //
   void waitlistStudent(string netid, int priority);

   //
   // searchWaitlisted
   //
   // Searches the Waitlisted queue for the given student. If
   // found the student's position is returned; positions are
   // 0-based, meaning the first student has position 0. If
   // the student is not found, -1 is returned.
   //
   int searchWaitlisted(string netid);

   //
   // retrieveWaitlistedStudent
   //
   // Retrieves the student netid and priority from the Waitlisted
   // queue at the given position. Positions are 0-based, meaning the  
   // first student has position 0. An exception is thrown if the
   // position is invalid, i.e.
   // throw invalid_argument("ClassReg::retrieveWaitlistedStudent: invalid position");
   //
   void retrieveWaitlistedStudent(int pos, string& netid, int& priority);

   //
   // removeWaitlistedStudent
   // 
   // Removes the student from the Waitlisted queue at the given 
   // position. Positions are 0-based, meaning the first student 
   // has position 0. An exception is thrown if the position is 
   // invalid, i.e.
   // throw invalid_argument("ClassReg::removeWaitlistedStudent: invalid position");
   //
   void removeWaitlistedStudent(int pos);
};
