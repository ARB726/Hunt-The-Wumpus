#ifndef cave_HPP
#define cave_HPP
#include "room.hpp"
#include <vector>
class cave
{
private:
    std::vector<std::vector<std::vector<Room>>> cave_system;

public:
    //constructor for cave class
    cave()=default;
    //destructor for cave class
    ~cave()=default;
    //constructor for cave class
    cave(int x, int y, int z);
    /*
    name: setEvent
    pre: x, y, z are valid coordinates, event is a valid pointer
    post: sets an event in a room    
    */
    void setEvent(int x, int y, int z, Event *event);
    /*
    name: getEvent
    pre: x, y, z are valid coordinates
    post: returns the event in a room
    */
    Event *getEvent(int x, int y, int z) const;
    /*
    name: removeEvent
    pre: x, y, z are valid coordinates
    post: removes an event from a room
    */
    void removeEvent(int x, int y, int z);
    /*
    name: isOccupied
    pre: x, y, z are valid coordinates
    post: checks if a room is occupied
    */
    bool isOccupied(int x, int y, int z) const;
};
#endif