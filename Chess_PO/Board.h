#ifndef _Board
#define _Board

#include "coordinates.h"
#include "utils.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Board
{
private:
	int _b[8][8];
	sf::RectangleShape fields[64];

public:
	void init();

	//add later - there will be mechainsm in GameManager class that'll use this to check is move legal
	int isMoveLegal(Coordinates,Coordinates);

	//add later -reverses sides of balck and white - useful in 2 player game
	void reverse();

	void drawBoard(sf::RenderTarget& target);

};

#endif