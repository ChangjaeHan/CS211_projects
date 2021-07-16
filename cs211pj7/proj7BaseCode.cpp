/* Project7-proj7Base.cpp, Changjae Han, June 10 2021
*/

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

#include "Pieces.h"
#include "Exceptions.h"
#include "Board.h"

#define TRUE 1
#define FALSE 0

// set DebugMode
int DebugMode = FALSE;


int main( int argc, char ** argv ) {
	
    
    for (int i=0; i<argc; i++)
    {
        cout << "Argv[" << i << "] = " << argv[i] << endl;
        if (strcmp(argv[i], "-d") == 0)
        {
            DebugMode = TRUE;
        }
    }
    
    if (DebugMode)
    {
        cout << "[DebugMode]: operated" << endl;
    }
    
    cout << "**Welcome to the Avoid-Robot game**" << endl;
    cout << endl;
    cout << "Make move: 1. q(up-left)" << endl;
    cout << "         : 2. w(up)" << endl;
    cout << "         : 3. e(up-right)" << endl;
    cout << "         : 4. a(left)" << endl;
    cout << "         : 5. s(stand)" << endl;
    cout << "         : 6. d(right)" << endl;
    cout << "         : 7. z(down-left)" << endl;
    cout << "         : 8. x(down)" << endl;
    cout << "         : 9. c(down-right)" << endl;
   
    // make board and get board
    Board * myBoard;
    myBoard = Board::getBoard( );
    
    // execute public function
    myBoard->display();
    myBoard->play( );

    
  /*  while( ! done ) {
        display( );
        player->move( );
        Loop through ( row from 0 to nRows, col from 0 to nCols )
        {
            if( lastTurn[ row ][ col ] < currentTurn )
            {
                Try( pieces[ row ][ col ]->move( row, col ))
                Catch any exceptions and handle them.
            }
        }
        currentTurn++
    }*/
    
    cout << "Good Bye" << endl;
    
    //free memory
    myBoard->destroyPiece();   
    myBoard->releaseBoard();
        
    return 0;
	
} // main
