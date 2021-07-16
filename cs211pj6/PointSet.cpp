/*
 * TODO: PointSet.cpp, Changjae Han, June 6 2021, Point3d.cpp file to utilize functions defined on PointSet.h
 */

#include <typeinfo>
#include "PointSet.h"

using namespace std; 


//No-argument constructor.  Set allocated to 10 by default
PointSet::PointSet( ) {
        
    this->allocated = 10; // set 10 by default
    this->points = new Point3d*[this->allocated];
    for (int i=0; i<this->allocated; i++)
    {
        this->points[i] = nullptr; 
    }
    
    this->luminosity = 0.0;
    
    for (int i=0; i<3; i++)
    {
        this->lowerBounds[i] = this->upperBounds[i] = 0.0;
    }
    this->nPoints = 0;

} // Constructor ( )


// Constructor with an argument. 
// Set allocated to the value of the passed-in argument
PointSet::PointSet( int initialCapacity) {
       
    this->allocated = initialCapacity; // set initialCapacity 
    this->points = new Point3d*[this->allocated];
    for (int i=0; i<this->allocated; i++)
    {
        this->points[i] = nullptr; 
    }
    
    this->luminosity = 0.0;
    
    for (int i=0; i<3; i++)
    {
        this->lowerBounds[i] = this->upperBounds[i] = 0.0;
    }
    this->nPoints = 0;

} // Constructor( int )

// Destructor needs to free all associated dynamic memory
// This includes all the dynamically allocated Point3ds
// AND the dynamically allocated array holding them.
PointSet::~PointSet( ) {
    
    if (typeid(*this) == typeid(PointSet))
    {
        for (int i=0; i<this->nPoints; i++)
        {
            delete this->points[i];
        }       
    }   

} // Destructor


// count number of points
int PointSet::getNumberOfPoints( ) const {
    
    return this->nPoints;

} // getNumberOfPoints


// Add a point to the set. Take & parameter
bool PointSet::addPoint( const Point3d & point ) {
	
    Point3d *newPoint = new Point3d(point);    
    
    if (newPoint == nullptr)
    {
        return false;
    }
        
    return addPoint(newPoint); // pass to addPoint(Point3d *pointPtr)
	
} // addPoint( const Pointe3d & point )


// Add a point to the set. Take * parameter
bool PointSet::addPoint(  Point3d * pointPtr ) {
	
    if (this->nPoints == this->allocated) // increases point size when it is full
    {
        Point3d **old = this->points;
        this->points = new Point3d*[2*this->allocated];
        if (this->points == nullptr)
        {
            this->points = old;
            old = nullptr;
            return false;
        }
        for (int i=0; i<this->nPoints; i++)
        {
            this->points[i] = old[i];
        }
        delete[] old;
        old = nullptr;
        this->allocated = this->allocated*2;       
    }
    
    for (int i=0; i<this->nPoints; i++)
    {        
        if (pointPtr->getID() == this->points[i]->getID()) // when point already exists
        {
            cout << "point already exist " << endl;
            return false;
        }
    }
    
    this->points[this->nPoints] = pointPtr; // add the point
    
    if (this->nPoints == 0) // set initial bounds
    {
        this->lowerBounds[0] = this->upperBounds[0] = pointPtr->getX(); 
        this->lowerBounds[1] = this->upperBounds[1] = pointPtr->getY();
        this->lowerBounds[2] = this->upperBounds[2] = pointPtr->getZ();
    }
    
    this->nPoints++;
    this->luminosity = (this->luminosity * (this->nPoints - 1) + pointPtr->getLuminosity())/this->nPoints; // calculate average luminosity
    
    if (pointPtr->getX() <= this->lowerBounds[0]) // setting upper and lower bounds
    {
        this->lowerBounds[0] = pointPtr->getX();
    }
    if (pointPtr->getX() >= this->upperBounds[0])
    {
        this->upperBounds[0] = pointPtr->getX();
    }
    if (pointPtr->getY() <= this->lowerBounds[1])
    {
        this->lowerBounds[1] = pointPtr->getY();
    }
    if (pointPtr->getY() >= this->upperBounds[1])
    {
        this->upperBounds[1] = pointPtr->getY();
    }
    if (pointPtr->getZ() <= this->lowerBounds[2])
    {
        this->lowerBounds[2] = pointPtr->getZ();
    }
    if (pointPtr->getZ() >= this->upperBounds[2])
    {
        this->upperBounds[2] = pointPtr->getZ();
    }
    
    return true;

} // addPoint

// Return true if there is an intersection, false otherwise
bool PointSet::intersect( Point3d point ) const {
    
    if (point.getX() >= this->lowerBounds[0] && point.getX() <= this->upperBounds[0]) // check whether it is in the bounds
    {
        if (point.getY() >= this->lowerBounds[1] && point.getY() <= this->upperBounds[1])
        {
            if (point.getZ() >= this->lowerBounds[2] && point.getZ() <= this->upperBounds[2])
            {
                return true; 
            }
        }
    }
    return false;   
    
} // intersect

// The following function "prints" to outStream all the information about
// a PointSet, except the actual points themselves.
void PointSet::printStats( ostream & outStream ) const {
	
    outStream << "This point set has " << nPoints << " stored out of " << allocated << " available.\n";
	
    outStream << "Average luminosity: " << luminosity << endl;
    outStream << "Upper bounds for X,Y,Z [" << upperBounds[0] << ", " << upperBounds[1] << ", " << upperBounds[2] << "]" << endl;
    outStream << "Lower bounds for X,Y,Z [" << lowerBounds[0] << ", " << lowerBounds[1] << ", " << lowerBounds[2] << "]" << endl;
    
    return;

} // printStats

// The following function "prints" to outStream all the information about
// a PointSet, INCLUDING ALL POINTS, regardless of their ID
void PointSet::printAll( ostream & outStream ) const {
	
    printStats( outStream ); // First call the other function for basics
	
    for (int i=0; i<nPoints; i++)
    {
        outStream << "Actual points ID: "<< i << " {";
        outStream << *points[i] << endl;
    }
	
    return;

} // printStats

// Return the address of the point with the given ID, or NULL otherwise
Point3d * PointSet::getPointByID( int id ) const {
	
    for (int i=0; i<this->nPoints; i++)
    {        
        if (id == this->points[i]->getID()) // when id corresponds
        {
            return this->points[i];
        }
    }
   
    return NULL; 

} // getPointByID

