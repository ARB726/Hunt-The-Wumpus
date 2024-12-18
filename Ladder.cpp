#include "Ladder.hpp"

Ladder::Ladder(bool up_ladder) : up_ladder(up_ladder) {}//constructor for Ladder class

std::string Ladder::percept()//returns the percept message when encountering a ladder
{
    return "";
}
void Ladder::encounter(player &player)//moves the player up or down a level when encountering a ladder
{
    if (up_ladder)//if the ladder is going up
    {
        player.z++;
    }
    else//if the ladder is going down
    {
        player.z--;
    }
}
char Ladder::getSymbol() const//returns the symbol representing a ladder in the game
{
    if (this->up_ladder)//if the ladder is going up
    {
        return '^';//return the symbol for up
    }
    else//if the ladder is going down
    {
        return 'v';//return the symbol for down
    }
}
