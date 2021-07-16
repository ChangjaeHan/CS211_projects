/*
 * TODO: Point3d.cpp, Changjae Han, June 2, point3d cpp file to set function in public realm.
 */

#include "Point3d.h"

/*
 * Point3d implementation
 */
 
// Initialize the static int class variable.
int Point3d::nextID = 0;
 

// Add constructor to initialize values in private realm  
Point3d::Point3d()
{
    this->ID = 0;
    for(int i=0; i<3; i++)
    {
        this->coordinates[i] = 0;
    }
    this->luminosity = 0.0;
}


// Two constructors
// Note that the first one  must assign a new unique value to ID, 
// making use of static int nextID
Point3d::Point3d( double X,  double Y,  double Z,  double luminosity ) {
	
	
    this->ID = Point3d::nextID++; // ID increases from 0; it can also be used as nextID 
    this->coordinates[0] = X;     // Set X, Y, Z, luminosity values
    this->coordinates[1] = Y;
    this->coordinates[2] = Z;	
    this->luminosity = luminosity;	

}



// copy constructor
Point3d::Point3d( const Point3d & point ) {
    
    this->ID = point.ID;
    this->coordinates[0] = point.coordinates[0];
    this->coordinates[1] = point.coordinates[1];
    this->coordinates[2] = point.coordinates[2];

    this->luminosity = point.luminosity;

}

// Destructor
Point3d::~Point3d( ) {
	
}

// Getters return class values
int Point3d::getID( ) {

    return this->ID;
}

double  Point3d::getX( ) const {

    return this->coordinates[0];
}

double Point3d::getY( ) const {

    return this->coordinates[1];
}

double Point3d::getZ( ) const {

    return this->coordinates[2];
}

double Point3d::getLuminosity( ) const {

    return this->luminosity;
}

//ostream & operator
ostream & operator << ( ostream & out, const Point3d & point ) {
 	
    out << "( X: " << point.getX( ); 	// print out X,Y,Z value
    out << " Y: " << point.getY();
    out << " Z: " << point.getZ();     
    out << " )";
 	
    return out;  // Allows multiple << operators on a line as shown above.	
 	
}

