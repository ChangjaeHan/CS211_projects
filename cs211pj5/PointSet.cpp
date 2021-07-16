/*
 * TODO: PointSet.cpp, Changjae Han, June 2, PointSet.cpp file to set function in public realm
 */

#include "PointSet.h"

using namespace std; // Debatable


// No-argument constructor.  Set allocated to 10 by default
PointSet::PointSet( ) {
      
    this->nPoints = 0;
    this->allocated = 10;
    this->points = new Point3d*[this->allocated];
    this->luminosity = 0.0;
    
    for (int i=0; i<3; i++)
    {
        this->lowerBounds[i] = this->upperBounds[i] = 0;
    }
} // Constructor ( )


// Constructor with an argument. 
// Set allocated to the value of the passed-in argument
PointSet::PointSet( int initialCapacity) {
    
    
    this->nPoints = 0;
    this->allocated = initialCapacity;
    this->points = new Point3d*[this->allocated];
    this->luminosity = 0.0;
    
    for (int i=0; i<3; i++)
    {
        this->lowerBounds[i] = this->upperBounds[i] = 0;
    }
    
    
} // Constructor( int )


// Destructor needs to free all associated dynamic memory
// This includes all the dynamically allocated Point3ds
// AND the dynamically allocated array holding them.
PointSet::~PointSet( ) {

    delete[] this->points;
    
} // Destructor


// getNumberOfPoints: count points
int PointSet::getNumberOfPoints( ) {
    
    return this->nPoints;
    
} // getNumberOfPoints


// addPoint: add point to pointset
// dynamically allocated points, which can grow if needed and save information
bool PointSet::addPoint( const Point3d & point ) {
    
  
    Point3d *newPoint = new Point3d(point);    
    
    if (this->nPoints == this->allocated)
    {
        Point3d **old = this->points;
        this->points = new Point3d*[2*this->allocated];
        if (this->points == NULL)
        {
            this->points = old;
            old = NULL;
            return false;
        }
        for (int i=0; i<this->nPoints; i++)
        {
            this->points[i] = old[i];
        }
        delete[] old;
        old = NULL;
        this->allocated = this->allocated*2;       
    }

    this->points[this->nPoints] = newPoint;
    
    if (this->nPoints == 0)
    {
        this->lowerBounds[0] = this->upperBounds[0] = newPoint->getX();
        this->lowerBounds[1] = this->upperBounds[1] = newPoint->getY();
        this->lowerBounds[2] = this->upperBounds[2] = newPoint->getZ();
    }
    
    this->nPoints++;
    this->luminosity = (this->luminosity * (this->nPoints - 1) + newPoint->getLuminosity())/this->nPoints;
    
    if (newPoint->getX() <= this->lowerBounds[0])
    {
        this->lowerBounds[0] = newPoint->getX();
    }
    if (newPoint->getX() >= this->upperBounds[0])
    {
        this->upperBounds[0] = newPoint->getX();
    }
    if (newPoint->getY() <= this->lowerBounds[1])
    {
        this->lowerBounds[1] = newPoint->getY();
    }
    if (newPoint->getY() >= this->upperBounds[1])
    {
        this->upperBounds[1] = newPoint->getY();
    }
    if (newPoint->getZ() <= this->lowerBounds[2])
    {
        this->lowerBounds[2] = newPoint->getZ();
    }
    if (newPoint->getZ() >= this->upperBounds[2])
    {
        this->upperBounds[2] = newPoint->getZ();
    }
 
    delete(newPoint);
    newPoint = NULL;
    
    return true;
    

} // addPoint


// intersect: return true if there is an intersection or false otherwise
bool PointSet::intersect( const Point3d & point ) {
      
    if (point.getX() >= this->lowerBounds[0] && point.getX() <= this->upperBounds[0])
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


// printStats: "prints" to outStream all the information about a PointSet,
// except the actual points themselves.
void PointSet::printStats( ostream & outStream ) {
	
    outStream << "This point set has " << nPoints << " stored out of " << allocated << " available.\n";
	
    outStream << "Average luminosity: " << luminosity << endl;
    outStream << "Upper bounds for X,Y,Z [" << upperBounds[0] << ", " << upperBounds[1] << ", " << upperBounds[2] << "]" << endl;
    outStream << "Lower bounds for X,Y,Z [" << lowerBounds[0] << ", " << lowerBounds[1] << ", " << lowerBounds[2] << "]" << endl;
    
    return;

} // printStats


// printAll: "prints" to outStream all the information about a PointSet,
// including the actual points themselves.
void PointSet::printAll( ostream & outStream ) {
	
    outStream << "This point set has " << nPoints << " stored out of " << allocated << " available.\n";
		
    outStream << "Average luminosity: " << luminosity << endl;
    outStream << "Upper bounds for X,Y,Z " << upperBounds[0] << ", " << upperBounds[1] << ", " << upperBounds[2] << endl;
    outStream << "Lower bounds for X,Y,Z " << lowerBounds[0] << ", " << lowerBounds[1] << ", " << lowerBounds[2] << endl;
    
    for (int i=0; i<nPoints; i++)
    {
        outStream << "Actual points ID: "<< i << " {";        
        outStream << points[i]->getX() << ", ";
        outStream << points[i]->getY() << ", ";
        outStream << points[i]->getZ() << "}" << endl;       
    }
        
    return;

} // printAll


// getPointByID: Return the address of the point with the given ID, or NULL otherwise
Point3d * PointSet::getPointByID( int id ) {
    
    for (int i=0; i<this->nPoints; i++)
    {
        if (id == points[i]->getID())
        {
            return this->points[i];
        }
    }
   
    return NULL; 

} // getPointByID



