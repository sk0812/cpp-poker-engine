#include "card.hpp"

Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

std::string Card::toString() const
{
    std::string rankStr;
    std::string suitStr;

    switch (rank)
    {
    case Rank::Two:
        rankStr = "2";
        break;
    case Rank::Three:
        rankStr = "3";
        break;
    case Rank::Four:
        rankStr = "4";
        break;
    case Rank::Five:
        rankStr = "5";
        break;
    case Rank::Six:
        rankStr = "6";
        break;
    case Rank::Seven:
        rankStr = "7";
        break;
    case Rank::Eight:
        rankStr = "8";
        break;
    case Rank::Nine:
        rankStr = "9";
        break;
    case Rank::Ten:
        rankStr = "10";
        break;
    case Rank::Jack:
        rankStr = "J";
        break;
    case Rank::Queen:
        rankStr = "Q";
        break;
    case Rank::King:
        rankStr = "K";
        break;
    case Rank::Ace:
        rankStr = "A";
        break;
    }

    switch (suit)
    {
    case Suit::Hearts:
        suitStr = "♥";
        break;
    case Suit::Diamonds:
        suitStr = "♦";
        break;
    case Suit::Clubs:
        suitStr = "♣";
        break;
    case Suit::Spades:
        suitStr = "♠";
        break;
    }

    return rankStr + suitStr;
}

Rank Card::getRank() const
{
    return rank;
}

Suit Card::getSuit() const
{
    return suit;
}