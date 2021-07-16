/*
 * TODO: PointSet.h, Changjae Han, June 6 2021, PointSet.h file to set class definition
 */

#ifndef _POINTSET_H
#define _POINTSET_H

#include <cstdlib>
#include <iostream>
#include "Point3d.h"

using namespace std;  // Debatable.  Easier for now.

class PointSet {
	
	// Protected data memebers are accessible to descendants
	
	protected: 
	    Point3d ** points; // Dynamic array of POINTERS TO Point3d objects
	    int nPoints;
	    
	// Private data memebers - Descendants don't need access to these?
	
	private: 
	    int allocated;
	    double luminosity;
	    double lowerBounds[ 3 ];
	    double upperBounds[ 3 ];
	    
	// Public methods
	
	public: 
	    
	    // Two constructors and one destructor
	    PointSet( );
	    PointSet( int initialCapacity );
	    virtual ~PointSet( );
		
	    int getNumberOfPoints( ) const;
	    virtual bool addPoint( const Point3d & point ); // Child can override this
	    virtual bool addPoint( Point3d * pointPtr ); // Child can override this
	    Point3d * getPointByID( int id ) const;
	    bool intersect( Point3d point ) const;
	    void printStats( ostream & out ) const;
	    void printAll( ostream & out ) const;
};

#endif //_POINTSET_H
