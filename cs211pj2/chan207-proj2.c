/* CS211 Summer 2021 Project 2

	Changjae Han on May 24, 2021. 

	The purpose of the project2: this project2 contains the information of 3D space
	and certain traits of the collection to help get familiar with the usage of
       	struct and pointer, and build the logical algorithms.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Point3d and PointSet data types using typedef and structs 

typedef struct
{
    int ID;
    double coordinates[3];
    double luminosity;
} Point3d;


typedef struct
{
     Point3d* points;
     int allocated;
     int nPoints;
     double luminosity;
     double lower[3],upper[3];
} PointSet;


#define TRUE 1
#define FALSE 0

int DebugMode;  //define DebugMode


//define function
int addPointToSet( PointSet *set, Point3d point );
int intersection( PointSet set, Point3d point );


int main( int argc, char const *argv[ ] )
{
    
    int i;

    //set condition for DebugMode
    DebugMode = FALSE;
    for (i=0; i<argc; i++)
    {
	if (strcmp(argv[i],"-d") == 0)
	{
	    printf("DebugMode is operating \n");
	    DebugMode = TRUE;
	}
    }

   /* if (DebugMode == TRUE)
    {
	printf("Check this out \n");  // Debug print statement which can be used for clarification.
	                              // Also can point out exact error using %d. This depends on users.
    }*/                                 


    //set struct and allocate memory
    PointSet Point3ds;
    int SIZE = 1;
    Point3ds.points = (Point3d*)malloc(SIZE*sizeof(Point3d));


    //initialize values
    int numID = 0;
    int count = 0;
    double x,y,z,luminosity = 0.0;
    Point3ds.nPoints = 0;

    double C_grav_x = 0.0;
    double C_grav_y = 0.0;
    double C_grav_z = 0.0;
    double num_x = 0.0;
    double num_y = 0.0;
    double num_z = 0.0;

    printf("\t **Greetings, this is a program dealing with collection of points in 3D** \n");
    printf("First points: Enter 4 values (negative luminosity for stop): \n");
    scanf("%lf %lf %lf %lf", &x,&y,&z,&luminosity);

    //
    // while loop until negative luminosity
    while (luminosity > 0.0)
    {
	if (count+1 > SIZE)
	{
	    Point3d *temp = Point3ds.points;
	    Point3ds.points = (Point3d*)malloc(SIZE*2*sizeof(Point3d)); // size twice
	    for (int i=0; i<SIZE; i++)
	    {
		*(Point3ds.points+i) = *(temp+i); // assign values
	    }

	    SIZE *=2;
	    free(temp); // free memory
	    temp = NULL; // set null to prevent reuse
	}

	Point3d point; // temporary point to add it 

	point.ID = numID;
	point.coordinates[0] = x;
	point.coordinates[1] = y;
	point.coordinates[2] = z;
	point.luminosity = luminosity;

	printf("User inputs coordinates(%.2lf, %.2lf, %.2lf) luminosity(%.2lf) \n", point.coordinates[0],
			point.coordinates[1], point.coordinates[2], point.luminosity);

	count++;


	printf("Add this point to Pointset... \n");

	int ret = addPointToSet(&Point3ds, point); // call the addPointToSet function to check
						   // whether points already exist or not

	if (ret == -1)
	{
	    printf("This point already exist. Try again \n");
	}
	else
	{
	    printf("Successfully added ID: %d \n", numID);
	    num_x = num_x + x;
	    num_y = num_y + y;
	    num_z = num_z + z;
	    numID++;
	}


	printf("Enter 4 value again: \n");
	scanf("%lf %lf %lf %lf", &x, &y, &z, &luminosity); // again and again if not -luminosity
    }

    Point3ds.allocated = SIZE;
    Point3ds.luminosity = Point3ds.luminosity/numID; // set struct values


    printf("lowerpoint,x = %lf \n", Point3ds.lower[0]);
    printf("upperpoint,x = %lf \n", Point3ds.upper[0]);

    printf("lowerpoint,y = %lf \n", Point3ds.lower[1]);
    printf("upperpoint,y = %lf \n", Point3ds.upper[1]);

    printf("lowerpoint,z = %lf \n", Point3ds.lower[2]);
    printf("upperpoint,z = %lf \n", Point3ds.upper[2]);


    printf("Average luminosity = %lf \n", Point3ds.luminosity);
    printf("The number of points in the Pointset = %d \n", Point3ds.nPoints);

    C_grav_x = (num_x)/numID;
    C_grav_y = (num_y)/numID;
    C_grav_z = (num_z)/numID;

    printf("(enhancement) the center of gravity: (%f,%f,%f) \n", C_grav_x, C_grav_y, C_grav_z);


    // second points -> check whether point is within the boundary
    printf("Second points: Enter 4 values (negative luminosity for stop): \n");
    scanf("%lf %lf %lf %lf", &x, &y, &z, &luminosity);

    //
    // while loop until negative luminosity
    while (luminosity > 0.0)
    {

        Point3d point2; // temporary point2 to check the condition

	point2.ID = numID;
	point2.coordinates[0] = x;
	point2.coordinates[1] = y;
	point2.coordinates[2] = z;
	point2.luminosity = luminosity;

	numID++;
	
	printf("Checking whether the point intersects with the Pointset or not... \n");
	int sec = intersection(Point3ds, point2); // call the intersection function 
						  // to check whether point is within the boundary

	if (sec == 1)
	{
	    printf("This point intersects with the PointSet \n");
	}
	else
	{
	    printf("This point doesn't intersect with the PointSet \n");
	}


	printf("Enter 4 values again: \n");
	scanf("%lf %lf %lf %lf", &x, &y, &z, &luminosity); // again and again until - luminosity
    }

    printf("Good Bye \n");

    free(Point3ds.points); // free memory

    return 0;
}

