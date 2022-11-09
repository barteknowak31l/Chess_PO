#ifndef _Board
#define _Board

#include "coordinates.h"
#include "utils.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Board
{
private:

	//positions on board are stored as follows
	// 0 1 2 3 4 5 6 7
	// 8 9 10 11 12 ...
	//.
	//.
	//.
	//...     61 62 63

	int _b[8][8];						
	sf::RectangleShape fields[8][8];
	sf::Vector2f piecesPositions[8][8];

public:
	void init();

	//add later - there will be mechainsm in GameManager class that'll use this to check is move legal
	int isMoveLegal(Coordinates,Coordinates);

	//add later -reverses sides of balck and white - useful in 2 player game
	void reverse();

	void drawBoard(sf::RenderTarget& target);

	sf::Vector2f boardToScreenPos(int, int);

	void calculatePiecesPositions();


	//getters
	sf::Vector2f getPiecesPositions(int,int);

};

#endif