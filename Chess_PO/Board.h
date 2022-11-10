#ifndef _Board
#define _Board

#include "coordinates.h"
#include "utils.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Piece;
class Rook;
class Pawn;
class Knight;
class Bishop;
class King;
class Queen;


class Board
{
private:
	friend class Piece;
	friend class Pawn;
	friend class Rook;
	friend class Knight;
	friend class Bishop;
	friend class Queen;
	friend class King;

	//logic representation of pieces on board
	static int _b[8][8];			

	//logic representations of fields under attack
	static int _fieldsUnderAttack[8][8];

	//fields
	static sf::RectangleShape fields[8][8];
	
	//positions of pieces on board
		//positions on board are stored as follows
	// 0 1 2 3 4 5 6 7
	// 8 9 10 11 12 ...
	//.
	//.
	//.
	//...     61 62 63
	static sf::Vector2f piecesPositions[8][8];


	//piece objects pointers
	Pawn* w_pawns[8];
	Pawn* b_pawns[8];
	
	Rook* w_rooks[2];
	Rook* b_rooks[2];

	Knight* w_knights[2];
	Knight* b_knights[2];

	Bishop* w_bishops[2];
	Bishop* b_bishops[2];

	King* w_kings[1];
	King* b_kings[1];

	Queen* w_queens[1];
	Queen* b_queens[1];

	//board colors
	sf::Color color1;
	sf::Color color2;


	//turn indicator
	static int turn;

	//private methods
	void initPieces();
	void calculatePiecesPositions();
	static void nextTurn();

public:


	Board();

	void init();

	//called once each frame
	void update(sf::RenderWindow&);


	//moves a piece to given coordinates on board
	static void move(Piece*,Coordinates);

	//deletes a piece on given coordinates
	static void capture(Coordinates);

	//add later -reverses sides of balck and white - useful in 2 player game
	void reverse();

	void drawBoard(sf::RenderWindow& target);

	static sf::Vector2f boardToScreenPos(int, int);
	static int* screenToBoardPos(sf::Vector2f);


	//setters
	static void setFieldUnderAttack(Coordinates);
	static void resetFieldsUnderAttack();

	//set colors of board
	void setColorsofBoard(sf::Color, sf::Color);

	//getters
	sf::Vector2f getPiecesPositions(int,int);

	static int getPieceTypeOnGivenCoords(Coordinates);

	static int getTurn();

	//debug
	static void printBoard();
	static void printUnderAttack();
};

#endif