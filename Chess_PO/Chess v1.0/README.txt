Chess Game Project.

This is an implementation of game of chess, written in C++, with support of SFML (Simple and Fast Multimedia Library).
Project includes a game of chess between two players with GUI. Game starts with player controlling white pieces to move and ends when there is
checkmate or stalemate. Game contains checking if a move done by the player is legal in terms of chess rules. Special moves (castle, enPassant) are also implemented.

There is possible configuration of some propeties of the game - it can be done by editing the config.txt file

Classes used in this project:

-Board - includes most of the game logic

-Coordinates - representation of positions on the chessboard

-Piece - abstract class for all chess pieces, each of them implements piece movement according to chess rules.

and the following classes inherits from the Piece class:

-Pawn

-Rook

-Knight

-Bishop

-Queen

-King

More detailed description of classes and their implementations can be found in source files. 

How to compile:
This application works on Windows only (tested on Windows 10)
There are two ways to compile this project:

using g++ manually, by typing following commands in shell opened in project folder:

g++ -c .\source\*.cpp -I .\source\include -DSFML_STATIC
g++ .\*.o -o Chess.exe -L .\lib -l:libsfml-graphics-s.a -l:libsfml-window-s.a -l:libsfml-system-s.a -l:libfreetype.a -lopengl32 -lwinmm -lgdi32
del *.o

or using make command in shell opened in project folder (make sure there's a makefile in project folder):

make all


To run this application, run file Chess.exe that should appear in project folder after compiling.