// end of main
// 
// I failed to create a second PointSet from the second set of points read in
// and report the result of detecting the intersection of two PointSets (for enhancements), 
// but I can write a method to detect the intersection of two PointSets.
//
// In order for two PointSets to intersect, points in the two PointSets must intersect as well.
// Therefore, after adding x,y,z,lum values to second PointSet by the function, specifc value 
// from the user should satisfy two intersection functions (both return 1)
// In this algorithm, I can report the results for enhancements.
//
// However, I just wrote this down due to lack of time, and just in case for partial credit. 
// 
//





 

//
// addPointToSet
//
// This function is for adding the point to the pointset and execute main()
//
int addPointToSet( PointSet *set, Point3d point )
{

    for( int i=0; i<set->nPoints; i++) // for loop to find whether there are exact the same x,y,z, value
    {
	if (set->points[i].coordinates[0] == point.coordinates[0]
		       	&& set->points[i].coordinates[1] == point.coordinates[1]
		       && set->points[i].coordinates[2] == point.coordinates[2])
	{
	    return -1; // if there are, return -1 to manage execution.
	}
    }

    // add point to the pointset
    set->points[set->nPoints].ID = point.ID;
    set->points[set->nPoints].coordinates[0] = point.coordinates[0];
    set->points[set->nPoints].coordinates[1] = point.coordinates[1];
    set->points[set->nPoints].coordinates[2] = point.coordinates[2];

    if (set->nPoints == 0) // set initial execution
    {

	set->luminosity = point.luminosity;

	set->lower[0] = point.coordinates[0];
	set->lower[1] = point.coordinates[1];
	set->lower[2] = point.coordinates[2];

	set->upper[0] = point.coordinates[0];
	set->upper[1] = point.coordinates[1];
	set->upper[2] = point.coordinates[2]; // one point: actually no boundary!
    }
    else // main case after initial execution
    {
	set->luminosity = set->luminosity + point.luminosity; // add luminosity to calculate avg later

	if (point.coordinates[0] <= set->lower[0]) // below are setting; lower and upper arrays
	{
	    set->lower[0] = point.coordinates[0];
	}
	if (point.coordinates[0] >= set->upper[0])
	{
	    set->upper[0] = point.coordinates[0];
	}

	if (point.coordinates[1] <= set->lower[1])
	{
	    set->lower[1] = point.coordinates[1];
	}
	if (point.coordinates[1] >= set->upper[1])
	{
	    set->upper[1] = point.coordinates[1];
	}

	if (point.coordinates[2] <= set->lower[2])
	{
	    set->lower[2] = point.coordinates[2];
	}
	if (point.coordinates[2] >= set->upper[2])
	{
	    set->upper[2] = point.coordinates[2];
	}

    }

    set->nPoints++; 

    return 0;

}
   
//
// intersection
//
// This function is for checking whether points are within the boundary
//
int intersection( PointSet set, Point3d point )
{
    if (set.nPoints == 0) // no point; return 0
    {
	return 0;
    }
    else 
    {   //within the boundary
	if (point.coordinates[0] <= set.upper[0] && point.coordinates[0] >= set.lower[0]
			&& point.coordinates[1] <= set.upper[1] && point.coordinates[1] >= set.lower[1]
			&& point.coordinates[2] <= set.upper[2] && point.coordinates[2] >= set.lower[2])
	{
	    return 1;
	}
	else
	{
	    return 0;
	}
    }
}

// end
   
