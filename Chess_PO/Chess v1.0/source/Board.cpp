#include "include\Board.h"
#include "algorithm"
#include <iostream>

#include "include\Piece.h"
#include "include\Rook.h"
#include "include\Pawn.h"
#include "include\Knight.h"
#include "include\Bishop.h"
#include "include\King.h"
#include "include\Queen.h"


//init static variables

int Board::blackWon;
int Board::whiteWon;
int Board::staleMate;

sf::RectangleShape Board::fields[8][8];
int Board::_b[8][8];
sf::Vector2f Board::piecesPositions[8][8];
int Board::turn;
int Board::_fieldsUnderAttackByWhite[8][8];
int Board::_fieldsUnderAttackByBlack[8][8];
int Board::check_white;
int Board::check_black;
int Board::hard_check_white;
int Board::hard_check_black;

//simulation stuff
int Board::_sim_b[8][8];
int Board::_sim_fieldsUnderAttackByWhite[8][8];
int Board::_sim_fieldsUnderAttackByBlack[8][8];

//promotion stuff
Piece* Board::w_promoted_pieces[8];
Piece* Board::b_promoted_pieces[8];
int Board::blackPromotions;
int Board::whitePromotions;



Board::Board()
{
	turn = 0;
	color1 = sf::Color::White;
	color2 = sf::Color::Black;

	whitePromotions = 0;
	blackPromotions = 0;
}

Board::~Board()
{
	//delete all pieces
	for (Piece* p : Piece::getInstances())
	{
		delete p;
	}

	//reset logical representation of board - static array 
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_b[i][j] = 0;
		}
	}


}

void Board::init()
{
	blackWon = false;
	whiteWon = false;
	staleMate = false;
	turn = 0;
	check_white = false;
	check_black = false;

	//initialize messagebox
	initInfoText();

	_b[0][0] = b_rook;
	_b[0][1] = b_knight;
	_b[0][2] = b_bishop;
	_b[0][3] = b_queen;
	_b[0][4] = b_king;
	_b[0][5] = b_bishop;
	_b[0][6] = b_knight;
	_b[0][7] = b_rook;

	_b[1][0] = b_pawn;
	_b[1][1] = b_pawn;
	_b[1][2] = b_pawn;
	_b[1][3] = b_pawn;
	_b[1][4] = b_pawn;
	_b[1][5] = b_pawn;
	_b[1][6] = b_pawn;
	_b[1][7] = b_pawn;


	_b[7][0] = w_rook;
	_b[7][1] = w_knight;
	_b[7][2] = w_bishop;
	_b[7][3] = w_queen;
	_b[7][4] = w_king;
	_b[7][5] = w_bishop;
	_b[7][6] = w_knight;
	_b[7][7] = w_rook;

	_b[6][0] = w_pawn;
	_b[6][1] = w_pawn;
	_b[6][2] = w_pawn;
	_b[6][3] = w_pawn;
	_b[6][4] = w_pawn;
	_b[6][5] = w_pawn;
	_b[6][6] = w_pawn;
	_b[6][7] = w_pawn;


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_fieldsUnderAttackByWhite[i][j] = 0;
			_fieldsUnderAttackByBlack[i][j] = 0;
			_sim_fieldsUnderAttackByBlack[i][j] = 0;
			_sim_fieldsUnderAttackByWhite[i][j] = 0;
			_sim_b[i][j] = 0;
		}
	}


	//initialize piece objects
	initPieces();

}

