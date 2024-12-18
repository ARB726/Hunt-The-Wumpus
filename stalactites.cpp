#include "stalactites.hpp"

Stalactites::Stalactites() {}//constructor for Stalactites class

std::string Stalactites::percept()//returns the percept message when encountering stalactites
{
    return "You hear water dripping.";//return the percept message
}

void Stalactites::encounter(player &player)//drops stalactites on the player
{
    std::cout << "Stalactites fall! There's a 50% chance you get hit." << std::endl;//print the message indicating stalactites are falling
    if (rand() % 2 == 0)//if the player is hit by the falling stalactites
    {
        std::cout << "You were hit by falling stalactites!" << std::endl;
        player.killed = true; // Indicate the player was hit and loses a life
        player.health--;      // Indicate the player was hit and loses a life
    }
    else//if the player is not hit by the falling stalactites
    {
        std::cout << "You narrowly escaped the falling stalactites." << std::endl;
        // return true; // Indicate the player escaped unharmed
    }
}

char Stalactites::getSymbol() const//returns the symbol representing stalactites in the game
{
    return 'S';//return the symbol for stalactites
}
