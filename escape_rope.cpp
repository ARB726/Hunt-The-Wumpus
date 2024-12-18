#include "escape_rope.hpp"

EscapeRope::EscapeRope() {}// Default constructor for EscapeRope class

std::string EscapeRope::percept()// Returns a perceptual message indicating the presence of an escape rope in an adjacent room
{
    return ""; // No percept for escape rope
}

void EscapeRope::encounter(player &player)// Handles the encounter when a player finds an escape rope
{
    if (player.has_gold)// Checks if the player has collected the gold
    {
        player.has_won = true;// Sets the player's win flag to true
        std::cout << "You have escaped the cave with the gold!" << std::endl;// Prints a message indicating the player has escaped with the gold
    }
    else
    {
        std::cout << "You must collect the gold before you can escape!" << std::endl;// Prints a message indicating the player must collect the gold before escaping
    }
}

char EscapeRope::getSymbol() const// Returns the symbol representing an escape rope in the game
{
    return 'E';// Return the symbol 'E' for escape rope
}
