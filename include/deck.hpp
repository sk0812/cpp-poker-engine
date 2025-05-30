#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include "card.hpp"

class Deck
{
public:
    Deck();
    void shuffle();
    Card dealCard();
    bool isEmpty() const;
    int remainingCards() const;

private:
    std::vector<Card> cards;
    int currentIndex;
};

#endif // DECK_HPP