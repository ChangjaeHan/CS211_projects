/**
 * Project7-Pieces.cpp, Changjae Han, June 10 2021
 */


#include "Pieces.h"


// First the Piece class methods

void Piece::move( int r, int c ) {
	return; // Do-nothing method
}

bool Piece::isBarrier() {
	return false; // for most Pieces
}

bool Piece::isSpace() {
	return false; // for most Pieces
}

// Then the Player class methods

char Player::display( ) {
    
	return 'A'; // player: A
}

void Player::move( int r, int c ){ // Reads in keyboard input
    
	return;
}

// Then the Robot class methods

char Robot::display( ) {
	return 'R'; // Robot: R
}

void Robot::move( int r, int c ){  // Basic AI to chase the player
	return;
}

// The Mine class method

char Mine::display( ) {
	return '*'; // Mine: *
}

// The Brick class methods

char Brick::display( ) {
	return '#'; // Brick: #
}

bool Brick::isBarrier() { // Brick needs to override this one
	return false;
}

// The Space class methods

char Space::display( ) {
	return ' '; // Space: " "
}

bool Space::isSpace() { // Space needs to override this one
	return false;
}

char Rwall::display( ) {
	return '|'; // Rwall: |
}

bool Rwall::isSpace() { // Space needs to override this one
	return false;
}

char Cwall::display( ) {
	return '='; // Cwall: =
}

bool Cwall::isSpace() { // Space needs to override this one
	return false;
}
char Edge::display( ) {
	return '+'; // Edge: +
}

bool Edge::isSpace() { // Space needs to override this one
	return false;
}
