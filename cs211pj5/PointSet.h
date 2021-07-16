/*
 * TODO: PointSet.h, Changjae Han, June 2, PointSet.h file to set class definition.
 */

#ifndef _POINTSET_H
#define _POINTSET_H

#include <cstdlib>
#include <iostream>
#include "Point3d.h"

using namespace std;  // Debatable.

class PointSet {
	
	// Private data memebers
	
	private: 
	    Point3d ** points; // Dynamic array of POINTERS TO Point3d objects
	    int nPoints;
	    int allocated;
	    double luminosity;
	    double lowerBounds[ 3 ];
	    double upperBounds[ 3 ];
	    
	// Public methods
	
	public: 
	    
	    // Two constructors and one destructor
	    PointSet( );
	    PointSet( int initialCapacity );
	    ~PointSet( );
		
	    int getNumberOfPoints( );
	    bool addPoint( const Point3d & point );
	    Point3d * getPointByID( int id );
	    bool intersect( const Point3d & point );
	    void printStats( ostream & out );
	    void printAll( ostream & out );
};

#endif //_POINTSET_H
