#include <iostream>
#include "player.hpp"

Player::Player(const std::string &name) : name(name) {}

void Player::receiveCard(const Card &card)
{
    if (hand.size() < 2)
    {
        hand.push_back(card);
    }
}

void Player::showHand() const
{
    std::cout << name << "'s hand: ";
    for (const Card &c : hand)
    {
        std::cout << c.toString() << " ";
    }
    std::cout << "\n";
}

std::string Player::getName() const
{
    return name;
}

std::vector<Card> Player::getHand() const
{
    return hand;
}