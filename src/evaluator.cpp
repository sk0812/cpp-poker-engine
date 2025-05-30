#include <map>
#include <algorithm>
#include <set>
#include "evaluator.hpp"

EvaluatedHand Evaluator::evaluate(const std::vector<Card> &cards)
{
    std::map<Rank, int> rankCount;
    std::map<Suit, std::vector<Rank>> suitMap;

    for (const Card &c : cards)
    {
        rankCount[c.getRank()]++;
        suitMap[c.getSuit()].push_back(c.getRank());
    }

    std::vector<Rank> allRanks;
    for (const Card &c : cards)
    {
        allRanks.push_back(c.getRank());
    }

    auto getSortedRanks = [](const std::vector<Rank> &ranks)
    {
        std::vector<Rank> sorted = ranks;
        std::sort(sorted.begin(), sorted.end(), std::greater<>());
        return sorted;
    };

    auto isStraight = [](std::set<int> values)
    {
        std::vector<int> sorted(values.begin(), values.end());
        if (values.count(14))
            sorted.insert(sorted.begin(), 1); // Ace-low

        for (size_t i = 0; i + 4 < sorted.size(); ++i)
        {
            if (sorted[i] + 1 == sorted[i + 1] &&
                sorted[i] + 2 == sorted[i + 2] &&
                sorted[i] + 3 == sorted[i + 3] &&
                sorted[i] + 4 == sorted[i + 4])
            {
                return sorted[i + 4]; // lowest card in straight
            }
        }
        return -1;
    };

    // 🔍 Flush?
    Suit flushSuit;
    bool hasFlush = false;
    std::vector<Rank> flushRanks;

    for (auto &[suit, ranks] : suitMap)
    {
        if (ranks.size() >= 5)
        {
            hasFlush = true;
            flushSuit = suit;
            flushRanks = getSortedRanks(ranks);
            break;
        }
    }

    // 🔍 Straight?
    std::set<int> uniqueRanks;
    for (const auto &[rank, _] : rankCount)
        uniqueRanks.insert(static_cast<int>(rank));
    int straightHigh = isStraight(uniqueRanks);

    // 🔍 Straight Flush?
    if (hasFlush)
    {
        std::set<int> flushSet;
        for (Rank r : flushRanks)
            flushSet.insert(static_cast<int>(r));
        int sfHigh = isStraight(flushSet);
        if (sfHigh != -1)
        {
            return EvaluatedHand{HandRank::StraightFlush, {static_cast<Rank>(sfHigh + 4)}};
        }
    }

    // 🔍 Four of a Kind
    for (auto &[rank, count] : rankCount)
    {
        if (count == 4)
        {
            std::vector<Rank> kickers;
            for (auto &[r, c] : rankCount)
            {
                if (r != rank)
                    kickers.push_back(r);
            }
            std::sort(kickers.begin(), kickers.end(), std::greater<>());
            return EvaluatedHand{HandRank::FourOfAKind, {rank, kickers[0]}};
        }
    }

    // 🔍 Full House
    Rank tripRank = Rank::Two;
    Rank pairRank = Rank::Two;
    bool foundTrips = false, foundPair = false;

    for (auto it = rankCount.rbegin(); it != rankCount.rend(); ++it)
    {
        if (it->second >= 3 && !foundTrips)
        {
            tripRank = it->first;
            foundTrips = true;
        }
        else if (it->second >= 2)
        {
            if (!foundPair || it->first != tripRank)
            {
                pairRank = it->first;
                foundPair = true;
            }
        }
    }

    if (foundTrips && foundPair)
    {
        return EvaluatedHand{HandRank::FullHouse, {tripRank, pairRank}};
    }

    // 🔍 Flush (if no SF)
    if (hasFlush)
    {
        return EvaluatedHand{HandRank::Flush, std::vector<Rank>(flushRanks.begin(), flushRanks.begin() + 5)};
    }

    // 🔍 Straight
    if (straightHigh != -1)
    {
        return EvaluatedHand{HandRank::Straight, {static_cast<Rank>(straightHigh + 4)}};
    }

    // 🔍 Three of a Kind
    for (auto it = rankCount.rbegin(); it != rankCount.rend(); ++it)
    {
        if (it->second == 3)
        {
            std::vector<Rank> kickers;
            for (auto &[r, c] : rankCount)
            {
                if (r != it->first)
                    kickers.push_back(r);
            }
            std::sort(kickers.begin(), kickers.end(), std::greater<>());
            return EvaluatedHand{HandRank::ThreeOfAKind, {it->first, kickers[0], kickers[1]}};
        }
    }

    // 🔍 Two Pair
    std::vector<Rank> pairs;
    Rank leftover;
    for (auto &[r, c] : rankCount)
    {
        if (c == 2)
            pairs.push_back(r);
        else
            leftover = r;
    }

    if (pairs.size() >= 2)
    {
        std::sort(pairs.begin(), pairs.end(), std::greater<>());
        return EvaluatedHand{HandRank::TwoPair, {pairs[0], pairs[1], leftover}};
    }

    // 🔍 One Pair
    for (auto it = rankCount.rbegin(); it != rankCount.rend(); ++it)
    {
        if (it->second == 2)
        {
            std::vector<Rank> kickers;
            for (auto &[r, c] : rankCount)
            {
                if (r != it->first)
                    kickers.push_back(r);
            }
            std::sort(kickers.begin(), kickers.end(), std::greater<>());
            return EvaluatedHand{HandRank::Pair, {it->first, kickers[0], kickers[1], kickers[2]}};
        }
    }

    // 🔍 High Card
    std::vector<Rank> allSorted = getSortedRanks(allRanks);
    return EvaluatedHand{HandRank::HighCard, std::vector<Rank>(allSorted.begin(), allSorted.begin() + 5)};
}

int Evaluator::compareHands(const EvaluatedHand &h1, const EvaluatedHand &h2)
{
    if (h1.rank > h2.rank)
        return 1;
    if (h1.rank < h2.rank)
        return -1;

    // Same hand rank — use tiebreakers
    for (size_t i = 0; i < std::min(h1.tiebreakers.size(), h2.tiebreakers.size()); ++i)
    {
        if (h1.tiebreakers[i] > h2.tiebreakers[i])
            return 1;
        if (h1.tiebreakers[i] < h2.tiebreakers[i])
            return -1;
    }

    return 0; // Tie
}