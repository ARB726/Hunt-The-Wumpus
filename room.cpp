#include "room.hpp"

Room::Room() : event(nullptr) {}//constructor for Room class

Room::~Room()//destructor for Room class
{
    if (event != nullptr)//if event is not a nullptr
    {
        delete event;//delete event
        event = nullptr;//set event to nullptr
    }

    delete event;//delete event
}

bool Room::isOccupied() const//checks if a room is occupied
{
    return event != nullptr;//returns true if event is not a nullptr
}

void Room::setEvent(Event *event)//sets an event in a room
{
    this->event = event;//sets the event in the room
}

Event *Room::getEvent() const//returns the event in a room
{
    return event;//returns the event in the room
}

void Room::removeEvent()//removes an event from a room
{
    if (event != nullptr)//if event is not a nullptr
    {
        delete event;//delete event
        event = nullptr;//set event to nullptr
    }
}
