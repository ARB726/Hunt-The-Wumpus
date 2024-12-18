#ifndef STALACTITES_HPP
#define STALACTITES_HPP

#include "event.hpp"
#include <iostream>

class Stalactites : public Event {// Stalactites derived from event
public:// public member functions
    Stalactites();// default constructor
    /*
    name: percept
    pre: none
    post: returns the percept message when encountering stalactites
    */
    std::string percept() override;//
    /*
    name: encounter
    pre: none
    post: handles the encounter when a player finds stalactites
    */
    void encounter(player&player) override;
    /*
    name: getSymbol
    pre: none
    post: returns the symbol representing stalactites in the game
    */
    char getSymbol() const override;
};

#endif
