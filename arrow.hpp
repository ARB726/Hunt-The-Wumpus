#ifndef ARROW_HPP
#define ARROW_HPP

#include "event.hpp"
#include <iostream>
// Arrow class, derived from Event
class Arrow : public Event
{
public:
    Arrow(); // Default constructor for Arrow class
    /*
    name: percept
    pre: none
    post: returns a perceptual message indicating the presence of an arrow in an adjacent room
    */
    std::string percept() override;
    /*
    name: encounter
    pre: none
    post: handles the encounter when a player finds an arrow
    */

    void encounter(player &player) override;
    /*
    name: getSymbol
    pre: none
    post: returns the symbol representing an arrow in the game
    */
    char getSymbol() const override;
};

#endif
