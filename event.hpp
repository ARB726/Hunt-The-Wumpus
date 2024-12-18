#ifndef EVENT_HPP
#define EVENT_HPP
#include "player.hpp"
#include <string>
class Event {
public:
    virtual ~Event() = default;// Destructor
    Event() = default;// Default constructor
    // Pure virtual functions to be overridden by derived classes
    /*
    name: percept
    pre: none
    post: returns a perceptual message indicating the presence of an event in an adjacent room
    */




    virtual std::string percept() = 0;
    /*
    name: encounter
    pre: none
    post: handles the encounter when a player finds an event
    */
    virtual void encounter(player&player) = 0;
    /*
    name: getSymbol
    pre: none
    post: returns the symbol representing an event in the game
    */
    virtual char getSymbol() const = 0;
};

#endif
