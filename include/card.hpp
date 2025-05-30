#ifndef CARD_HPP
#define CARD_HPP

#include <string>

enum class Suit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum class Rank
{
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

class Card
{
public:
    Card(Rank rank, Suit suit);
    std::string toString() const;
    Rank getRank() const;
    Suit getSuit() const;

private:
    Rank rank;
    Suit suit;
};

#endif // CARD_HPP