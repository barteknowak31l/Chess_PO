#include "Board.h"
#include "algorithm"
#include <iostream>

#include "Piece.h"
#include "Rook.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"


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


Board::Board()
{
	turn = 0;
	color1 = sf::Color::White;
	color2 = sf::Color::Black;
}

Board::~Board()
{
	for (Piece* p : Piece::getInstances())
	{
		delete p;
	}

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


	//init piece objects
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

void Board::update(sf::RenderWindow& window)
{
	drawBoard(window);
	calculatePiecesPositions();
}


void Board::drawBoard(sf::RenderWindow& target)
{
	//find proper size of field
	float x = target.getSize().x * 0.75;
	float y = target.getSize().y;
	float size = std::min(x, y) / 8;


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


	//set proper colors
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

void Board::setColorsofBoard(sf::Color c1, sf::Color c2)
{
	color1 = c1;
	color2 = c2;
}


void Board::move(Piece* p, Coordinates c)
{
	if (p->isMoveLegal(c) == 0)
	{
		//std::cout << "NIEPOPRAWNY RUCH\n";
		return;
	}

	if (simulateNextMove(p, c) == 0)
	{
		//std::cout << "KROL POD SZACHEM\n";
		return;
	}




	//std::cout<<"RUCH ZAAKCEPTOWANY!\n";

	capture(c);

	//set old logical position to empty state
	_b[p->getPositionOnBoard().getY()][p->getPositionOnBoard().getX()] = empty;

	//set new position to piece object
	p->setPositionOnboard(c);

	//set new position of piece in logical representation of board
	_b[c.getY()][c.getX()] = p->getType();

	//nextTurn
	nextTurn();
}

bool Board::simulateNextMove(Piece* p, Coordinates c2)
{
	Coordinates c1 = p->getPositionOnBoard();
	Piece* old = Piece::getPieceByCoords(c2);

	//proba zbicia wlasnej figury
	if (old != nullptr)
	{
		if (old->pieceTypeToColor(old->getType()) == p->pieceTypeToColor(p->getType()))
		{
			return false;
		}
	}

	//kopiuj aktualna tablice board
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_sim_b[i][j] = _b[i][j];
		}
	}

	//zmien koordynaty w obiekcie piece p
	p->setPositionOnboard(c2);

	//zasymuluj bicie
	if (getPieceTypeOnGivenCoords(c2) != empty)
	{
		if (old == nullptr) {
			
			//std::cout << "TU NIC NIE MA\n ale jest wylapywane:: " << getPieceTypeOnGivenCoords(c2) << std::endl;
			return false;
		}

		//std::cout << "TU COS JEST: " << getPieceTypeOnGivenCoords(c2) << std::endl;
		old->setCapturedInSim();

	}


	//wykonaj ruch na starej tablicy
	_b[c2.getY()][c2.getX()] = getPieceTypeOnGivenCoords(c1);
	_b[c1.getY()][c1.getX()] = empty;


	//std::cout << "TABLICA PO ATAKU\n----------------\n";
	//printBoard();

	//symuluj atak
	resetFieldsUnderAttack();
	Piece::setFieldsUnderAttack();

	//std::cout << "ATAK WHITE\n----------------\n";
	//printUnderAttackWhite();


	//sprawdz czy krol danego koloru jest atakowany:
	// - tak - przywroc stara tablice i wywolaj potem setfieldsunderattack
	// - nie - poprawny ruch do nothing

	//ustawia flagi
	isCheck();

	//niepoprawny ruch bialego
	if (p->pieceTypeToColor(p->getType()) == 0 && check_white)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				_b[i][j] = _sim_b[i][j];
			}
		}

		if (old != nullptr)
		{
			old->unsetCapturedInSim();
		}

		p->setPositionOnboard(c1);
		resetFieldsUnderAttack();
		Piece::setFieldsUnderAttack();
		isCheck();

		return false;
	}

	//niepoprawny ruch czarnego
	if (p->pieceTypeToColor(p->getType()) == 1 && check_black)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				_b[i][j] = _sim_b[i][j];
			}
		}

		if (old != nullptr)
		{
			old->unsetCapturedInSim();
		}

		p->setPositionOnboard(c1);
		resetFieldsUnderAttack();
		Piece::setFieldsUnderAttack();
		isCheck();

		return false;

	}

	//poprawny ruch
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_b[i][j] = _sim_b[i][j];
		}
	}
	if (old != nullptr)
	{
		old->unsetCapturedInSim();
	}
	p->setPositionOnboard(c1);
	resetFieldsUnderAttack();
	Piece::setFieldsUnderAttack();
	isCheck();
	return true;

}

