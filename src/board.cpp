#include <iostream>
#include "board.hpp"

void Board::dealFlop(Deck &deck)
{
    for (int i = 0; i < 3; ++i)
    {
        communityCards.push_back(deck.dealCard());
    }
}

void Board::dealTurn(Deck &deck)
{
    communityCards.push_back(deck.dealCard());
}

void Board::dealRiver(Deck &deck)
{
    communityCards.push_back(deck.dealCard());
}

void Board::show() const
{
    std::cout << "Board: ";
    for (const Card &card : communityCards)
    {
        std::cout << card.toString() << " ";
    }
    std::cout << "\n";
}

std::vector<Card> Board::getCards() const
{
    return communityCards;
}