#ifndef BATS_HPP
#define BATS_HPP

#include "event.hpp"
#include <iostream>

class Bats : public Event
{ // Bats derived from event
public:
    Bats(); // default constructor
    /*
    name: percept
    pre: none
    post: returns the percept message when encountering bats
    */

    std::string percept() override;
    /*
    name: encounter
    pre: none
    post: moves the player to a random room when encountering bats
    */

    void encounter(player &player) override;

    /*
    name: getSymbol
    pre: none
    post: returns the symbol representing bats in the game
    */

    char getSymbol() const override;
};

#endif
