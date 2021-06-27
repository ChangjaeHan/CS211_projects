//
// Author: Changjae Han
// 
// Project 6 Part1;  April 29, 2021
// 

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

//#include "classreg.h"
#include "list.h"
//#include "queue.h"
//#include "pqueue.h"

using namespace std;

/*


//
// define all functions
//
//
void sortByName(ClassReg csclass, string enrollment[]);
void coutHelp(void);
void coutStats(ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251);
void listCS(ClassReg csclass);
void IncreaseCap(ClassReg& csclass, string command_class, int capacity);
void enrollmentStudent(ClassReg& csclass, string command_class, string ID);
void waitStudent(ClassReg& csclass, string command_class, string ID, int priority);
void outputProcess(ofstream& outfile, bool promptUser, ClassReg& csclass);
void executeList(ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251, string command_class);
void executeIncrease(ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251, string command_class, int command_capacity);
void executeEnroll(ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251, string command_class, string ID);
void executeWaitlist(ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251, string command_class, string ID, int priority);
void processCommands(ifstream& input, bool promptUser, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251);
void executeFunction(string command, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251);
void inputfile(ifstream& infile, ClassReg& csclass);



//
// sortByName
// 
// sorting by name; alphabetical order(a~z) by assigning csclass value to new list.
//
void sortByName(ClassReg csclass, string enrollment[])
{

   for (int i = 0; i < csclass.numEnrolled()-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < csclass.numEnrolled(); j++)
      {
         if (enrollment[j] < enrollment[minIndex]) //alphabetical order
         {
            minIndex = j;
         }
      }
      
      string temp = enrollment[i];                 //assign value for order
      enrollment[i] = enrollment[minIndex];
      enrollment[minIndex] = temp;         
   }   
}

//
// coutHelp
// 
// print help message for user.
//
void coutHelp(void)
{
    cout << "stats" << endl;
    cout << "list class" << endl;
    cout << "increase class capacity" << endl;
    cout << "enroll class netid" << endl;
    cout << "waitlist class netid priority" << endl;
    cout << "process filename" << endl;
    cout << "output filename" << endl;
    cout << "quit" << endl;
    cout << endl;
}

//
// coutStats
//
// print enrolled and waitlisted student in class.  
//
void coutStats(ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251)
{
    cout << "cs111: enrolled=" << cs111.numEnrolled() << ", waitlisted=" << cs111.numWaitlisted() << endl;
    cout << "cs141: enrolled=" << cs141.numEnrolled() << ", waitlisted=" << cs141.numWaitlisted() << endl;
    cout << "cs151: enrolled=" << cs151.numEnrolled() << ", waitlisted=" << cs151.numWaitlisted() << endl;
    cout << "cs211: enrolled=" << cs211.numEnrolled() << ", waitlisted=" << cs211.numWaitlisted() << endl;
    cout << "cs251: enrolled=" << cs251.numEnrolled() << ", waitlisted=" << cs251.numWaitlisted() << endl;
}

//
// listCS
// 
// print capacity, enrolled and waitlisted student in specific class.
// enrolled student is sorted by name.
//
void listCS(ClassReg csclass) 
{
    string* enrollment = new string[csclass.numEnrolled()]; //create new list for assigning sorted enrolled student.
       
    for (int i=0; i< csclass.numEnrolled(); i++)
    {
       enrollment[i] = csclass.retrieveEnrolledStudent(i);
    }
    
    sortByName(csclass, enrollment); //call sortByName function to sort in alphabetical order
    
    cout << "Capacity: " << csclass.getCapacity() << endl;
    cout << "Enrolled (" << csclass.numEnrolled() << "): ";
    for (int i = 0; i < csclass.numEnrolled(); i++)
    {                    
        cout << enrollment[i] << " ";
    }
    cout << endl;
   
    cout << "Waitlisted (" << csclass.numWaitlisted() << "): ";
    for (int i = 0; i < csclass.numWaitlisted(); i++)
    {                
        string netid;
        int priority;
        csclass.retrieveWaitlistedStudent(i, netid, priority);  //pass-by-reference is applied      
        cout << netid << " (" << priority << ") ";
    }
    cout << endl;
    delete[] enrollment;
}

//
// IncreaseCap
// 
// Increase Capacity in class; capacity cannot decrease
// if user tries to input lower integer, print error
//
void IncreaseCap(ClassReg& csclass, string command_class, int capacity)
{
  
    if (capacity >= csclass.getCapacity()) //cannot decrease capacity
    {
        csclass.setCapacity(capacity);
        cout << command_class << endl;
        cout << "Capacity: " << csclass.getCapacity() << endl;
    }
    else
    {
        cout << "**Error, cannot decrease class capacity, ignored..." << endl;       
    } 

}


//
// enrollmentStudent
//
// enroll a student in class. If capacity is full, students will be in the waitlist (priority 1).
// If the student was in the waitlist, then enroll and remove him from the waitlist.
//
void enrollmentStudent(ClassReg& csclass, string command_class, string ID)
{
    
    if (csclass.searchEnrolled(ID) != -1) // if already enrolled; nothing happens
    {
        cout << "Student " << "'" << ID << "'" << " enrolled in " << command_class << endl;
    }
    else if (csclass.searchWaitlisted(ID) != -1) // if already waitlisted
    {
        if (csclass.getCapacity() != csclass.numEnrolled()) // enough capacity
        {
            csclass.enrollStudent(ID);
            csclass.removeWaitlistedStudent(csclass.searchWaitlisted(ID));
            cout << "Student " << "'" << ID << "'" << " enrolled in " << command_class << endl;
        }
        else // not enough capacity
        {            
            cout << "Class full, " << "'" << ID << "'" << " waitlisted for " << command_class << endl;          
        }

    }
    else // not in the waitlist
    {
        if (csclass.getCapacity() != csclass.numEnrolled()) // enough capacity
        {
            csclass.enrollStudent(ID);
            cout << "Student " << "'" << ID << "'" << " enrolled in " << command_class << endl;
        }
        else // not enough capacity
        {
            
            cout << "Class full, " << "'" << ID << "'" << " waitlisted for " << command_class << endl;
            
            if (csclass.numWaitlisted() == 0) // nothing in the waitlist; priority = 1
            {
                csclass.waitlistStudent(ID, 1);
            }
            else  // some people in the waitlist; priority = last person's priority; so one should be the last
            {
                string netid;
                int priority;
                csclass.retrieveWaitlistedStudent(csclass.numWaitlisted()-1, netid, priority);
                csclass.waitlistStudent(ID, priority);
            }
            
        }
    }
    
}

//
// waitStudent 
// 
// A function for putting a student into the waitlist.  
// If the student was already in the waitlist, nothing will happen.
//
void waitStudent(ClassReg& csclass, string command_class, string ID, int priority)
{
    
    if (csclass.searchEnrolled(ID) != -1) // if already enrolled; nothing happens
    {
        cout << "Student " << "'" << ID << "'" << " enrolled in " << command_class << endl;
    }
    else if (csclass.searchWaitlisted(ID) != -1) // if in the waitlist
    {
        csclass.removeWaitlistedStudent(csclass.searchWaitlisted(ID));
        csclass.waitlistStudent(ID, priority);        
        cout << "Student " << "'" << ID << "'" << " waitlisted for " << command_class << endl;
    }
    else // if not in the waitlist
    {
        csclass.waitlistStudent(ID, priority);        
        cout << "Student " << "'" << ID << "'" << " waitlisted for " << command_class << endl;            
    }
   
}

// 
// outputProcess 
// 
// output file list; if promptUser is false, output file
//
void outputProcess(ofstream& outfile, bool promptUser, ClassReg& csclass)
{
    if (promptUser) 
    {
        cout << endl;
        cout << "Enter a command (help for more info, quit to stop)>" << endl;
    }
    else
    {        
        outfile << csclass.getCapacity() << endl;
        
        string* enrollment = new string[csclass.numEnrolled()];
       
        for (int i=0; i< csclass.numEnrolled(); i++)
        {
           enrollment[i] = csclass.retrieveEnrolledStudent(i);
        }
                                                                    //no need to sort, same with listCS
        for (int i = 0; i < csclass.numEnrolled(); i++)
        {                    
            outfile << enrollment[i] << " ";
        }
        outfile << "#" << endl;

        for (int i = 0; i < csclass.numWaitlisted(); i++)
        {        
            string netid;
            int priority;
            csclass.retrieveWaitlistedStudent(i, netid, priority);        
            
            outfile << netid << " " << priority << " ";
        }
        outfile << "#" << endl;
        delete[] enrollment;
    }
}

//
// executeList
// 
// execute list when command_class is cs111, cs141, cs151, cs211, cs251
//
void executeList(ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251, string command_class)
{
    
    if (command_class == "cs111")
    {
        cout << "cs111" << endl;                
        listCS(cs111);
    }
    else if (command_class == "cs141")
    {
        cout << "cs141" << endl;
        listCS(cs141);
    }
    else if (command_class == "cs151")
    {
        cout << "cs151" << endl;
        listCS(cs151);
    }
    else if (command_class == "cs211")
    {
        cout << "cs211" << endl;
        listCS(cs211);
    }
    else if (command_class == "cs251")
    {
        cout << "cs251" << endl;
        listCS(cs251);
    }
    else
    {
        cout << "**Invalid class name, try again..." << endl;
    }
}

//
// executeIncrease
// 
// execute increasing capacity; when command_class is cs111, cs141, cs151, cs211, cs251
//
void executeIncrease(ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251, string command_class, int command_capacity)
{
                     
    if (command_class == "cs111")
    {
        IncreaseCap(cs111, command_class, command_capacity);                 
    }
    else if (command_class == "cs141")
    {
        IncreaseCap(cs141, command_class, command_capacity);                  
    }
    else if (command_class == "cs151")
    {
        IncreaseCap(cs151, command_class, command_capacity);                  
    }
    else if (command_class == "cs211")
    {
        IncreaseCap(cs211, command_class, command_capacity);                  
    }
    else if (command_class == "cs251")
    {
        IncreaseCap(cs251, command_class, command_capacity);                  
    }
    else
    {
        cout << "**Invalid class name, try again..." << endl;
    }      
}

//
// executeEnroll
//
// execute enrollmentStudent; when command_class is cs111, cs141, cs151, cs211, cs251
//
void executeEnroll(ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251, string command_class, string ID)
{
    
    if (command_class == "cs111")
    {
        enrollmentStudent(cs111, command_class, ID);
    }
    else if (command_class == "cs141")
    {
        enrollmentStudent(cs141, command_class, ID);
    }
    else if (command_class == "cs151")
    {
        enrollmentStudent(cs151, command_class, ID);
    }
    else if (command_class == "cs211")
    {
        enrollmentStudent(cs211, command_class, ID);
    }
    else if (command_class == "cs251")
    {
        enrollmentStudent(cs251, command_class, ID);
    }
    else
    {
        cout << "**Invalid class name, try again..." << endl;
    }
}

//
// executeWaitlist
//
// execute waitStudent; when command_class is cs111, cs141, cs151, cs211, cs251
//
void executeWaitlist(ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251, string command_class, string ID, int priority)
{   

    if (command_class == "cs111")
    {
        waitStudent(cs111, command_class, ID, priority);
    }
    else if (command_class == "cs141")
    {
        waitStudent(cs141, command_class, ID, priority);
    }
    else if (command_class == "cs151")
    {
        waitStudent(cs151, command_class, ID, priority);
    }
    else if (command_class == "cs211")
    {
        waitStudent(cs211, command_class, ID, priority);
    }
    else if (command_class == "cs251")
    {
        waitStudent(cs251, command_class, ID, priority);
    }
    else 
    {
        cout << "**Invalid class name, try again..." << endl; 
    }
}

//
// processCommands
//
// process commands in the file; similar with executeFunction; this also can recursively process the file.
// This functions can execute 9 commands; otherwise print invalid message
//
void processCommands(ifstream& input, bool promptUser, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    string cmd;
    if (promptUser)
    {
        cout << endl;
        cout << "Enter a command (help for more info, quit to stop)>" << endl;
    }
    
    input >> cmd;    
    while (cmd != "quit" && cmd!= "q") // while loop to continue processing commands until file has quit or q
    {
        if (cmd == "help" || cmd == "h") // below is the similar with executeFunction
        {
            coutHelp();
        }
        else if (cmd == "stats" || cmd == "s")
        {
            coutStats(cs111, cs141, cs151, cs211, cs251);
        }
        else if (cmd == "list" || cmd == "l")
        {
            string command_class;
            input >> command_class;
            executeList(cs111, cs141, cs151, cs211, cs251, command_class);
        }
        else if (cmd == "increase" || cmd == "i")
        {
            string command_class;
            input >> command_class;
            int command_capacity;
            input >> command_capacity;
            executeIncrease(cs111, cs141, cs151, cs211, cs251, command_class, command_capacity);            
        }
        else if (cmd == "enroll" || cmd == "e")
        {
            string command_class;
            input >> command_class;
            string ID;
            input >> ID;
            executeEnroll(cs111, cs141, cs151, cs211, cs251, command_class, ID);            
        }
        else if (cmd == "waitlist" || cmd == "w")
        {
            string command_class;
            input >> command_class;
            string ID;
            input >> ID;
            int priority;
            input >> priority;
            executeWaitlist(cs111, cs141, cs151, cs211, cs251, command_class, ID, priority);           
        }
        else if (cmd == "process" || cmd == "p") // recursively can process file
        {
            string filename;
            input >> filename;
            cout << "**Processing commands from " << "'" << filename << "'" << endl;
            ifstream infile;
            infile.open(filename);
            if (!infile.good())
            {
                cout << "**Error: unable to open command file '" << filename << "'" << endl;
                processCommands(infile, true, cs111, cs141, cs151, cs211, cs251);
            }
            else
            {               
                processCommands(infile, false, cs111, cs141, cs151, cs211, cs251);
                cout << "**Done processing " << "'" << filename << "'" << endl;
            }
            infile.close();             
        }
        else if (cmd == "output" || cmd == "o")
        {
            string filename2;
            input >> filename2;         
            ofstream outfile;
            outfile.open(filename2);
                      
            cout << "Enrollment data output to " << "'" << filename2 << "'" << endl;
            outfile << "cs111" << endl;
            outputProcess(outfile, false, cs111);
            outfile << "cs141" << endl;
            outputProcess(outfile, false, cs141);
            outfile << "cs151" << endl;
            outputProcess(outfile, false, cs151);
            outfile << "cs211" << endl;
            outputProcess(outfile, false, cs211);
            outfile << "cs251" << endl;
            outputProcess(outfile, false, cs251);
                           
            outfile.close();               
        }
        else
        {
            cout << "**Invalid command, please try again..." << endl;
        }   
        
        input >> cmd;
    }   
}

//
// executeFunction
//
// This function is for executing commands from the user
//
// (1) help: print help statement (also h) 
// (2) stats: print information of all class; how many enrolled and waitlisted (also s)
// (3) list: print detailed information for specific class; classname, capacity, # and information of enrolled and waitlisted student (also l) 
// (4) increase: increase capacity for specific class (also i)
// (5) enroll: enroll students in specific class (also e)
// (6) waitlist: put students in the waitlist in specific class (also w)
// (7) process: process commands in the file (also p)
// (8) output: output information to the file (also o)
//
void executeFunction(string command, ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    while (command != "quit" && command != "q") // while loop to continue processing commands until user put quit or q
    {
        if (command == "help" || command == "h")
        {
            coutHelp();
        }
        else if (command == "stats" || command == "s")
        {
            coutStats(cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "list" || command == "l")
        {
            string command_class;
            cin >> command_class;
            executeList(cs111, cs141, cs151, cs211, cs251, command_class);
        }
        else if (command == "increase" || command == "i")
        {
            string command_class;
            cin >> command_class;
            int command_capacity;
            cin >> command_capacity;
            executeIncrease(cs111, cs141, cs151, cs211, cs251, command_class, command_capacity);            
        }
        else if (command == "enroll" || command == "e")
        {
            string command_class;
            cin >> command_class;
            string ID;
            cin >> ID;
            executeEnroll(cs111, cs141, cs151, cs211, cs251, command_class, ID);            
        }
        else if (command == "waitlist" || command == "w")
        {
            string command_class;
            cin >> command_class;
            string ID;
            cin >> ID;
            int priority;
            cin >> priority;
            executeWaitlist(cs111, cs141, cs151, cs211, cs251, command_class, ID, priority);           
        }
        else if (command == "process" || command == "p")
        {
            
            string filename;
            cin >> filename;
            cout << "**Processing commands from " << "'" << filename << "'" << endl;
            ifstream infile;
            infile.open(filename);
            if (!infile.good())
            {
                cout << "**Error: unable to open command file '" << filename << "'" << endl;
                processCommands(infile, true, cs111, cs141, cs151, cs211, cs251);
            }
            else
            {               
                processCommands(infile, false, cs111, cs141, cs151, cs211, cs251);
                cout << "**Done processing " << "'" << filename << "'" << endl;
            }
            infile.close();             
        }
        else if (command == "output" || command == "o")
        {
            string filename2;
            cin >> filename2;
            ofstream outfile;
            outfile.open(filename2);
              
            cout << "Enrollment data output to " << "'" << filename2 << "'" << endl;
            outfile << "cs111" << endl;
            outputProcess(outfile, false, cs111);
            outfile << "cs141" << endl;
            outputProcess(outfile, false, cs141);
            outfile << "cs151" << endl;
            outputProcess(outfile, false, cs151);
            outfile << "cs211" << endl;
            outputProcess(outfile, false, cs211);
            outfile << "cs251" << endl;
            outputProcess(outfile, false, cs251);
                           
            outfile.close();               
        }
        else
        {
            cout << "**Invalid command, please try again..." << endl;
        }
        
        cout << "Enter a command (help for more info, quit to stop)>" << endl;
        cin >> command;
    }
    cout << "**Done**" << endl;
}

//
// inputfile
//
// save information from enrollments file
//
void inputfile(ifstream& infile, ClassReg& csclass)
{
    string classname;
    infile >> classname;
    
    int classcapacity;
    infile >> classcapacity;
  
    csclass.setCapacity(classcapacity);
      
    string classenrollment;
    infile >> classenrollment;
    
    while (classenrollment != "#") // # indicates finished
    {        
        csclass.enrollStudent(classenrollment);
     
        infile >> classenrollment;
    }

    string classwaitlist;
    int classpriority;
    infile >> classwaitlist;
    
    while (classwaitlist != "#")
    {
        infile >> classpriority;
        csclass.waitlistStudent(classwaitlist, classpriority);

        infile >> classwaitlist;       
    }     
}
*/

