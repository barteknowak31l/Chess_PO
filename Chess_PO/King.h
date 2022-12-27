#ifndef _King
#define _King

#include "include\Piece.h"

class King : Piece
{

private:

	//determines of a player tries to do a castle move and if it is possible with the current state of the board
	int castle(Coordinates);

	//texture of piece loaded from file
	sf::Texture texture;

public:

	King();

	//params: coord x, coord y, color, type 
	King(int, int, int,int);
	
	~King();
	

	//overrided virtual functions

	//returns true if move is legal, false if not or if any special move should be performed
	bool isMoveLegal(Coordinates);
	
	//finds all fields that are attacked by this piece (according to its possible movement) and stores that information in Board class. If this piece was captured in 
	//simulation step, no calculation is performed
	void findFieldsUnderAttack();

	//finds possible moves (according to chess rules) and stores them in set of possible moves - it is used in simulation on next move
	void findAllPossibleMoves();

};
#endif

