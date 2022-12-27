#ifndef _knight
#define _Knight

#include "include\Piece.h"

class Knight : Piece
{
private:

	//texture of piece loaded from file
	sf::Texture texture;

public:
	Knight();

	//params: coord x, coord y, color, type 
	Knight(int, int, int,int);

	~Knight();
	

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

