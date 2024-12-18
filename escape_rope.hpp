#ifndef ESCAPE_ROPE_HPP
#define ESCAPE_ROPE_HPP

#include "event.hpp"
#include <iostream>

class EscapeRope : public Event
{ // EscapeRope derived from event
public:
    EscapeRope(); // default constructor
    /*
    name: percept
    pre: none
    post: returns the percept message when encountering an escape rope
    */
    std::string percept() override;
    /*
    name: encounter
    pre: none
    post: moves the player to the starting room when encountering an escape rope
    */

    void encounter(player &player) override;
    /*
    name: getSymbol
    pre: none
    post: returns the symbol representing an escape rope in the game
    */
    char getSymbol() const override;
};

#endif
