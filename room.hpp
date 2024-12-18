#ifndef ROOM_HPP
#define ROOM_HPP

#include "event.hpp"

class Room
{
private:
    Event *event; // Private member to store the event

public:
    Room();// default constructor
    ~Room();// destructor
    /*
    name: isOccupied
    pre: none
    post: checks if a room is occupied
    */
    bool isOccupied() const;
    /*
    name: setEvent
    pre: event is a valid pointer
    post: sets an event in a room
    */
    void setEvent(Event *event);
    /*
    name: getEvent
    pre: none
    post: returns the event in a room
    */
    Event *getEvent() const;
    /*
    name: removeEvent
    pre: none
    post: removes an event from a room
    */
    void removeEvent();
};

#endif
