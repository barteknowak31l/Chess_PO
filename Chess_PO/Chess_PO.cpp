#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chess!");
    Board board;

    Pawn b_pawn_0(0, 75, 1, 1);
    Pawn b_pawn_1(75, 75, 1, 2);
    Pawn b_pawn_2(150, 75, 1, 3);
    Pawn b_pawn_3(225, 75, 1, 4);
    Pawn b_pawn_4(300, 75, 1, 5);
    Pawn b_pawn_5(375, 75, 1, 6);
    Pawn b_pawn_6(450, 75, 1, 7);
    Pawn b_pawn_7(525, 75, 1, 8);


    board.init();



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
            }
        }

        //draw step
        window.clear();

        board.drawBoard(window);
        Piece::drawPieces(window);

        window.display();
    }

    return 0;
}