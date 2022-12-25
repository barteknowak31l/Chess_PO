#ifndef _Board
#define _Board

#include "coordinates.h"
#include "utils.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Piece;
class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;


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
	static int _fieldsUnderAttackByWhite[8][8];
	static int _fieldsUnderAttackByBlack[8][8];


	//boards for nextMove simulation 
	static int _sim_b[8][8];
	static int _sim_fieldsUnderAttackByWhite[8][8];
	static int _sim_fieldsUnderAttackByBlack[8][8];

	//fields - visual representation
	static sf::RectangleShape fields[8][8];
	
	//positions of pieces on board
	//positions on board are stored as follows
	// 0 1 2 3 4 5 6 7
	// 8 9 10 11 12 ...
	//...
	//...
	//...
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

	static Piece* w_promoted_pieces[8];
	static Piece* b_promoted_pieces[8];

	//board colors
	sf::Color color1;
	sf::Color color2;


	//turn indicator 0 -white 1 - black
	static int turn;

	//check indicators
	//when kings are attacked once
	static int check_white;
	static int check_black;
	
	//when kings are attacked more than once
	static int hard_check_white;
	static int hard_check_black;

	//to check if somebody won
	static int whiteWon;
	static int blackWon;
	static int staleMate;

	//to display info about game
	sf::Font font;
	sf::Text infoText;

	//promotion counters
	static int whitePromotions;
	static int blackPromotions;

	//private methods

	//initializes pieces of both colors on board - creates new Piece objects and stores them in arrays of same type
	void initPieces();

	//the function to print messages on the right side of screen
	void handleInfoText();
	
	//initializes messagebox on the right of the screen
	void initInfoText();

	//the function calculates the point where the piece should be drawn for each field 
	void calculatePiecesPositions();

	//prepare game logic for the next turn
	static void nextTurn();

	//functions to check state of a game

	static void isCheck();
	static bool isMate(int);
	static bool isStaleMate(int);


	//utility function to get color of piece by given piece type
	static int pieceTypeToColor(int);

	//moves a piece to given coordinates on board
	static void move(Piece*, Coordinates);

	//performs "castle" in game logic - roszada
	static void castle(Piece*, Coordinates, int);

	//performs "enPassant" in game logic - bicie w przelocie
	static void enPassant(Piece*, Coordinates, Coordinates);

	//performs a capture - deletes a piece on given coordinates
	static void capture(Coordinates);

	//draws board fields and messagebox
	void drawBoard(sf::RenderWindow& target);

	//utility - returns position of the field in pixels from the given logical representation of the field
	static sf::Vector2f boardToScreenPos(int, int);

	//utility - returns logical position of the field from the given position of mouse in pixels
	static int* screenToBoardPos(sf::Vector2f);

	//performs a promotion of a pawn to queen in logical reprasentation, also deletes pawn and creates object
	static void pawnPromotion(Coordinates, Coordinates);


public:


	Board();
	~Board();

	//initializes board - sets flags to default and initializes pieces on board
	void init();

	//called once each frame
	void update(sf::RenderWindow&);





	//nextMove simulation - checks if next move is legal - in terms of:	 capturing own piece, trying to capture nothing (when moving pawn), trying to move a piece, which was pinned to a king
	static bool simulateNextMove(Piece*,Coordinates);



	//setters

	//increments appropriate position in _fieldsUnderAttack array if a field is under attack
	static void setFieldUnderAttack(Coordinates,int,int);

	//sets all values in _fieldsUnderAttact array to 0
	static void resetFieldsUnderAttack();

	//set colors of board
	void setColorsofBoard(sf::Color, sf::Color);

	//getters

	//returns piece position on given logical field representation
	sf::Vector2f getPiecesPositions(int,int);

	//returns piece type on given logical representation (in coordinates)
	static int getPieceTypeOnGivenCoords(Coordinates);

	//returns turn indicator
	static int getTurn();

	//returns a number of attackers of given color(int) on given field (in coordinates)
	static int getFieldUnderAttack(Coordinates, int);

	//debug
	static void printBoard();
	static void printUnderAttackWhite();
	static void printUnderAttackBlack();
	static void printCheckStatus();
};

#endif