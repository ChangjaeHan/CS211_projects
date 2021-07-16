/**
 * Project7-Board.cpp, Changjae Han, June 10 2021
 */


#include "Board.h"
#include <ctime>

Board * Board::theBoard = NULL;

// private constructor (for singleton)
Board::Board( ): nRows(NROWS), nCols(NCOLS) {

     
    // assign random and initialize
    srand(time(NULL));
    this->nRows = 10;
    this->nCols = 20;    
    this->playerRow = 0;
    this->playerCol = 0;

    /* make a Board by using random*/
    
    //1. fill every space up with space
    for (int i = 0; i<nRows; i++)
    {
        for (int j = 0; j<nCols; j++) 
        {
             pieces[i][j] = new Space();             
        }  
    }    
    //2. fill the edge
    pieces[0][0] = new Edge();
    pieces[0][nCols-1] = new Edge();
    pieces[nRows-1][0] = new Edge();
    pieces[nRows-1][nCols-1] = new Edge();
    
    //3. fill the col
    for (int j = 1; j<nCols-1; j++)
    {
        pieces[0][j] = new Cwall();
        pieces[nRows-1][j] = new Cwall();
    }
    //4. fill the row
    for (int i = 1; i<nRows-1; i++)
    {
        pieces[i][0] = new Rwall();
        pieces[i][nCols-1] = new Rwall();
    } 
    
    //5. fill the Robot, Brick, and Mine: (left-side preferred)
    //   rand() % (b+1-a) + a -> a~b random value
    for (int i=0; i<5; i++)
    {
        int ranRow_Robot = rand()%8 + 1;
        int ranCol_Robot = rand()%8 + 1;  
        int ranRow_Brick = rand()%8 + 1;
        int ranCol_Brick = rand()%8 + 1; 
        int ranRow_Mine = rand()%8 + 1;
        int ranCol_Mine = rand()%8 + 1; 
        
        
        pieces[ranRow_Robot][ranCol_Robot] = new Robot();
        pieces[ranRow_Brick][ranCol_Brick] = new Brick();
        pieces[ranRow_Mine][ranCol_Mine] = new Mine();

    }
    
    //6. fill the player: (right-side preferred)
    int ranRow_Player = rand()%8 + 1;
    int ranCol_Player = rand()%7 + 11;
    
    pieces[ranRow_Player][ranCol_Player] = new Player(); 
    
    //7. set playerRow and playerCol
    playerRow = ranRow_Player;
    playerCol = ranCol_Player;
 
  
}

/* static Board * getBoard( ) is a method that any code can call to get a pointer to the one and only Board class  instance.
 *     It  first  checks  the  static Board  *  theBoard,  to  see  if  it  is  still  NULL.
 *     If  it  is,  then  this method  uses  new  to  create  a  new  instance  of  the  Board  class,
 *   and  saves  the  address  in  the  theBoard variable.  It then returns theBoard. */
Board * Board::getBoard( ) {

    if (theBoard == NULL)
    {
        theBoard = new Board();        
    }
    return theBoard;
}

// releaseBoard()
// This is the inverse of getBoard(), delete the Board and set NULL 
void Board::releaseBoard( ) {

    delete theBoard;
    theBoard = NULL;
    
}

// destroyPiece()
// This is to destroy piece in order to prevent leak of memory
// delete the pieces and set NULL
void Board::destroyPiece( ) {
    
    for (int i = 0; i<nRows; i++)
    {
        for (int j = 0; j<nCols; j++) 
        {
             delete this->pieces[i][j];
             this->pieces[i][j] = NULL;
        }  
    }   
    
}

// display()
// This is to show the board by using for loop.
void Board::display( ) {

    
    for (int i = 0; i<nRows; i++)
    {
        for (int j = 0; j<nCols; j++) 
        {
             cout << pieces[i][j]->display();             
        }  
        cout << endl;
    }
     
  
}

// play()
// There are 9 possible commands that user can input
// Each time player can move one block
void Board::play( ) {

   char key;
   cout << "Decide where to move: " << endl;
   cin >> key;
    
   while (playerRow != 9 && playerRow != 0 && playerCol != 19 && playerCol != 0) // beyond the wall
   { 
       
       if (key == 'w') // 1. move up
       {
           pieces[playerRow][playerCol] = new Space();
           playerRow--;
       }
       else if (key == 'a') // 2. move left
       {
           pieces[playerRow][playerCol] = new Space();
           playerCol--;
       } 
       else if (key == 'd') // 3. move right
       {
           pieces[playerRow][playerCol] = new Space();
           playerCol++;          
       }
       else if (key == 'x') // 4. move down
       {
           pieces[playerRow][playerCol] = new Space();
           playerRow++;
       }
       else if (key == 's') // 5. stand still
       {
           // nothing happen for player
       }
       else if (key == 'q') // 6. move left up
       {
           pieces[playerRow][playerCol] = new Space();
           playerRow--;
           playerCol--;
       } 
       else if (key == 'e') // 7. move right up
       {
           pieces[playerRow][playerCol] = new Space();
           playerRow--;
           playerCol++;
       }
       else if (key == 'z') // 8. move left down
       {
           pieces[playerRow][playerCol] = new Space();
           playerRow++;
           playerCol--;           
       }
       else if (key == 'c') // 9. move right down
       {
           pieces[playerRow][playerCol] = new Space();
           playerRow++;
           playerCol++;                 
       }
       else // 10. invalid command
       {
           cout << "Invalid value... try again" << endl;
       }
       
       Board::moveMeTo( playerRow, playerCol );
       
       if (playerRow == 9 || playerRow == 0 || playerCol == 19 || playerCol == 0)
       {
           break;
       }
       else
       {
           display();
       }
       
       cout << "Decide where to move: " << endl;
       cin >> key;
   }
   
    
}

//After Players and Robots have decided where they want to move,
//they call Board::moveMeTo( ) to actually make the move.
void Board::moveMeTo( int newRow, int newCol ) {

    pieces[newRow][newCol] = new Player();
}

//to find out where the player is currently located.
void Board::getPlayerPosition( int & row, int & col ) {

    row = playerRow;
    col = playerCol;
}