void Board::initPieces()
{
	//init pieces
	b_pawns[0] = new Pawn(0, 1, 1, b_pawn);
	b_pawns[1] = new Pawn(1, 1, 1, b_pawn);
	b_pawns[2] = new Pawn(2, 1, 1, b_pawn);
	b_pawns[3] = new Pawn(3, 1, 1, b_pawn);
	b_pawns[4] = new Pawn(4, 1, 1, b_pawn);
	b_pawns[5] = new Pawn(5, 1, 1, b_pawn);
	b_pawns[6] = new Pawn(6, 1, 1, b_pawn);
	b_pawns[7] = new Pawn(7, 1, 1, b_pawn);

	w_pawns[0] = new Pawn(0, 6, 0, w_pawn);
	w_pawns[1] = new Pawn(1, 6, 0, w_pawn);
	w_pawns[2] = new Pawn(2, 6, 0, w_pawn);
	w_pawns[3] = new Pawn(3, 6, 0, w_pawn);
	w_pawns[4] = new Pawn(4, 6, 0, w_pawn);
	w_pawns[5] = new Pawn(5, 6, 0, w_pawn);
	w_pawns[6] = new Pawn(6, 6, 0, w_pawn);
	w_pawns[7] = new Pawn(7, 6, 0, w_pawn);

	b_rooks[0] = new Rook(0, 0, 1, b_rook);
	b_rooks[1] = new Rook(7, 0, 1, b_rook);
	
	w_rooks[0] = new Rook(0, 7, 0, w_rook);
	w_rooks[1] = new Rook(7, 7, 0, w_rook);

	b_knights[0] = new Knight(1, 0, 1, b_knight);
	b_knights[1] = new Knight(6, 0, 1, b_knight);

	w_knights[0] = new Knight(1, 7, 0, w_knight);
	w_knights[1] = new Knight(6, 7, 0, w_knight);

	b_bishops[0] = new Bishop(2, 0, 1, b_bishop);
	b_bishops[1] = new Bishop(5, 0, 1, b_bishop);

	w_bishops[0] = new Bishop(2, 7, 0, w_bishop);
	w_bishops[1] = new Bishop(5, 7, 0, w_bishop);

	b_kings[0] = new King(4, 0, 1, b_king);
	
	w_kings[0] = new King(4, 7, 0, w_king);

	b_queens[0] = new Queen(3, 0, 1, b_queen);
	
	w_queens[0] = new Queen(3, 7, 0, w_queen);

	Piece::setFieldsUnderAttack();

}

void Board::initInfoText()
{
	if (!font.loadFromFile("font/sugar_snow.ttf"))
	{
		std::cout << "No font file detected\n";
		exit(-1);
	}

	infoText.setFont(font);
	//winText.setString("temporary");
	infoText.setString("White to move\n");
	infoText.setCharacterSize(24);
	infoText.setPosition(sf::Vector2f(630, 200));
	infoText.setFillColor(textColor);
	infoText.setStyle(sf::Text::Bold);
	infoText.setOrigin(sf::Vector2f(infoText.getGlobalBounds().width / 2, infoText.getGlobalBounds().height / 2));

}

void Board::update(sf::RenderWindow& window)
{
	drawBoard(window);
	handleInfoText();
	calculatePiecesPositions();
}

void Board::handleInfoText()
{
	if (turn == 0)
	{
		infoText.setString("White to move\n");
	}
	if (turn == 1)
	{
		infoText.setString("Black to move\n");
	}

	if (check_white)
	{
		infoText.setString("       CHECK!\n\nWhite to move\n");
	}
	if (check_black)
	{
		infoText.setString("       CHECK!\n\nBlack to move\n");
	}


	if (blackWon)
	{
		infoText.setString("Black won by checkmate!\n\nPress R to restart game.\n");
	}
	if (whiteWon)
	{
		infoText.setString("White won by checkmate!\n\nPress R to restart game.\n");
	}
	if (staleMate)
	{
		infoText.setString("           StaleMate!\n\nPress R to restart game.\n");
	}


}

void Board::drawBoard(sf::RenderWindow& target)
{

	//find appropriate size of field
	float x = target.getSize().x * 0.75;
	float y = target.getSize().y;

	float textSize = std::min(x, y);
	float textSizeScale = 20;
	float size = std::min(x, y) / 8;


	//dipslay infoText
	infoText.setCharacterSize(textSize / textSizeScale);
	infoText.setOrigin(sf::Vector2f(infoText.getGlobalBounds().width / 2, infoText.getGlobalBounds().height / 2));
	infoText.setPosition(sf::Vector2f(textSize + (target.getSize().x - textSize) / 2, textSize / 3));

	target.draw(infoText);
	

	//set fields positions and size
	x = 0;
	y = 0;
	for(int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fields[i][j].setSize(sf::Vector2f(size, size));
			fields[i][j].setPosition(sf::Vector2f(x, y));
			x += size;
		}
		x = 0;
		y += size;
	}


	//set appropriate colors
	x = 0;
	y = 0;
	int col = 1;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (col)
			{
				fields[i][j].setFillColor(color1);
			}
			else
			{
				fields[i][j].setFillColor(color2);
			}
			col = !col;
			target.draw(fields[i][j]);
		}
		col = !col;


	}

}

