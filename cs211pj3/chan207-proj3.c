/* CS211 Summer 2021 Project 3

	Project 3 written by Changjae Han on May 26 2021
	
	This project holds two struct, PointNode and polygon which are vertex and polygon respectively.
	When user put integer values, polygon is made and shows vertices information.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FALSE 0;
#define TRUE 1;



int DebugMode = FALSE;


// create PointNode and Polygon data types using typedef

typedef struct PointNode
{
    int ID;
    struct PointNode* next;
} PointNode;

typedef struct Polygon
{
    PointNode* points;
    int nPoints;
    int min, max;
} Polygon;


// declare function
void printList( Polygon* polygon );
int addVertexToPolygon( Polygon* polygon, int vertexID );
PointNode* findVertexInPolygon( Polygon polygon, int vertexID );
int size( Polygon polygon );
int isEmpty( Polygon polygon );
int remove1stVertexFromPolygon( Polygon* polygon );
void findminmax( Polygon polygon, int* minimum, int* maximum);



int main( int argc, char const *argv[ ] )
{
    int data;

    /* Global variable DebugMode: if -d argument is given, additional information should be printed out	as the program runs. */
    
    const char *filename = NULL;

    for (int i=1; i<argc; i++)
    {
	if (strcmp(argv[i], "-d") == 0)
	{
	    printf("DebugMode is operating \n");
	    DebugMode = TRUE;
	}
    }

    // Create polygon and set nPoints
    Polygon nodes;
    nodes.points = NULL;
    nodes.nPoints = 0; 
    
    // Read data for the vertices comprising a Polygon (build a polygon) from standard input 
    // Read data until a negative integer is read.

    printf("Hello! This program comprises dynamically allocated linked lists within struct \n");
    printf("Read data until a negative integer is typed... \n");

    printf("Add data: ");
    scanf("%d", &data);
    while (data >= 0)
    {
	int val = addVertexToPolygon(&nodes, data);
	if (val == -1) // first addition
	{
	    printf("The first data processing... \n");
	    printf("You add %d, then list is: ", data);
	    printList(&nodes);
	    printf("\n");
	}
	else // after first
	{
	    printf("You add %d, then list is: ", data);
	    printList(&nodes);
	    printf("\n");
	}

	printf("Add data: ");
	scanf("%d", &data);
    }

    // just in case there is nothing (user inputs negative integer at first)
    if (isEmpty(nodes) == 1)
    {
	printf("nothing in the polygon \n");
	return 0;
    }

    //DebugMode
    if (DebugMode)
    {
	printf("DebugMode operated: polygon is not linked lists, not empty \n");
	printf("Right before showing min, max, and second vertices set \n");
    }



    // set minimum and maximum and call the findminmax function to find minimum and maximum
    int minimum = 0;
    int maximum = 0;
    findminmax(nodes, &minimum, &maximum);

    

    // Report the Polygon's number of vertices, the specific list of vertex indecies, 
    //  and the minimum and maximum indices in the list.                           
    printf("This polygon has %d vertices, ", size(nodes));
    printf("with indices ");
    printList(&nodes);
    printf("\n");

    printf("The min and max vertices found are %d and %d respectively.", minimum, maximum);

    printf("\n");
    printf("Make second set of integers for queries \n");
   

     // Read data for a second set of vertices,
     //  and for each vertex ID search the Polygon's list of vertices, 
     //  if a matching vertex ID is found, report the address of the PointNode where the ID was found. 
    
     // Read data until a negative integer is read.

    printf("Add data: ");
    scanf("%d", &data);
    while (data >= 0)
    {
	PointNode* temp;

	if ((temp = findVertexInPolygon(nodes, data)) != NULL)
	{
	    printf("Vertex %d was found in the PointNode at address %p", data, temp);
	    printf("\n");
	}
	else
	{
	    printf("Vertex %d was not found \n", data);
	}

	printf("Add data: ");
	scanf("%d", &data);

    }

    

    // free any dynamically allocated memory by calling remove function
    int rem = 0;

    printf("get rid of all vertices and free \n");
    while ((rem = remove1stVertexFromPolygon(&nodes)) != -1)
    {

	printf("polygon: ");
	printList(&nodes);
	printf("\n");
    }

    printf("Good bye\n");

    return 0;

}
// end of main





// function definitions



//
// printList
//
// This function is to show all vertices in polygon.
void printList( Polygon* polygon)
{
    PointNode *current;
    for (current = polygon->points; current != NULL; current = current->next)
    {
	printf("%d ", current->ID);
    }

}


//
// addVertexToPolygon
//
// This function is to add vertex ID to polygon
// Two cases; 1) add first vertex 2) add vertex after first
int addVertexToPolygon( Polygon* polygon, int vertexID )
{
	
    if (polygon->points == NULL)
    {
	PointNode *firstnode;
	firstnode = (PointNode*)malloc(sizeof(PointNode));
	firstnode->ID = vertexID;
	polygon->points = firstnode;
	firstnode->next = NULL;

	polygon->nPoints++;

	return -1; // set -1 as a unique case; when first vertex is added
    }

    PointNode *node;
    node = (PointNode*)malloc(sizeof(PointNode));
    node->ID = vertexID;

    node->next = polygon->points;
    polygon->points = node;
    node = NULL;
    polygon->nPoints++;

    return 0; // add vertex (saved)
}


//
// findminmax
//
// This function is to find minimum and maximum by passing vertices
void findminmax( Polygon polygon, int* minimum, int* maximum)
{
    PointNode *current;
    current = polygon.points;
    *minimum = current->ID;
    *maximum = current->ID;
    for (current != NULL; current = current->next;) // loop to check whether each vertex is less than or more than existing value.
    {
	if (current->ID <= *minimum)
	{
	    *minimum = current->ID;
	}
	if (current->ID >= *maximum)
	{
	    *maximum = current->ID;
	}
    }
}


//
// findVertexInPolygon
//
// This function is to find specific vertex from the user and return its address.
PointNode* findVertexInPolygon( Polygon polygon, int vertexID )
{
    PointNode *current;

    for (current = polygon.points; current != NULL; current = current->next)
    {
	if (current->ID == vertexID) // find matching vertex
	{
	    return current;
	}
    }

    return NULL;
}


//
// size
//
// This function returns nPoints value.
int size( Polygon polygon )
{
    return polygon.nPoints;
}




//
// isEmpty
//
// This function returns 1 when nPoints is 0 and returns 0 otherwise.
int isEmpty( Polygon polygon )
{
    if (polygon.points == NULL)
    {
	return 1;
    }

    return 0;
}



//
// remove1stVertexFromPolygon
//
// This function is to remove first vertex from polygon.
int remove1stVertexFromPolygon( Polygon* polygon )
{
    if (polygon->points == NULL)
    {
	return -1;
    }

    PointNode *getrid = polygon->points;
    polygon->points = (polygon->points)->next;
    
    getrid->next = NULL;
    free(getrid); // free node to prevent memory leak

    return getrid->ID;

}

//
//
//
// I made this code run correctly and free well,
// but when running valgrind, this program shows trivial error in the remove1stVertexFromPolygon.
// I can confirm that error increases whenever the number of vertices increase,
// so there are one or two lines causing this error. It usually said invalid size of 4, 
// this is probably linked to the problem when accessing memory which is not allocated with malloc() or stack.
// I spent a lot of time on this but failed to solve it.
// I will utilize code review for this to find which line or algorithm makes this trivial valgrind error.
//
//
//
