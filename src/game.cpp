#include <iostream>
#include "deck.hpp"
#include "game.hpp"

Game::Game()
{
    std::cout << "Game initialised.\n";
}

void Game::start()
{
    std::cout << "Starting hand...\n";

    players.emplace_back("Player 1");
    players.emplace_back("Player 2");

    for (Player &player : players)
    {
        player.receiveCard(deck.dealCard());
        player.receiveCard(deck.dealCard());
    }

    for (const Player &player : players)
    {
        player.showHand();
    }
}