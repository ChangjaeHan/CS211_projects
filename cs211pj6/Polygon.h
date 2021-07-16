/*
 *  TODO: Polygon.h, Changjae Han, June 6 2021, Polygon.h file to set class definition
 */


#ifndef _POLYGON_H
#define _POLYGON_H

#include "PointSet.h"


class Polygon: public PointSet {
	
	private: 
		// Private data
	        double normal[ 3 ];
	    
	    // Private methods
		void calcNormal( );
		void calcVector( const Point3d & start, const Point3d & finish, 
			double result[ 3 ] ) const;
		void cross( const double vec1[ 3 ], const double vec2[ 3 ], 
			double result[ 3 ] ) const;
		double dot( const double vec1[ 3 ], const double vec2[ 3 ] ) const;
	    
	public: 
	    
	    // Constructors and destructor
		Polygon( );
		Polygon( int initialCapacity );
		~Polygon( );
	    
		virtual bool addPoint( const Point3d & point );
		virtual bool addPoint(  Point3d * pointPtr );
		bool isCoplanar( const Point3d & point ) const;
                void printAll( ostream & outStream ) const; 
                void setNormal(); 
};

// TODO:  Add a means of printing Polygons, either as class methods or by operator <<

#endif //_POLYGON_H
