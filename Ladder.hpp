#ifndef ladder_HPP
#define ladder_HPP
#include "event.hpp"
#include "player.hpp"
class Ladder : public Event// Ladder derived from event
{
private:
    bool up_ladder;// boolean to determine if the ladder is going up or down

public:
    Ladder(bool up_ladder);// constructor for ladder class
    /*
    name: percept
    pre: none
    post: returns the percept message when encountering a ladder
    */
    std::string percept() override;
    /*
    name: encounter
    pre: none
    post: moves the player to a random room when encountering a ladder
    */
    void encounter(player &player) override;
    /*
    name: getSymbol
    pre: none
    post: returns the symbol representing a ladder in the game
    */
    char getSymbol() const override;
};
#endif