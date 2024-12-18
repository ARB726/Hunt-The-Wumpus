#ifndef WUMPUS_HPP
#define WUMPUS_HPP

#include "event.hpp"
#include <iostream>

class Wumpus : public Event {// Wumpus derived from event
public:// public member functions
    Wumpus();// default constructor
    /*
    name: percept
    pre: none
    post: returns the percept message when encountering the wumpus
    */
    std::string percept() override;
    /*
    name: encounter
    pre: none
    post: handles the encounter when a player finds the wumpus
    */
    void encounter(player&player) override;
    /*
    name: getSymbol
    pre: none
    post: returns the symbol representing the wumpus in the game
    */
    char getSymbol() const override;

private:
    // void playTicTacToe();
    void playTicTacToe();
};

#endif
