#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include <vector>
#include "card.hpp"

enum class HandRank
{
    HighCard,
    Pair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush
};

struct EvaluatedHand
{
    HandRank rank;
    std::vector<Rank> tiebreakers; // To break ties within same rank
};

class Evaluator
{
public:
    EvaluatedHand evaluate(const std::vector<Card> &cards);
    static int compareHands(const EvaluatedHand &h1, const EvaluatedHand &h2);
};

#endif // EVALUATOR_HPP