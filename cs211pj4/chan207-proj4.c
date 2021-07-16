/******************************************************************************

    Project4: written by changjae han on May 31, 2021
    
    This project combines the pointset with the polygon and reaches the information
    by utilizing pointer.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Define typedef Point3d, PointSet, PointNode, and Polygon
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


typedef struct pointNode
{
    Point3d* point; // A pointer to a Point3d, located within a PointSet somewhere
    struct pointNode* next;
} PointNode;


typedef struct Polygon
{
    int ID;
    PointNode* points;
    int nPoints;
    double luminosity; 
    double lower[3], upper[3];
} Polygon;



#define X 0
#define Y 1
#define Z 2

#define TRUE 1
#define FALSE 0


// global variable: DebugMode
int DebugMode;


//function declaration
int addPointToSet( PointSet *set, Point3d point );
int addVertexToPolygon( Polygon *polygon, Point3d *temp );
Point3d * findPointAddress( PointSet set, int ID );
int polygonPointIntersection(Polygon poly, Point3d point);
int remove1stVertexFromPolygon(Polygon *polygon);


int main( int argc, char const *argv[ ] )
{
  
    // Set DeBugMode when -d is typed;
    const char *filename = NULL;
    for (int i=1; i<argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            DebugMode = TRUE;
        }
    }

    // Set dynamically allocated PointSet (allPoints) and initialize;
    PointSet *allPoints = (PointSet*)malloc(sizeof(PointSet));
    allPoints->allocated = 100;
    allPoints->points = (Point3d*)malloc((allPoints->allocated)*sizeof(Point3d));
    allPoints->nPoints = 0;
    allPoints->luminosity = 0.0;
    int id = 0;
    
    
    
    /****************************************************
      Input1: add point to pointset
    ****************************************************/
    if (DebugMode == TRUE)
    {
        printf("input1: reading x,y,z, and lum value");
    }
    
    printf("Enter 4 value: (x,y,z,lum)\n");
    double x,y,z,lum;
    scanf("%lf %lf %lf %lf", &x, &y, &z, &lum );
    while (lum >= 0.0) // loop until negative luminosity is entered.
    {
        Point3d pt;
        pt.ID = id;
        pt.coordinates[X] = x;
        pt.coordinates[Y] = y;
        pt.coordinates[Z] = z;
        pt.luminosity = lum;
        
        id++;
        
        int val = addPointToSet(allPoints,pt); // call addPointToSet to add point to pointset
        
        if (val == -1) // if impossible to add, free memory and exit program
        {
            free(allPoints->points);
            allPoints->points = NULL;
            free(allPoints);
            allPoints = NULL;
            exit(0);
        }
        
        printf("Enter 4 value: (x,y,z,lum)\n");
        scanf("%lf %lf %lf %lf", &x, &y, &z, &lum );
    }
  
    printf("input1 done\n");
    
    // output current information
    printf("given list\n");
    for (int i=0; i<allPoints->nPoints; i++)
    {
        printf("ID %d : ", allPoints->points[i].ID);
        printf("%.2lf ", allPoints->points[i].coordinates[0]);
        printf("%.2lf ", allPoints->points[i].coordinates[1]);
        printf("%.2lf ", allPoints->points[i].coordinates[2]);
        
        printf("\n");
    }
    printf("The number of points are: %d\n", allPoints->nPoints);
    printf("The average of luminosity is: %lf\n", allPoints->luminosity);
    
    printf("The dimension of bounding box X: lower %.2lf upper %.2lf\n", allPoints->lower[X], allPoints->upper[X]);
    printf("The dimension of bounding box Y: lower %.2lf upper %.2lf\n", allPoints->lower[Y], allPoints->upper[Y]);
    printf("The dimension of bounding box Z: lower %.2lf upper %.2lf\n", allPoints->lower[Z], allPoints->upper[Z]);
    
    
    
    
    
    
    printf("input2 start\n");
    
    // Set dynamically allocated Polygon (polygons) and initialize;
    int NUM = 100;
    Polygon *polygons = (Polygon*)malloc(NUM*sizeof(Polygon));
    memset(polygons, 0, NUM*sizeof(Polygon));
    polygons->points = NULL;
  
    int numID = 0;
    int numPolygon = 0;
    int number = 0;
    int index;
    double tempLum = 0.0;
    
    
    
    if (DebugMode == TRUE)
    {
        printf("input2: reading ID for polygon");
    }
    
    /***************************************************************
      Input2: add pointset to polygon until negative index in a row
    ***************************************************************/
    printf("Enter index for polygon ID: %d\n", numID);
    scanf("%d", &index );
    while (index >= 0)
    {
        // *2 allocated if need more space
        if (numPolygon == NUM) 
        {
            Polygon *oldpoly = polygons;
            polygons = (Polygon*)malloc(NUM*2*sizeof(Polygon));
            
            if (polygons == NULL)
            {
                polygons = oldpoly;
                oldpoly = NULL;
                return -1;
            }
            
            for (int i=0; i<numPolygon; i++)
            {
                polygons[i] = oldpoly[i];
            }
            
            free(oldpoly);
            oldpoly = NULL;
            NUM *=2;
        }
        
        
        // create temporary point to save its address, which is used for keeping track of information later
        Point3d * temp;
        
        temp = findPointAddress( *allPoints, index ); // call findPointAddress for the purpose above
        if (temp != NULL)
        {
            printf("Added\n");
            polygons[numID].ID = numID;
            polygons[numID].nPoints = number;
            int ret = addVertexToPolygon(&polygons[numID], temp); // call addVertexToPolygon to add address to polygon
            tempLum = tempLum + temp->luminosity;
            number++;
        }
        else
        {
            printf("This point doesn't exist..\n");
        }
        
        int index2;
        scanf("%d",&index2);
        while (index2 >= 0) // loop again
        {
            Point3d * temp2;
        
            temp2 = findPointAddress( *allPoints, index2 );
            if (temp2 != NULL)
            {
                printf("Added\n");
                polygons[numID].ID = numID;
                polygons[numID].nPoints = number;
                int ret = addVertexToPolygon(&polygons[numID], temp2);
                tempLum = tempLum + temp2->luminosity;
                number++;
            }
            else
            {
                printf("This point doesn't exist..\n");
            }
            scanf("%d", &index2);
        }
        
        polygons[numID].nPoints = number;
        polygons[numID].luminosity = tempLum/number;
      
        number = 0;
        tempLum = 0.0;
        numID++;
        numPolygon++;
        
        printf("Enter index for polygon ID: %d\n", numID);
        scanf("%d", &index);
    }
    
    
    // output current information
    printf("You have made %d polygons:\n", numID);
    printf("Processing the address of vertices of each Polygon...\n");
    
    if (numID == 0) // if there is no polygon, free memory and exit program 
    {
        printf("Since you didn't make any polygons, program out..\n");
        free(allPoints->points);
        free(allPoints);
        free(polygons);
        allPoints = NULL;
        polygons = NULL;
        exit(0);
    }
    
    printf("Storing address..\n");
    printf("average luminosity, lower, and upper\n");
    for (int j=0; j<numID; j++)
    {
        printf("polygon ID: %d\n", polygons[j].ID);
        printf("avg luminosity %.2lf\n", polygons[j].luminosity);
        printf("lower_x %.2lf, upper_x %.2lf\n",polygons[j].lower[0], polygons[j].upper[0]);
        printf("lower_y %.2lf, upper_y %.2lf\n",polygons[j].lower[1], polygons[j].upper[1]);
        printf("lower_z %.2lf, upper_z %.2lf\n",polygons[j].lower[2], polygons[j].upper[2]);
        printf("\n");
        
    }
    
    

    if (DebugMode == TRUE)
    {
        printf("input3: reading x,y,z, and lum value for intersections");
    }
    
    /************************************************************************************************************
      Input3: compare points with polygons to find whether there are intersections until negative index in a row
    ************************************************************************************************************/
    int newID = 0;
    printf("Enter second sets of points: (x,y,z,lum)\n");
    double x2,y2,z2,lum2;
    scanf("%lf %lf %lf %lf", &x2, &y2, &z2, &lum2 );
    while (lum2 >= 0.0)
    {
        Point3d newpt; // create new point
        newpt.ID = newID;
        newpt.coordinates[X] = x2;
        newpt.coordinates[Y] = y2;
        newpt.coordinates[Z] = z2;
        newpt.luminosity = lum2;
        
        newID++;
        
        for (int i=0; i<numID; i++)
        {
            int intersect = polygonPointIntersection(polygons[i],newpt); // call polygonPointIntersection function for intersections
            
            if (intersect == 0)
            {
                printf("This point doesn't intersect with polygon ID: %d \n", i);
            }
            else
            {
                printf("This point and polygon ID: %d intersected!\n", i);
            }
        }
        
        printf("Enter 4 value: (x,y,z,lum)\n");
        scanf("%lf %lf %lf %lf", &x2, &y2, &z2, &lum2 );
    }
    
    
    // free temporarily allocated memory when adding vertex to polygon, and remove all linked lists
    int r1=0;
    int rem;
    for (int i=0; i<numID; i++)
    {
        while ((rem = remove1stVertexFromPolygon(&polygons[i])) != -1)
        {
            r1++; // nothing happen
        }
    }
   
    printf("Good Bye\n");

    // free memory
    free(allPoints->points);
    free(allPoints);
    free(polygons);
    allPoints = NULL;
    polygons = NULL;
    
    return 0;
}
// End of main






 /******************************
      Function Information
  ******************************/


