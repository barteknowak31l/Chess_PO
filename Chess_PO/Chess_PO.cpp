#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chess!");


    Board board;
    board.setColorsofBoard(sf::Color::White,sf::Color(134,79,0,255));
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

        //update
        window.clear();
        board.update(window);
        Piece::update(window,board);
        window.display();


        //debug
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            Board::printBoard();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            Board::printUnderAttackWhite();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            Board::printUnderAttackBlack();
        }


    }

    return 0;
}