sf::Vector2f Board::boardToScreenPos(int x, int y)
{
	return fields[x][y].getPosition();
}

int* Board::screenToBoardPos(sf::Vector2f mousePos)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (fields[i][j].getGlobalBounds().contains(mousePos))
			{
				int* pos = new int[2];
				pos[0] = j;
				pos[1] = i;
				return pos;
			}
		}
	}

	return  NULL;
}

void Board::calculatePiecesPositions()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			piecesPositions[i][j] = sf::Vector2f(fields[i][j].getPosition().y + fields[i][j].getSize().y/2,
												fields[i][j].getPosition().x + fields[i][j].getSize().x/2);
		}
	}
}


void Board::move(Piece* p, Coordinates c)
{
	//check if the input is right i.e if bishop was moved diagonally with the mouse or if a piece is not trying to "jump" over another piece
	//it's a virtual function
	if (p->isMoveLegal(c) == 0)
	{
		return;
	}

	//check if next move is legal
	if (simulateNextMove(p, c) == 0)
	{
		return;
	}

	capture(c);

	//set old logical position to empty state
	_b[p->getPositionOnBoard().getY()][p->getPositionOnBoard().getX()] = empty;

	//set new position in piece object
	p->setPositionOnboard(c);

	//set new position of piece in logical representation of board
	_b[c.getY()][c.getX()] = p->getType();

	//nextTurn
	nextTurn();
}

void Board::castle(Piece* p, Coordinates c,int variant)
{
	//get rook piece from given coordinates (c)
	//move king and rook according to given variant of castle

	Piece* rook = Piece::getPieceByCoords(c);
	Coordinates r;
	Coordinates k;

	switch (variant)
	{
	case 1: //white left rook
	{

		//change logical representation of pieces on board
		_b[7][3] = w_rook;
		_b[7][2] = w_king;
		_b[7][0] = empty;
		_b[7][4] = empty;

		//set new coordinates in pieces objects
		r.setX(3);
		r.setY(7);
		k.setX(2);
		k.setY(7);
		

		p->setPositionOnboard(k);
		rook->setPositionOnboard(r);
		nextTurn();

		break;
	}
	case 2: //white right rook
	{
		//change logical representation of pieces on board
		_b[7][4] = w_rook;
		_b[7][5] = w_king;
		_b[7][7] = empty;

		//set new coordinates in pieces objects
		r.setX(4);
		r.setY(7);
		k.setX(5);
		k.setY(7);


		p->setPositionOnboard(k);
		rook->setPositionOnboard(r);
		nextTurn();

		break;
	}
	case 3: //black left rook
	{
		//change logical representation of pieces on board
		_b[0][3] = b_rook;
		_b[0][2] = b_king;
		_b[0][0] = empty;
		_b[0][4] = empty;

		//set new coordinates in pieces objects
		r.setX(3);
		r.setY(0);
		k.setX(2);
		k.setY(0);


		p->setPositionOnboard(k);
		rook->setPositionOnboard(r);
		nextTurn();

		break;
	}
	case 4: //black right rook
	{
		//change logical representation of pieces on board
		_b[0][4] = b_rook;
		_b[0][5] = b_king;
		_b[0][7] = empty;

		//set new coordinates in pieces objects
		r.setX(4);
		r.setY(0);
		k.setX(5);
		k.setY(0);

		p->setPositionOnboard(k);
		rook->setPositionOnboard(r);
		nextTurn();

		break;
	}



	}
}

