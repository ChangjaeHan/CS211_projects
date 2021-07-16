/*
 * TODO: Point3d.h, Changjae Han, June 2, Point3d.h file to set class definition
 */


#ifndef _POINT3D_H
#define _POINT3D_H

#include <cstdlib>
#include <iostream>
#include <ostream>

using namespace std;  // Debateable, but makes things easier.

class Point3d {
	
	/* Private data members */
		
	private: 
	    static int nextID;
	    int ID;
	    double coordinates[ 3 ];
	    double luminosity;
	    
	/* Public methods */
	
	public: 
	    
		// Three constructors and one destructor
            Point3d( ); // added
	    Point3d( double X, double Y, double Z, double luminosity );
	    Point3d( const Point3d & point ); // Copy constructor
	    ~Point3d( );
		
	    // Getters
	    int getID( );    
	    double getX( ) const;    
	    double getY( ) const;    
	    double getZ( ) const;    
	    double getLuminosity( ) const;

};

// non-class function to allow cout << Point3d statements.
ostream & operator << ( ostream & out, const Point3d & point );

#endif //_POINT3D_H
