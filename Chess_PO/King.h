#ifndef _King
#define _King

#include "Piece.h"

class King : Piece
{
public:
	sf::Texture texture;
	King();
	King(int, int, int,int);
	~King();
	bool isMoveLegal(Coordinates);

};
#endif

