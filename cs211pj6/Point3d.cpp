/*
 * TODO: Point3d.cpp, Changjae Han, June 6 2021, Point3d.cpp file to utilize functions defined on Point3d.h
 */

#include "Point3d.h"

/*
 * Point3d implementation
 */
 
// Initialize the static int class variable.
int Point3d::nextID = 0;
 
//Set initial values in constructor.  Make getters functional
Point3d::Point3d()
{
    this->ID = 0;
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
    this->luminosity = 0.0;  
}


// Two constructors
// Note that the first one  must assign a new unique value to ID, 
// making use of static int nextID
Point3d::Point3d( double X,  double Y,  double Z,  double luminosity ) 
{
	
    this->ID = nextID;
    nextID++;
    
    this->X = X; 
    this->Y = Y;
    this->Z = Z;
    this->luminosity = luminosity;
    
}

// copy constructor
Point3d::Point3d( const Point3d & point ) 
{
	
    this->ID = point.ID;
    this->X = point.X;	
    this->Y = point.Y;
    this->Z = point.Z;
    this->luminosity = point.luminosity;
        
}

// Destructor
Point3d::~Point3d( ) {
	
}

// Getters return class values
int Point3d::getID( ) const 
{
    return this->ID;
}

double Point3d::getX( ) const 
{
    return this->X;
}

double Point3d::getY( ) const 
{
    return this->Y;
}

double Point3d::getZ( ) const 
{
    return this->Z;
}

double Point3d::getLuminosity( ) const 
{
    return this->luminosity;
}

 
// The following method allows code like this, where p is a Point3d:
//			cout << "Point p = " << p << endl;
ostream & operator << ( ostream & out, const Point3d & point ) 
{ 	
    out << "( X: " << point.getX( ); 	
    out << " Y: " << point.getY( );
    out << " Z: " << point.getZ( );
    out << " luminosity: " << point.getLuminosity( );     
    out << " )";
 	
    return out; 	
 	
} // operator << ( ostream &, Point3d )
