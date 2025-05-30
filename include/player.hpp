#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "card.hpp"

class Player
{
public:
    Player(const std::string &name);
    void receiveCard(const Card &card);
    void showHand() const;
    std::string getName() const;
    std::vector<Card> getHand() const;

private:
    std::string name;
    std::vector<Card> hand;
};

#endif // PLAYER_HPP