void Board::enPassant(Piece* p, Coordinates c1, Coordinates c2)
{
	//delete piece from c2
	//move piece p to c1

	//delete piece on coord c2
	_b[c2.getY()][c2.getX()] = empty;
	for (Piece* p : Piece::getInstances())
	{
		if (p->getPositionOnBoard() == c2)
		{
			delete p;
		}
	}

	//move p to c1
	_b[p->getPositionOnBoard().getY()][p->getPositionOnBoard().getX()] = empty;
	p->setPositionOnboard(c1);
	_b[p->getPositionOnBoard().getY()][p->getPositionOnBoard().getX()] = p->getType();

	//go to next turn
	nextTurn();




}

bool Board::simulateNextMove(Piece* p, Coordinates c2)
{
	//p - piece that is moving
	//c1 - coordinates of moving piece
	//old - piece that is on coordinates that p moves to - NULL if theres no piece
	//c2 - coordinates that p moves to

	Coordinates c1 = p->getPositionOnBoard();
	Piece* old = Piece::getPieceByCoords(c2);

	//check if player tries to capture own piece
	if (old != nullptr)
	{
		if (old->pieceTypeToColor(old->getType()) == p->pieceTypeToColor(p->getType()))
		{
			return false;
		}
	}
	
	//simulate next move

	//copy logical board representation
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_sim_b[i][j] = _b[i][j];
		}
	}

	//change coordinates in piece object p
	p->setPositionOnboard(c2);

	//if theres a piece on coords c2, try to perform a capture
	if (getPieceTypeOnGivenCoords(c2) != empty)
	{
		if (old == nullptr) {
			
			return false;
		}

		//set appropriate flag in captured piece object
		old->setCapturedInSim();

	}


	//make a move in original logical board representation
	_b[c2.getY()][c2.getX()] = getPieceTypeOnGivenCoords(c1);
	_b[c1.getY()][c1.getX()] = empty;



	//simulate new attacks after making a move
	resetFieldsUnderAttack();
	Piece::setFieldsUnderAttack();


	//check if kings are under attack
	// - yes - incorrect move
	// - no - correct move 

	//check if kings are under attack
	isCheck();

	//incorrect white move
	if (p->pieceTypeToColor(p->getType()) == 0 && check_white)
	{
		//restore logical board state
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				_b[i][j] = _sim_b[i][j];
			}
		}

		//unset flag of piece captured in simulation
		if (old != nullptr)
		{
			old->unsetCapturedInSim();
		}

		//restore logical position stored in piece object
		p->setPositionOnboard(c1);

		//restore fieldsUnderAttack
		resetFieldsUnderAttack();
		Piece::setFieldsUnderAttack();
		
		//restore flags
		isCheck();

		//return incorrect move
		return false;
	}

	//incorrect black move
	if (p->pieceTypeToColor(p->getType()) == 1 && check_black)
	{
		//restore logical board state
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				_b[i][j] = _sim_b[i][j];
			}
		}

		//unset flag of piece captured in simulation
		if (old != nullptr)
		{
			old->unsetCapturedInSim();
		}

		//restore logical position stored in piece object
		p->setPositionOnboard(c1);

		//restore fieldsUnderAttack
		resetFieldsUnderAttack();
		Piece::setFieldsUnderAttack();

		//restore flags
		isCheck();

		//return incorrect move
		return false;

	}

	//correct move 
	for (int i = 0; i < 8; i++)
	{
		//restore logical board state
		for (int j = 0; j < 8; j++)
		{
			_b[i][j] = _sim_b[i][j];
		}
	}

	//unset flag of piece captured in simulation
	if (old != nullptr)
	{
		old->unsetCapturedInSim();
	}

	//restore logical position stored in piece object
	p->setPositionOnboard(c1);
	
	//restore fieldsUnderAttack
	resetFieldsUnderAttack();
	Piece::setFieldsUnderAttack();
	
	//restore flags
	isCheck();

	//return correct move
	return true;

}

