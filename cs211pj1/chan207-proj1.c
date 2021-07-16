/*  proj1Base.c

    Written on May 19 by Changjae Han for CS 211, Summer 2021

    This program is to find elements correctly matched to each other
    by comparing an original list with a sorted list.
    
*/



#include <stdio.h>

#include <stdlib.h> // header for malloc


// copyArray
// This funciton is to copy array.
void copyArray(int fromArray[], int toArray[], int size)
{
    for (int i=0; i<size; i++)
    {
        toArray[i] = fromArray[i]; // copy every elements from 'fromArray'
    }
}

// selectionSort
// This function is to do selection sort.
void selectionSort(int arr[], int size)
{
    for (int i=0; i<size-1; ++i)
    {
        int smallIndex = i;

	for (int j=i+1; j<size; ++j)
	{
	    if (arr[j] < arr[smallIndex]) // compare values
	    {
		smallIndex = j;
	    }
	}

	int temp = arr[i];         // assign to sort the array in ascending order
	arr[i] = arr[smallIndex];
	arr[smallIndex] = temp;
    }
}

// countMatches
// This fucntion is to count how many values in two arrays match
int countMatches(int arr[], int sorted[], int size)
{
    int count = 0;
    int *parr = arr;    // pointer to arr[]
    int *psor = sorted; // pointer to sorted[]

    for (int i=0; i<size; i++)
    {
	if (*(parr+i) == *(psor+i)) // count how many values in two arrays match
	{
	    count++;
	}
    }

    return count;
}

// findInList
// This function is to determine whether the target is either;
// (a) in the list, in a correctly sorted position
// (b) in the list but not in the correct position
// (c) Not in the list at all
int findInList(int arr[], int sorted[], int size, int target, int* nfound, int* index)
{
    int *parr = arr;     // pointer to arr[]
    int *psor = sorted;  // pointer to sorted[]

    int negCount = 0; // set to verify whether there is nothing found
    int setIndex = 0; // set to save the first index
    int setReturn = 0; // set to compare return 0 and 1

    int t = 0;
    while (*(psor+t) <= target) // if pointer is above target, it stops
    {
	if(*(psor+t) == target)
	{
		
	    *nfound = *nfound + 1; // add nfound

	    if (*(parr+t) == *(psor+t))
	    {
	        if (setIndex == 0) // set first index
       	        {
		    *index = t+1;
		    setReturn = 1; 
	        }
	        setIndex = 1;
	    }
	}
	else
	{
	    negCount++;
	}
	t++;
    }

    if (negCount == t) // nothing found
    {
	return-1;
    }

    if (setReturn == 0) // found but not in order
    {
	return 0;
    }
    else if (setReturn == 1) // found and in order
    {
	return 1;
    }
}




// main function
int main( void )
{
 int val;
 
 // a dynamically allocated array of ints, with initial size 100
 int *Array;
 int allocated = 100;
 Array = (int*)malloc(allocated*sizeof(int));

 
 printf( "Enter in a list of numbers to be stored in a dynamic array.\n" );
 printf( "End the list with the terminal value of -999\n" );
 

 // loop until the user enters
 scanf( "%d", &val );

 int index = 0;
 while( val != -999 )
 {
    // Store the value into an array, growing array if needed.(doubled)
    if (index+1 > allocated)
    {
	int *remove = Array;
	Array = (int*)malloc(allocated*2*sizeof(int));
	for (int i=0; i<allocated; i++)
	{
	    Array[i] = remove[i];
	}
	free(remove); // free the original array
	remove = NULL;
	allocated *= 2; // doubled space
    }

    Array[index] = val;
    // get next value
    index++;
    scanf( "%d", &val );
 }

 int *NewArray;
 NewArray = (int*)malloc(allocated*sizeof(int)); // new array to copy and sort

 // Call function to make a copy of the array of values.
 copyArray(Array, NewArray, allocated);
 // Call function to sort one of the arrays.
 selectionSort(NewArray, allocated);
 

 // call countMatches to calculate percentage.
 printf("\n The number of matches are: ");
 int Matches = countMatches(Array, NewArray, allocated);
 printf("%d\n", Matches);

 printf("\n Numbers already in sorted order: ");
 double percentCal = (double)Matches/allocated*100;
 printf("%.2f%% \n", percentCal);



 // loop until the user enters -999
 printf( "Enter in a list of numbers to search for.  \n" );
 printf( "End the list with a terminal value of -999\n" );
 scanf( "%d", &val );
 while( val != -999 )
 {
    
    int nfound = 0;
    int index = 0;
    // call findInList to check three case
    int check = findInList(Array, NewArray, allocated, val, &nfound, &index);

    printf("Target: %d = ", val);

    if (check == 0)
    {
	printf("present %d times but out of order. \n", nfound);
    }
    else if (check == 1)
    {
	printf("present %d times. \n", nfound);
	printf("First match at position %d. \n", index);
    }
    else if (check == -1)
    {
	printf("Not even in the list! \n");
    }

    // get next value
    scanf( "%d", &val );
 }


 printf( "Good bye\n" );
 
 return 0;
} 
