#include <iostream>
#include "deck.hpp"
#include "game.hpp"
#include "board.hpp"
#include "evaluator.hpp"

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

    Evaluator evaluator;

    std::cout << "\nEvaluating hands...\n";

    for (const Player &player : players)
    {
        std::vector<Card> totalCards = player.getHand();
        std::vector<Card> boardCards = board.getCards();
        totalCards.insert(totalCards.end(), boardCards.begin(), boardCards.end());

        EvaluatedHand hand = evaluator.evaluate(totalCards);

        std::cout << player.getName() << ": ";

        if (hand.rank == HandRank::StraightFlush && hand.tiebreakers[0] == Rank::Ace)
        {
            std::cout << "Royal Flush";
        }
        else
        {
            switch (hand.rank)
            {
            case HandRank::HighCard:
                std::cout << "High Card";
                break;
            case HandRank::Pair:
                std::cout << "Pair";
                break;
            case HandRank::TwoPair:
                std::cout << "Two Pair";
                break;
            case HandRank::ThreeOfAKind:
                std::cout << "Three of a Kind";
                break;
            case HandRank::Straight:
                std::cout << "Straight";
                break;
            case HandRank::Flush:
                std::cout << "Flush";
                break;
            case HandRank::FullHouse:
                std::cout << "Full House";
                break;
            case HandRank::FourOfAKind:
                std::cout << "Four of a Kind";
                break;
            case HandRank::StraightFlush:
                std::cout << "Straight Flush";
                break;
            }
        }

        std::cout << "\n";
    }

    EvaluatedHand bestHand = evaluator.evaluate(players[0].getHand());
    std::string winner = players[0].getName();

    for (size_t i = 1; i < players.size(); ++i)
    {
        std::vector<Card> total = players[i].getHand();
        std::vector<Card> boardCards = board.getCards();
        total.insert(total.end(), boardCards.begin(), boardCards.end());

        EvaluatedHand currentHand = evaluator.evaluate(total);

        int result = Evaluator::compareHands(currentHand, bestHand);
        if (result == 1)
        {
            bestHand = currentHand;
            winner = players[i].getName();
        }
        else if (result == 0 && winner != players[i].getName())
        {
            winner += " & " + players[i].getName(); // Tie
        }
    }

    std::cout << "\nWinner: " << winner << "\n";
}