//
// remove1stVertexFromPolygon
//
// remove first vertex from polygon by assigning head;
// remove node between head and next node, then link each other
int remove1stVertexFromPolygon(Polygon *polygon)
{
    if (polygon->points == NULL) // no node
    {
        return -1;
    }
    
    PointNode *head = polygon->points;
    polygon->points = polygon->points->next;
    
    free(head);
    head = NULL;
    polygon->nPoints--;
    
    return 0;
}


//
// polygonPointIntersection
//
// Find intersection if each point coordinates is lower than polygon lower,
// and is higher than polygon upper
int polygonPointIntersection(Polygon poly, Point3d point)
{
    int posCount = 0;
    if (poly.nPoints == 0)
    {
        return 0;
    }
    else 
    {
        for (int i=0; i<3; i++)
        {
            if (point.coordinates[i] >= poly.lower[i] && point.coordinates[i] <= poly.upper[i]) // check condition
            {
                posCount++;
            }
        }
        
        //return 0; 
    }
    if (posCount == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//
// addVertexToPolygon
//
// add vertex to polygon by allocating new pointnode and assign information.
// This function also saves lower and upper information of polygon
int addVertexToPolygon(Polygon *polygon, Point3d *temp)
{
    if (polygon == NULL)
    {
        return -1;
    }
    
    if (polygon->nPoints == 0)
    {
        for (int i=0; i<3; i++)
        {
            polygon->lower[i] = polygon->upper[i] = temp->coordinates[i];
        }
    }
    
    PointNode *pn = (PointNode*)malloc(sizeof(PointNode)); // create dynamically allocated pointnode
    
    if (pn == NULL)
    {
        return -1;
    }
    
    // save information
    pn->point = temp; 
    pn->next = polygon->points;
    polygon->points = pn;
    
    for (int i=0; i<3; i++) // assign lower and upper information of polygon by comparing existing value
    {
        polygon->lower[i] = polygon->lower[i] <= temp->coordinates[i] ? polygon->lower[i] : temp->coordinates[i];
        polygon->upper[i] = polygon->upper[i] >= temp->coordinates[i] ? polygon->upper[i] : temp->coordinates[i];
    }
    
    return 0;
    
}


//
// findPointAddress
//
// return the address of point in pointset
Point3d * findPointAddress( PointSet set, int ID )
{
    int i = 0;
    int stack = 0;
    for (i=0; i<set.nPoints; i++)
    {
        if (set.points[i].ID != ID)
        {
            stack++;
        }
        else
        {
            break;
        }
    }
    if (stack == set.nPoints)
    {
        return NULL;
    }
    else
    {
        return &set.points[i];
    }

}



//
// addPointToSet
//
// add point to pointset 
// This funciton also saves lower and upper information of pointset
int addPointToSet(PointSet *set, Point3d point)
{
    if (set->nPoints == 0)
    {
        for (int i=0; i<3; i++)
        {
            set->lower[i] = set->upper[i] = point.coordinates[i];
        }
    }
    
    //increase allocated size when it is full.
    if (set->nPoints == set->allocated)
    {
        Point3d *prev = set->points;
        set->points = (Point3d*)malloc((set->allocated)*2*sizeof(Point3d));
        
        if (set->points == NULL)
        {
            set->points = prev;
            prev = NULL;
            return -1;
        }
        
        for (int i=0; i<set->nPoints; i++)
        {
            set->points[i] = prev[i];
        }
        
        free(prev);
        prev = NULL;
        set->allocated *=2;
    }
    
    set->points[set->nPoints] = point;
    set->nPoints++;
    set->luminosity = (set->luminosity * (set->nPoints - 1) + point.luminosity)/ set->nPoints;
    
    for (int i=0; i<3; i++)
    {
        if (point.coordinates[i] <= set->lower[i])
        {
            set->lower[i] = point.coordinates[i];
        }
        if (point.coordinates[i] >= set->upper[i])
        {
            set->upper[i] = point.coordinates[i];
        }
    }
    
    return 0;
}



// END //
