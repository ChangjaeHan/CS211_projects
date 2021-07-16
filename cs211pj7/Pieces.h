/**
 * Project7-Pieces.h, Changjae Han, June 10 2021
 */


#ifndef _PIECES_H
#define _PIECES_H

// First the Piece class itself

class Piece {
	public:  
	    virtual char display( ) = 0;
      	    virtual void move( int r, int c );
    	    virtual bool isBarrier( );
    	    virtual bool isSpace( );
};

// Then all the subclasses
// 
class Player: public Piece {
	    virtual char display( );
    	    virtual void move( int r, int c );
};


class Robot: public Piece {
	    static int nRobots;
	    virtual char display( );
    	    virtual void move( int r, int c );
};


class Mine: public Piece {
	    virtual char display( );
};

class Brick: public Piece {
	    virtual char display( );
    	    virtual bool isBarrier( );
};

class Space: public Piece {
	    virtual char display( );
    	    virtual bool isSpace( );
};

class Rwall: public Piece {
	    virtual char display( );
    	    virtual bool isSpace( );
};

class Cwall: public Piece {
	    virtual char display( );
    	    virtual bool isSpace( );
};

class Edge: public Piece {
	    virtual char display( );
    	    virtual bool isSpace( );
};



#endif //_PIECES_H