void Board::nextTurn()
{
	resetFieldsUnderAttack();
	Piece::setFieldsUnderAttack();
	isCheck();

	if (turn == 0)
	{
		turn = 1;
	}
	else
	{
		turn = 0;
	}

	if (check_black || check_white)
	{
		std::cout << "SZACH!\n";
	}


	if (isStaleMate(turn))
	{
		if (turn == 0)
		{
			std::cout << "PAT! Bialy nie ma ruchu\n";
		}
		else if (turn == 1)
		{
			std::cout << "PAT! Czarny nie ma ruchu\n";
		}
	}

	if (isMate(turn) && (check_black || check_white))
	{
		if (turn == 0 && check_white)
		{
			std::cout << "CZARNE DALY MATA\n";
		}
		else if(turn == 1 && check_black)
		{
			std::cout << "BIALE DALY MATA\n";
		}
	}

}

void Board::isCheck()
{
	//znajdz krole, sprawdz czy te pola sa atakowane
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
	//color == 0 sprawdz czy bialy ma mata
	if (color == 0)
	{
		for (Piece* p : Piece::getInstances())
		{
			//wszystkie biale figury 
			if (p->pieceTypeToColor(p->getType()) == 0)
			{
				p->findAllPossibleMoves();

				for (Coordinates *c : p->getPossibleMoves())
				{
					std::cout << "FIGURA NA: ";
					p->getPositionOnBoard().print();
					std::cout << " ATAKUJE ";
					c->print();
					std::cout << std::endl;

					if (simulateNextMove(p, *c) && p->isMoveLegal(*c))
					{
						std::cout << "Znaleziono ruch bialego: " << p->getPositionOnBoard().getX() << " " << p->getPositionOnBoard().getY() << " -> " << c->getX() << " " << c->getY() << std::endl;
						return false;
					}
				}
			}
		}
	}

	//color == 1 sprawdz czy czarny ma mata
	if (color == 1)
	{
		for (Piece* p : Piece::getInstances())
		{
			//wszystkie czarne figury 
			if (p->pieceTypeToColor(p->getType()) == 1)
			{
				p->findAllPossibleMoves();

				for (Coordinates *c : p->getPossibleMoves())
				{
					std::cout << "FIGURA NA: ";
					p->getPositionOnBoard().print();
					std::cout << " ATAKUJE ";
					c->print();
					std::cout << std::endl;

					if (simulateNextMove(p, *c))
					{
						std::cout << "Znaleziono ruch czarnego: " << p->getPositionOnBoard().getX() << " " << p->getPositionOnBoard().getY() << " -> " << c->getX() << " " << c->getY() << std::endl;
						return false;
					}
				}
			}
		}
	}

	return true;

}

bool Board::isStaleMate(int color)
{
	//sprawdz czy bialy ma jakis ruch, ktory jest legalny i czy nie ma szacha
	if (color == 0)
	{
		//pat
		if (isMate(color) && !check_white)
		{
			return true;
		}
	}

	//sprawdz czy czarny ma jakis ruch, ktory jest legalny i czy nie ma szacha
	if (color == 1)
	{
		//pat
		if (isMate(color) && !check_black)
		{
			return true;
		}
	}
	
	//nie ma pata
	return false;

}

void Board::capture(Coordinates c)
{
	//get piece on coords c
	//destroy that piece
	//change score - add later
	
	for (Piece* p : Piece::getInstances())
	{
		if (p->getPositionOnBoard() == c)
		{
			delete p;
			return;
		}
	}

}

//setters
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
		//std::cout << "checking white " << c.getX() << c.getY() << _fieldsUnderAttackByWhite[c.getY()][c.getX()] << std::endl;;
		return _fieldsUnderAttackByWhite[c.getY()][c.getX()];
	}
	else if (color == 1)
	{
		//std::cout << "checking black " << c.getX() << c.getY() << _fieldsUnderAttackByBlack[c.getY()][c.getX()] << std::endl;
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