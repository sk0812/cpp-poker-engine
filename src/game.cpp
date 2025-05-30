#include <iostream>
#include "deck.hpp"
#include "game.hpp"
#include "board.hpp"

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

    Board board;
    std::cout << "\nDealing flop...\n";
    board.dealFlop(deck);
    board.show();

    std::cout << "Dealing turn...\n";
    board.dealTurn(deck);
    board.show();

    std::cout << "Dealing river...\n";
    board.dealRiver(deck);
    board.show();
}