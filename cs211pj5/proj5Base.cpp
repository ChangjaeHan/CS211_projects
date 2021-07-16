/*
 *  TODO:  PointSet.cpp, Changjae Han, June 2, PointSet.cpp file to set function in public realm
 *
 *	TODO:  Create a makefile and use make.
 *         In the meantime, the following command will build proj5Base:
 *
 *         gcc -g -o proj5Base proj5Base.cpp Point3d.cpp PointSet.cpp
 */

#include <string.h>
#include <cstdlib>
#include <iostream>
#include "Point3d.h"
#include "PointSet.h"
 
using namespace std;	// Debatable, but easier for now.
  


#define TRUE 1
#define FALSE 0

// set DebugMode
int DebugMode = FALSE;



int main( int argc, char ** argv ) 
{
 	
    
    for (int i=0; i<argc; i++)
    {
        cout << "Argv[" << i << "] = " << argv[i] << endl;
        if (strcmp(argv[i], "-d") == 0)
        {
            DebugMode = TRUE;
        }
    }
    
    PointSet set1; // create set1
    
    cout << "First pointset" << endl;
    cout << "Enter x, y, z, luminosity value (negative lum = quit)" << endl;
    
    double X, Y, Z, Lum;     
    cin >> X;
    cin >> Y;
    cin >> Z;
    cin >> Lum;
    while (Lum >= 0.0) // loop until negative luminosity is entered
    {
        
        Point3d point(X, Y, Z, Lum); 
               
        if (set1.addPoint(point)) // call addPoint function to check whether the point can be added and save the point. 
        {
            cout << "Successfully added" << endl;
        }
        else
        {
            cout << "failed" << endl;
        }
                   
        cout << "input x, y, z, luminosity value" << endl;
        cin >> X;
        cin >> Y;
        cin >> Z;
        cin >> Lum;
    }

    if (set1.getNumberOfPoints() == 0) // when negative luminosity is entered at the beginning
    {
	cout << "You didn't make any points" << endl;
	cout << "Good Bye!" << endl;
	return 0;
    }

    cout << endl;
    cout << "You have made " << set1.getNumberOfPoints() << " point set." << endl;
    set1.printStats( cout ); // call the printStats function to show the output
    
    
    if (DebugMode)
    {
        cout << "[DebugMode]: finish reading x,y,z, and lum value for adding points" << endl;
    }
     
    
    cout << endl;
    cout << "Second pointset" << endl;
    cout << "Enter x, y, z, luminosity value (negative lum = quit)" << endl;
    
    double X2, Y2, Z2, Lum2;     
    cin >> X2;
    cin >> Y2;
    cin >> Z2;
    cin >> Lum2;
    while (Lum2 >= 0.0) // loop until negative luminosity is entered
    {
        
        Point3d point2(X2, Y2, Z2, Lum2);
        
        cout << "Entered point is {" << X2 << ", " << Y2 << ", " << Z2 << "} luminosity: " << Lum2 << endl;
        cout << "Checking whether point intersects or not..." << endl;
        
        if (set1.intersect(point2)) // call the intersect function to check whether the point intersects or not
        {
            cout << "Intersect!" << endl;            
        }
        else
        {
            cout << "This point doesn't intersect..." << endl;
        }
                   
        cout << "input x, y, z, luminosity value" << endl;
        cin >> X2;
        cin >> Y2;
        cin >> Z2;
        cin >> Lum2;
    }
    
    if (DebugMode)
    {
        cout << "[DebugMode]: finish reading x,y,z, and lum value for checking intersection" << endl;
    }
    
    
    cout << endl;
    cout << "Good Bye!" << endl;
	
    return 0;
  	
} // main
 
