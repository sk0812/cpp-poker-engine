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
};

#endif // EVALUATOR_HPP