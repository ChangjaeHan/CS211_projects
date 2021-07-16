/**
 * Project7-Board.h, Changjae Han, June 10 2021
 */


#ifndef _BOARD_H
#define _BOARD_H

#include "Exceptions.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


#include "Pieces.h"

#define NROWS 10
#define NCOLS 20

class Board {
	private: 
	    int nRows;
	    int nCols;
	    int row;
	    int col;
	    int playerRow; // current location of player row
	    int playerCol; // current location of player col
	    Piece * pieces[ NROWS ][ NCOLS ]; // The pointers in this array will actually point to instances of subclasses of Piece                                                       
	    int lastTurnPlayed[ NROWS ][ NCOLS ];
	    int currentTurn;
	    static Board * theBoard;
		Board( ); // PRIVATE constructor, for Singleton pattern
        
	    
	public: 
        
	    static Board * getBoard( );
            void releaseBoard( ); //free Board 
            void destroyPiece( ); //free Piece
            void display( );
	    void play( );
	    void moveMeTo( int newRow,  int newCol );
	    void getPlayerPosition( int & row, int & col );
};

#endif //_BOARD_H
