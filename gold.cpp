#include "gold.hpp"

Gold::Gold() {}// Default constructor for Gold class

std::string Gold::percept() {// Returns a perceptual message indicating the presence of gold in an adjacent room
    return "You see something shimmer nearby.";
}

void Gold::encounter(player& player) {// Handles the encounter when a player finds gold
    player.has_gold = true;// Sets the player's gold flag to true
    std::cout << "You found the gold!" << std::endl; // Prints a message indicating the player has found the gold
}

char Gold::getSymbol() const {// Returns the symbol representing gold in the game
    return 'G';// Return the symbol 'G' for gold
}
