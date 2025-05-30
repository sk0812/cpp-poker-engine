#include <algorithm>
#include <random>
#include <chrono>
#include "deck.hpp"

Deck::Deck()
{
    cards.reserve(52);
    for (int s = 0; s < 4; ++s)
    {
        for (int r = 2; r <= 14; ++r)
        {
            cards.emplace_back(static_cast<Rank>(r), static_cast<Suit>(s));
        }
    }
    shuffle();
    currentIndex = 0;
}

void Deck::shuffle()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    currentIndex = 0;
}

Card Deck::dealCard()
{
    if (currentIndex < cards.size())
    {
        return cards[currentIndex++];
    }
    else
    {
        throw std::out_of_range("No cards left in the deck.");
    }
}

bool Deck::isEmpty() const
{
    return currentIndex >= cards.size();
}

int Deck::remainingCards() const
{
    return static_cast<int>(cards.size() - currentIndex);
}