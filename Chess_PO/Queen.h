#ifndef _Queen
#define _Queen

#include "include\Piece.h"

class Queen : Piece
{
private:

	//texture of piece loaded from file
	sf::Texture texture;

	//bishop versrion of isMoveLegal
	bool diagonalMove(Coordinates);

	//rook version of isMoveLegal
	bool horizontalVerticalMove(Coordinates);
	
	//bishop version of findFieldsUnderAttack
	void diagonalUnderAttack();

	//rook version of findFieldsUnderAttack
	void horizontalVerticalUnderAttack();

	//bishop version of findAllPossibleMoves
	void bishopMoves();

	//rook version of findAllPossibleMoves
	void rookMoves();

public:

	Queen();
	
	//params: coord x, coord y, color, type 
	Queen(int, int, int,int);

	~Queen();
	
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

