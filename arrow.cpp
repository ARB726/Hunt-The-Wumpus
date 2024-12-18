#include "arrow.hpp"

// Default constructor for Arrow class
Arrow::Arrow() {}

// Returns a perceptual message indicating the presence of an arrow in an adjacent room
std::string Arrow::percept() {
    return "You see an arrow on the ground in an adjacent room.";
}

// Handles the encounter when a player finds an arrow
void Arrow::encounter(player& player) {
    std::cout << "You found an arrow!" << std::endl;
    player.arrows++; // Increment the player's arrow count
}

// Returns the symbol representing an arrow in the game
char Arrow::getSymbol() const {
    return 'A';
}

