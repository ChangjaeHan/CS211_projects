# CS211_projects
I've learned how to:
1. utilize Pointer (double, triple pointer)
2. utilize virtual, const, and static function
3. differentiate C from C++
4. use inheritance for class
5. making board game
6. handle complex code

--------------------------------------------------------------------Programming in C-----------------------------------------------------------------------------------
# Project1 #
// Target List // 

This program is capable of:
1. Arranging the list in an alphabetical order (sorting algorithm)
2. Setting the target number and compare its position to the list, which is not sorted
3. Expanding the list whenever needed (Dynamically allocated arrays and size double)


# Project2 #
// Collection points in 3D //

This program is capable of:
1. Utilizing typedef struct to have some properties
2. Debug Mode "-d" as a command line argument
3. Handling pointers in the struct and interconnections


# Project3 #
// Linked List for Polygon //

This program is capable of:
1. Handing linked-list and struct
2. Assigning indices and making the most of them


# Project4 #
// Interconnected Structure //

This program is capable of:
1. (project2~4)Connecting 4 typedef structs and utilizing Data diagram


----------------------------------------------------------------------Programming in C++--------------------------------------------------------------------------
# Project5 #
// Collection points in 3D with class //

This program is capable of:
1. Utilizing double pointer
2. Handling class, not struct (so distinguish the concept of public and private)


# Project6 #
// Polygons by using inheritance //

This program is capable of:
1. Inheritance
2. Virtual function for Polygon, Pointset
3. Static and const function


# Project7 #
// Board game // (pending, almost done)

This program is capable of:
1. All of the previous project
2. Making a board and character
3. Detecting collision
4. AI depending on my main character



# Need #
• In-line commenting
• Function header commenting
• File header commenting
• Meaningful and description variable names
• Proper use of indentation
• Proper use of blank lines
• Use of Functions


# Restrictions #
• No global variables are allowed, with the unusual exception of the DebugMode bool. In particular the PointCloud must be declared in main and passed around as needed. ( The definition of the classes must be global, so they are known to all functions, but the variables themselves are all local variables. )
• All good programming practices should be exercised, including proper commenting, variable naming, loop indentation, use of functions, and so on.
• All dynamically allocated memory must be freed before exiting the program. This last point will be tested using valgrind when evaluating your program. ( And for all future projects. )
• This assignment is to use new and delete in place of malloc and free. new throws exceptions if the requested memory cannot be allocated, instead of returning NULL. Exception handling will be covered later in the course, so you may omit this error handling for now if you are not familiar with exceptions and exception handling.
