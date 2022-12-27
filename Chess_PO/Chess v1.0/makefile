PROJECT=Chess
LIBS=libsfml-graphics.a libsfml-window.a libsfml-system.a libfreetype.a -lopengl32 -lwinmm -lgdi32
INC=-I.\source\include 

all: chess

Chess_PO.o: .\source\Chess_PO.cpp
	g++ -c ".\source\Chess_PO.cpp" $(INC) -DSFML_STATIC -o Chess_PO.o

Board.o: .\source\Board.cpp
	g++ -c ".\source\Board.cpp" $(INC) -DSFML_STATIC -o Board.o

Bishop.o: .\source\Bishop.cpp
	g++ -c ".\source\Bishop.cpp" $(INC) -DSFML_STATIC -o Bishop.o

coordinates.o: .\source\coordinates.cpp
	g++ -c ".\source\coordinates.cpp" $(INC) -DSFML_STATIC -o coordinates.o

King.o: .\source\King.cpp
	g++ -c ".\source\King.cpp" $(INC) -DSFML_STATIC -o King.o

Knight.o: .\source\Knight.cpp
	g++ -c ".\source\Knight.cpp" $(INC) -DSFML_STATIC -o Knight.o

Pawn.o: .\source\Pawn.cpp
	g++ -c ".\source\Pawn.cpp" $(INC) -DSFML_STATIC -o Pawn.o

Piece.o: .\source\Piece.cpp
	g++ -c ".\source\Piece.cpp" $(INC) -DSFML_STATIC -o Piece.o

Queen.o: .\source\Queen.cpp
	g++ -c ".\source\Queen.cpp" $(INC) -DSFML_STATIC -o Queen.o

Rook.o: .\source\Rook.cpp
	g++ -c ".\source\Rook.cpp" $(INC) -DSFML_STATIC -o Rook.o

utils.o: .\source\utils.cpp
	g++ -c ".\source\utils.cpp" $(INC) -DSFML_STATIC -o utils.o

chess: Chess_PO.o Board.o Bishop.o coordinates.o King.o Knight.o Pawn.o Piece.o Queen.o Rook.o utils.o
	@echo "** Building the game..."
	g++ Chess_PO.o Board.o Bishop.o coordinates.o King.o Knight.o Pawn.o Piece.o Queen.o Rook.o utils.o -o $(PROJECT) -L .\lib -l:libsfml-graphics-s.a -l:libsfml-window-s.a -l:libsfml-system-s.a -l:libfreetype.a -lopengl32 -lwinmm -lgdi32
	@echo "** Removing object files..."
	del -f *.o 
	@echo "**process completed successfully**"