void Board::nextTurn()
{
	//calculate fields under attack again
	resetFieldsUnderAttack();
	Piece::setFieldsUnderAttack();

	//find out if theres a check
	isCheck();

	//change turn indicator
	if (turn == 0)
	{
		turn = 1;
	}
	else
	{
		turn = 0;
	}

	//determine if theres a stalemate
	if (isStaleMate(turn))
	{
		staleMate = true;
	}


}

void Board::isCheck()
{
	//find both kings and check if they're under attack
	Coordinates pos_w_king;
	Coordinates pos_b_king;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (_b[i][j] == w_king)
			{
				pos_w_king.setX(j);
				pos_w_king.setY(i);
			}
			if (_b[i][j] == b_king)
			{
				pos_b_king.setX(j);
				pos_b_king.setY(i);
			}
		}
	}

	if (getFieldUnderAttack(pos_w_king, 1) > 0)
	{
		check_white = 1;
		if (getFieldUnderAttack(pos_b_king, 0) > 1) {
			hard_check_white = 1;
		}
		else
		{
			hard_check_white = 0;
		}
	}
	else
	{
		check_white = 0;
		hard_check_white = 0;
	}

	if (getFieldUnderAttack(pos_b_king, 0) > 0)
	{
		check_black = 1;
		if (getFieldUnderAttack(pos_b_king, 0) > 1) {
			hard_check_black = 1;
		}
		else
		{
			hard_check_black = 0;
		}
	}
	else
	{
		check_black = 0;
		hard_check_black = 0;
	}


}

bool Board::isMate(int color)
{
	//color == 0 check if white is checkmate'd
	if (color == 0)
	{
		for (Piece* p : Piece::getInstances())
		{
			//for all white pieces
			if (p->pieceTypeToColor(p->getType()) == 0)
			{

				p->findAllPossibleMoves();

				for (Coordinates *c : p->getPossibleMoves())
				{

					//if there is a possible move, then theres no checkmate
					if (simulateNextMove(p, *c))
					{
						return false;
					}
				}
			}
		}
	}

	//color == 1 check if black is checkmate'd
	if (color == 1)
	{
		for (Piece* p : Piece::getInstances())
		{
			//for all black pieces
			if (p->pieceTypeToColor(p->getType()) == 1)
			{
				p->findAllPossibleMoves();

				for (Coordinates *c : p->getPossibleMoves())
				{

					//if there is a possible move, then theres no checkmate
					if (simulateNextMove(p, *c))
					{
						return false;
					}
				}
			}
		}
	}


	//theres a checkmate - set appropriate flags
	if (color == 0)
	{
		blackWon = 1;
	}

	if (color == 1)
	{
		whiteWon = 1;
	}

	return true;

}

bool Board::isStaleMate(int color)
{
	//check if white is not under check and if he has any move which is legal 
	if (color == 0)
	{
		//stalemate
		if (isMate(color) && !check_white)
		{
			return true;
		}
	}

	//check if black is not under check and if he has any move which is legal 
	if (color == 1)
	{
		//stalemate
		if (isMate(color) && !check_black)
		{
			return true;
		}
	}
	
	//not a stalemate
	return false;

}

void Board::capture(Coordinates c)
{
	//get piece on coords c
	//destroy that piece
	
	for (Piece* p : Piece::getInstances())
	{
		if (p->getPositionOnBoard() == c)
		{
			delete p;
			return;
		}
	}

}

