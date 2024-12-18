#ifndef GOLD_HPP
#define GOLD_HPP

#include "event.hpp"
#include <iostream>

class Gold : public Event// Gold derived from event
{
public:
    Gold();// default constructor
    /*
    name: percept
    pre: none
    post: returns the percept message when encountering gold
    */

    std::string percept() override;
    /*
    name: encounter
    pre: none
    post: adds gold to the player's inventory when encountering gold
    */
    void encounter(player &player) override;
    /*
    name: getSymbol
    pre: none
    post: returns the symbol representing gold in the game
    */
    char getSymbol() const override;
};

#endif
