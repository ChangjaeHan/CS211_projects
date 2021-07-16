/*
 * TODO: Polygon.cpp, Changjae Han, June 6 2021, Polygon.cpp file to utilize functions defined on Polygon.h
 */


#include "Polygon.h"

// No-argument constructor
Polygon::Polygon() {

    for (int i=0; i<3; i++)
    {
        normal[i] = 0.0;
    }
}

// Constructor with an argument
Polygon::Polygon( int initialCapacity ) {

    for (int i=0; i<3; i++)
    {
        normal[i] = initialCapacity;
    }
}

// Destructor
Polygon::~Polygon( ) {
    
}



// Polygon addPoint function call the PointSet addpoint function and add point as a child class
// This function requires two conditions 1) getPointByID and 2) isCoplanar to check whether point is acceptable.
// In order for points to be acceptable, it should not duplicate and should be coplanar.
bool Polygon::addPoint( const Point3d & point ) {
	

    Point3d *ptPoly = new Point3d(point);
  
    if (this->getPointByID(ptPoly->getID())==NULL) // points don't exist in Polygon
    {
        
        if (this->nPoints >= 3)
        {
            this->calcNormal();           
        }
        if (this->isCoplanar(*ptPoly)) // check isCoplanar
        {
          
            cout << "added" << endl;
            return PointSet::addPoint(ptPoly); 
        }   
        else
        {
            cout << "it is not coplanar" << endl;
            return false;
        }
        
    }
    else
    {
        cout << "this point already exist in polygon" << endl;
        return false;
    }

}


// Similar with above addPoint, it functions without creating temporary set.
bool Polygon::addPoint( Point3d * pointPtr ) {

    
    if (this->getPointByID(pointPtr->getID())==NULL) // points don't exist in Polygon
    {
        
        if (this->nPoints >= 3)
        {
            this->calcNormal();           
        }
        if (this->isCoplanar(*pointPtr)) // check isCoplanar
        {
            cout << "added" << endl;
            return PointSet::addPoint(pointPtr); 
        }   
        else
        {
            cout << "it is not coplanar" << endl;
            return false;
        }
        
    }
    else
    {
        cout << "this point already exist in polygon" << endl;
        return false;
    }

    
}



// isCoplanar returns true when the number of points are less than three 
// since it is automatically coplanar, and true if absolute value of the dot product
// is less than 1.0E-6; otherwise return false.
bool Polygon::isCoplanar( const Point3d & point ) const {
   
    if (this->nPoints < 3)
    {
        return true;
    }
    else
    {
        double vectorAB[3]; // Create vector, and calculate dot product by calling the following function.
        this->calcVector(*(this->points[0]), point, vectorAB);
        
        double dotProduct = this->dot(vectorAB, this->normal); 
  
        
        if (abs(dotProduct) < 0.000006)
        {
            return true;
        }
        else
        {
            return false;
        }
    }       
}



// calcNormal calculates normal vector by setting each point.
void Polygon::calcNormal() {

    // For vector1
    double vector01[3];
    for (int i=0; i<3; i++)
    {
        vector01[i] = 0;
    }
    this->calcVector(*(this->points[0]),*(this->points[1]), vector01);

    // For vector2
    double vector02[3];
    for (int i=0; i<3; i++)
    {
        vector02[i] = 0;
    }
    this->calcVector(*(this->points[0]),*(this->points[2]), vector02);

    // calculate cross vector
    this->cross( vector01, vector02, this->normal); 
       
}


// calcVector takes two point and calculates by subtracting their components
void Polygon::calcVector( const Point3d & start, const Point3d & finish, 
	double result[ 3 ] ) const {

    result[0] = finish.getX() - start.getX();
    result[1] = finish.getY() - start.getY();
    result[2] = finish.getZ() - start.getZ();
        
    return;
}


// cross product which follows the "Right hand rule" is being calculated
void Polygon::cross( const double vec1[ 3 ], const double vec2[ 3 ], 
	double result[ 3 ]) const {

    result[0] = vec1[1]*vec2[2] - vec2[1]*vec1[2];
    result[1] = vec1[2]*vec2[0] - vec2[2]*vec1[0];
    result[2] = vec1[0]*vec2[1] - vec2[0]*vec1[1];
    
    return;
    
}


// dot product is the sum of the products of their components
// if it is 0, it means two vectors are perpindicular to each other
double Polygon::dot( const double vec1[ 3 ], const double vec2[ 3 ] ) const {


    return (vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2]);
}


// PrintAll function which is very similar to PointSet's function but different print content
void Polygon::printAll( ostream & outStream ) const {
	
    printStats( outStream ); // First call the other function for basics
	
    for (int i=0; i<nPoints; i++)
    {
        outStream << "Polygon points ID: "<< i << " {";
        outStream << *points[i] << endl;
    }	
    return;
}


// setNormal function helps set Normal and avoid const restriction.
void Polygon::setNormal()
{
    if (this->nPoints >=3) // after 3 points, normal is calculated.
    {
        this->calcNormal();
    }
}
