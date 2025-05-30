#include "player.hpp"
#include "deck.hpp"
#include <vector>

class Game
{
public:
    Game();
    void start();

private:
    Deck deck;
    std::vector<Player> players;
};