void Board::pawnPromotion(Coordinates c_pawn, Coordinates c_new)
{
	
	Piece* pawn = Piece::getPieceByCoords(c_pawn);
	int color = pawn->pieceTypeToColor(pawn->getType());

	//delete old piece if there was a capture:
	for (Piece* p : Piece::getInstances())
	{
		if (p->getPositionOnBoard() == c_new)
		{
			delete p;
		}
	}

	//white
	if (color == 0)
	{
		//create new piece
		Queen *q = new Queen(c_new.getX(), c_new.getY(), color, w_queen);
		w_promoted_pieces[whitePromotions] = (Piece*)q;
		whitePromotions++;

		//put new piece in logical representation
		_b[c_new.getY()][c_new.getX()] = w_queen;

		//remove old pawn from logical representation
		_b[c_pawn.getY()][c_pawn.getX()] = empty;

		//delete old pawn

		for (Piece* p : Piece::getInstances())
		{
			if (p->getPositionOnBoard() == c_pawn)
			{
				delete p;
			}
		}


	}

	//black
	if (color == 1)
	{
		//create new piece
		Queen* q = new Queen(c_new.getX(), c_new.getY(), color, b_queen);
		b_promoted_pieces[whitePromotions] = (Piece*)q;
		blackPromotions++;

		//put new piece in logical representation
		_b[c_new.getY()][c_new.getX()] = b_queen;

		//remove old pawn from logical representation
		_b[c_pawn.getY()][c_pawn.getX()] = empty;

		//delete old pawn

		for (Piece* p : Piece::getInstances())
		{
			if (p->getPositionOnBoard() == c_pawn)
			{
				delete p;
			}
		}


	}






	nextTurn();

}

//setters
void Board::setColorsofBoard(sf::Color c1, sf::Color c2)
{
	color1 = c1;
	color2 = c2;
}

void Board::setMessageTextColor(sf::Color c)
{
	textColor = c;
}

void Board::setFieldUnderAttack(Coordinates c,int color,int type)
{
	if (color == 0)
	{
		_fieldsUnderAttackByWhite[c.getY()][c.getX()] ++;
	}
	else
	{
		_fieldsUnderAttackByBlack[c.getY()][c.getX()] ++;
	}
}

void Board::resetFieldsUnderAttack()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_fieldsUnderAttackByWhite[i][j] = 0;
			_fieldsUnderAttackByBlack[i][j] = 0;
		}
	}
}

//getters
sf::Vector2f Board::getPiecesPositions(int x, int y)
{
	return piecesPositions[x][y];
}

int Board::getPieceTypeOnGivenCoords(Coordinates c)
{
	return _b[c.getY()][c.getX()];
}

int Board::getTurn()
{
	return turn;
}

int Board::getFieldUnderAttack(Coordinates c, int color)
{
	if (color == 0)
	{
		return _fieldsUnderAttackByWhite[c.getY()][c.getX()];
	}
	else if (color == 1)
	{
		return _fieldsUnderAttackByBlack[c.getY()][c.getX()];
	}

	return -1;
}

int Board::pieceTypeToColor(int t)
{
	switch (t)
	{
	case w_pawn:
	case w_rook:
	case w_knight:
	case w_bishop:
	case w_queen:
	case w_king:
	{
		return 0;
	}
	case b_pawn:
	case b_rook:
	case b_knight:
	case b_bishop:
	case b_queen:
	case b_king:
	{
		return 1;
	}

	default: return -1;
	}
}


//debug
void Board::printBoard()
{
	std::cout << "----------------------\n";
	std::cout << "y\\x0 1 2 3 4 5 6 7\n";
	std::cout << "----------------------\n";
	for (int i = 0; i < 8; i++)
	{	
		std::cout << i << "| ";
		for (int j = 0; j < 8; j++)
		{
			std::cout << _b[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Board::printUnderAttackWhite()
{
	std::cout << "----------------------\n";
	std::cout << "y\\x0 1 2 3 4 5 6 7\n";
	std::cout << "----------------------\n";
	for (int i = 0; i < 8; i++)
	{
		std::cout << i << "| ";
		for (int j = 0; j < 8; j++)
		{
			std::cout << _fieldsUnderAttackByWhite[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Board::printUnderAttackBlack()
{
	std::cout << "----------------------\n";
	std::cout << "y\\x0 1 2 3 4 5 6 7\n";
	std::cout << "----------------------\n";
	for (int i = 0; i < 8; i++)
	{
		std::cout << i << "| ";
		for (int j = 0; j < 8; j++)
		{
			std::cout << _fieldsUnderAttackByBlack[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Board::printCheckStatus()
{
	std::cout << "-----------------------\n";
	std::cout << "check white: " << check_white << std::endl;
	std::cout << "check black: " << check_black << std::endl;
	std::cout << "hard check white: " << hard_check_white << std::endl;
	std::cout << "hard check black: " << hard_check_black << std::endl;
}