//
// main function 
//
//
int main()
{   
    
    List L1;
    List L2;
        
    
    string value1 = "";
    int value2 = 0;
    cout << "L size: " << L1.size() << endl;
    cout << "list empty?: ";
    if (L1.empty())
    {
         cout << "yes!" << endl;    
    }
    
    L1.insert(0, "apple", 123);

    L1.insert(1, "pizza", 789);

    L1.insert(2, "wowow", 789);
    for (int pos = 0; pos<L1.size(); pos++)
    {
        L1.retrieve(pos, value1, value2);
        cout << value1 << " ";
        cout << value2 << endl;
    }
 
    L1.insert(3, "ThisONE", 456);
    L1.insert(4, "cola", 123);
    L1.insert(5, "sider", 123);
    
    /*for (int pos = 0; pos<L1.size(); pos++)
    {
        L1.retrieve(pos, value1, value2);
        cout << value1 << " ";
        cout << value2 << endl;
    }*/
    L1.remove(0);
    L1.remove(4);
    
   /* for (int pos = 0; pos<L1.size(); pos++)
    {
        L1.retrieve(pos, value1, value2);
        cout << value1 << " ";
        cout << value2 << endl;
    }*/
    L1.insert(0, "heck", 123);
    
    /*for (int pos = 0; pos<L1.size(); pos++)
    {
        L1.retrieve(pos, value1, value2);
        cout << value1 << " ";
        cout << value2 << endl;
    }*/
    /*
    L2.insert(0, "cola", 123);
    L2.insert(1, "popcorn", 789);
    L2.insert(1, "corn", 456);
    for (int pos = 0; pos<L2.size(); pos++)
    {
        L2.retrieve(pos, value1, value2);
        cout << value1 << " ";
        cout << value2 << endl;
    }*/
    
    
    return 0;
}
   /* cout << "size: " << L.size() << endl;
   
    for (int pos = 0; pos<L.size(); pos++)
    {
        L.retrieve(pos, value1, value2);
        cout << value1 << " ";
        cout << value2 << endl;
    }
    L.remove(0);
    for (int pos = 0; pos<L.size(); pos++)
    {
        L.retrieve(pos, value1, value2);
        cout << "value1: " << value1 << " ";
        cout << "value2: " << value2 << endl;
    }
    L.insert(0, "HojaeHan", 1);
    L.insert(1, "CHANGJAEHAN", 500);
    L.insert(2, "wait", 400);
    for (int pos = 0; pos<L.size(); pos++)
    {
        L.retrieve(pos, value1, value2);
        cout << "value1: " << value1 << " ";
        cout << "value2: " << value2 << endl;
    }
    L.remove(1);
    for (int pos = 0; pos<L.size(); pos++)
    {
        L.retrieve(pos, value1, value2);
        cout << "value1: " << value1 << " ";
        cout << "value2: " << value2 << endl;
    }
    L.insert(2, "LAST", 40);
    for (int pos = 0; pos<L.size(); pos++)
    {
        L.retrieve(pos, value1, value2);
        cout << "value1: " << value1 << " ";
        cout << "value2: " << value2 << endl;
    }*/
    /*
    L.push_back("orange", 5);    
    L.push_back("apple", 3);
    L.push_back("orange", 5);
    L.push_front("heheheh", 8);
    L.front(value1,value2);
    cout << "value1: " << value1 << endl;
    cout << "value2: " << value2 << endl;
    L.back(value1,value2);
    cout << "value1: " << value1 << endl;
    cout << "value2: " << value2 << endl;
    L.insert(0, "ChangjaeHan", 6);
    L.front(value1,value2);
    cout << "value1: " << value1 << endl;
    cout << "value2: " << value2 << endl;
    L.insert(3, "Kimgyeongnam", 10);
    L.back(value1,value2);
    cout << "value1: " << value1 << endl;
    cout << "value2: " << value2 << endl;
    cout << L.size() << endl;
    L.insert(2, "like", 2);
    L.insert(3, "3 position", 2);
    
    L.remove(5);
    for (int pos = 0; pos<L.size(); pos++)
    {
        L.retrieve(pos, value1, value2);
        cout << value1 << " ";
        cout << value2 << endl;
    }
    cout << L.size() << endl;
    L.remove(0);
    cout << "list empty?: ";
    if (L.empty())
    {
         cout << "yes!" << endl;    
    }
    //L.print_List();
    //L.retrieve()
    */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
   /* 
    ClassReg cs111, cs141, cs151, cs211, cs251;
    
    cout << "**CS Enrollment System**" << endl;  
    
    string filename;  
    cout << "Enter enrollments filename>" << endl;
    
    cin >> filename;
    ifstream infile;
    infile.open(filename);        
    if (!infile.good()) //file is NOT good, i.e. could not be opened:
    {
        cout << "**Error: unable to open enrollments file '" << filename << "'" << endl;        
        return 0; // return now since we cannot continue without input file.        
    }
      
    inputfile(infile, cs111); // call inputfile function to save information in cs111,141,151,211,251 
    inputfile(infile, cs141);
    inputfile(infile, cs151);
    inputfile(infile, cs211);
    inputfile(infile, cs251);
            
    cout << "Enter a command (help for more info, quit to stop)>" << endl;
    string command;
    cin >> command;
           
    executeFunction(command, cs111, cs141, cs151, cs211, cs251);
    infile.close();
    */
    
    
    
    
    
    
    
    
    
    
    
