#include "wumpus.hpp"
#include <cstdlib>

Wumpus::Wumpus() {}//constructor for Wumpus class

std::string Wumpus::percept()//returns the percept message when encountering a wumpus
{
    return "You smell a terrible stench.";
}

void Wumpus::encounter(player &player)//kills the player when encountering a wumpus
{
    player.killed_by_wumpus = true;//indicate the player was killed by the wumpus
    player.killed = true;//indicate the player was killed
}
char Wumpus::getSymbol() const//returns the symbol representing a wumpus in the game
{
    return 'W';
}
