#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "card.hpp"
#include "deck.hpp"

class Board
{
public:
    void dealFlop(Deck &deck);
    void dealTurn(Deck &deck);
    void dealRiver(Deck &deck);
    void show() const;
    std::vector<Card> getCards() const;

private:
    std::vector<Card> communityCards;
};

#endif // BOARD_HPP