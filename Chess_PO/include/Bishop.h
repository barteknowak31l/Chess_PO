#ifndef _Bishop
#define _Bishop

#include "Piece.h"

class Bishop : Piece
{
private:

	//texture of piece loaded from file
	sf::Texture texture;

public:

	Bishop();

	//params: coord x, coord y, color, type 
	Bishop(int, int, int,int);

	~Bishop();
	
	
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

