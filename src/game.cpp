#include <iostream>
#include "deck.hpp"
#include "game.hpp"

Game::Game()
{
    std::cout << "Game initialised.\n";
}

void Game::start()
{
    std::cout << "Game started. Dealing 5 cards:\n";
    Deck deck;
    for (int i = 0; i < 5; ++i)
    {
        Card c = deck.dealCard();
        std::cout << c.toString() << " ";
    }
    std::cout << "\n";
}