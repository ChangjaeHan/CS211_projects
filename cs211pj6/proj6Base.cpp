/*
 *  TODO: proj6Base.cpp, Changjae Han, June 6, proj6Base.cpp file to execute main function with point3d, pointset, polygon
 */
#include <cstring>
#include <typeinfo>
#include <cstdlib>
#include <iostream>
#include "Point3d.h"
#include "PointSet.h"
#include "Polygon.h"
 
using namespace std;	
 

#define TRUE 1
#define FALSE 0

// set DebugMode
int DebugMode = FALSE;




int main( int argc, char ** argv ) {
 	
//#ifdef DEBUG

 	
    for (int i=0; i<argc; i++)
    {
        cout << "Argv[" << i << "] = " << argv[i] << endl;
        if (strcmp(argv[i], "-d") == 0)
        {
            DebugMode = TRUE;
        }
    }
    
    // set PointSet allPoints
    PointSet allPoints;
    
    cout << "Create pointset" << endl;
    cout << "Enter x, y, z, luminosity value" << endl;
    
 	/*********/
    /* part1 */
    /*********/
    double X, Y, Z, Lum;     
    cin >> X >> Y >> Z >> Lum;   
    while (Lum >= 0.0) // Enter x,y,z,lum value and set
    {
        
        Point3d point(X, Y, Z, Lum); 
        
        if (allPoints.addPoint(point)) // call addPoint to add points to pointset
        {
            cout << "Successfully added" << endl;
        }
        else
        {
            cout << "failed" << endl;
        }
        
        cout << "input x, y, z, luminosity value" << endl;
        cin >> X >> Y >> Z >> Lum;
    }
    
    if (allPoints.getNumberOfPoints() == 0) // You have never made the points.
    {
        cout << "You didn't make any points" << endl;
        return 0;
    }
    
    cout << endl;
    cout << "You have made " << allPoints.getNumberOfPoints() << " point set." << endl;
    allPoints.printAll( cout );
    cout << endl;
    
    if (DebugMode)
    {
        cout << "[DebugMode]: Part1 Complete: finish reading x,y,z, and lum value for adding points" << endl;
    }
    
    
    
    
    /*********/
    /* part2 */
    /*********/
     int allocatePolygon = 10;
     int numPolygon = 0;
     int numID = 0;
   
     // Create dynamically allocated polygons
     Polygon *polygons = new Polygon[allocatePolygon];     
     
    
     int vertexID;
     cout << "Enter index for polygon ID: " << endl;
     cin >> vertexID;
     while (vertexID >= 0 )
     {
         
        if (numPolygon == allocatePolygon) // increases size when it is full
        {
            Polygon *oldpoly = polygons;
            polygons = new Polygon[allocatePolygon*2];
            
            if (polygons == nullptr)
            {
                polygons = oldpoly;
                oldpoly = nullptr;
                return -1;
            }            
            for (int i=0; i<numPolygon; i++)
            {
                polygons[i] = oldpoly[i];
            }            
            free(oldpoly);
            oldpoly = nullptr;
            allocatePolygon *=2;
        }
         
         
        Point3d * temp1;        
        temp1 = allPoints.getPointByID(vertexID ); // call getPointByID to find whether point exists on the pointset.
               
        if (temp1 != NULL)
        {            
            polygons[numID].addPoint(*temp1); // call addPoint when point exists on the pointset     
        }
        else
        {
            cout << "This point doesn't exist.." << endl;
        }
        
        int vertexID2; 
        cin >> vertexID2;
        while (vertexID2 >= 0 ) // repeat above
        {
            Point3d * temp2;
        
            temp2 = allPoints.getPointByID(vertexID2 );
            if (temp2 != NULL)
            {              
                polygons[numID].addPoint(*temp2);             
            }
            else
            {
                cout << "This point doesn't exist.." << endl;
            }        
            cin >> vertexID2;
        }

        numID++;
        numPolygon++;
        
        cout << "Enter index for polygon ID: " << endl;
        cin >> vertexID;
     }
     
     for (int i=0; i<numID; i++) // show each polygon's member
     {
         cout << "Polygon " << i << " is:  ";
         polygons[i].printAll(cout);
     }
    
     cout << endl;
    
     if (DebugMode)
     {
	 cout << "[DebugMode]: Part2 Complete: meet conditions and add point to polygon" << endl;
     }


    
    /*********/
    /* part3 */
    /*********/
     cout << "input x, y, z, luminosity value" << endl;
     double X2, Y2, Z2, Lum2;
     cin >> X2 >> Y2 >> Z2 >> Lum2;
    
     while (Lum2 > 0.0)
     {
         
         Point3d newpoint(X2, Y2, Z2, Lum2); // Create new point 
         
         cout << "Entered point is {" << X2 << ", " << Y2 << ", " << Z2 << "} luminosity: " << Lum2 << endl;
         cout << "Checking whether point intersects or not..." << endl;
         cout << endl;
         
         
         //Checking:
         //1. whether point intersect or not with pointset
         //2. whether point intersect or not with polygon
         //3. whether point is coplanar or not
         
         
         cout << "First check whether it intersects with pointset" << endl;
         
         if (allPoints.intersect(newpoint)) // call the intersect function to check whether the point intersects or not
         {
             cout << "Intersect with pointset!" << endl;            
         }
         else
         {
             cout << "This point doesn't intersect with pointset" << endl;
         }
         cout << endl;
         
         cout << "Second check whether it intersects with polygon" << endl;
        
         for (int i=0; i<numID; i++)
         {
             
             if (polygons[i].intersect(newpoint))
             {
                 cout << "Intersect with polygon[" << i << "]"<< endl;
             }
             else
             {
                 cout << "This point doesn't intersect with polygon[" << i << "]" << endl;
             }
             
         }
         cout << endl;
         
         cout << "Final check whether it is coplanar" << endl;
         
         for (int i=0; i<numID; i++)
         {
            
             polygons[i].setNormal(); // call to set normal if the number of points are over 3
             
             if (polygons[i].isCoplanar(newpoint)) // call isCoplanar to check whether it is coplanar or not
             {
                 cout << "It is coplanar to polygon[" << i << "]" << endl;
             }
             else
             {
                 cout << "Not coplanar to polygon[" << i << "]" << endl;
             }
         }
         cout << endl;
                   
         cout << "input x, y, z, luminosity value" << endl;
         cin >> X2 >> Y2 >> Z2 >> Lum2;         
     }

     if (DebugMode)
     {
	 cout << "[DebugMode]: Part3 complete: check points whether it intersects and is coplanar" << endl;
     }

    
     cout << "Good Bye" << endl; 
    
    
   
     // free dynamically allocated array
     delete[] polygons;
     polygons = NULL;
      
   
     return 0;
  	
 } // main
 


//
// I succeeded to implement code but failed to free all arrays which are dynamically allocated
// I will keep trying to find the reason for failure to free after deadline :)
//  
