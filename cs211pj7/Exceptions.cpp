/**
 * Project7-Exceptions.cpp, Changjae Han, June 10 2021
 */

// incomplete due to lack of time,,

#include "Exceptions.h"

// First the methods for Exception itself

Exception::Exception( string s ): description(s) {

}

string Exception::getDescription( ) {

    return description;
}

// Then the subclasses

InvalidMove::InvalidMove( string s ): Exception( s ) { // Done as a sample

}

SpaceUnavailable::SpaceUnavailable( string s ): Exception(s) { // TODO:  Finish this one.

}

Collision::Collision( string s, int r, int c): Exception(s), row(r), col(c) {

    
}

void Collision::getLocation( int & r, int & c ) {

}
