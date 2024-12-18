#include "cave.hpp"

cave::cave(int x, int y, int z)//constructor for cave class
{
    this->cave_system = std::vector<std::vector<std::vector<Room>>>(z, std::vector<std::vector<Room>>(x, std::vector<Room>(y)));
    //cave_system is a 3D vector of Room objects
}
void cave::setEvent(int x, int y, int z, Event *event)//sets an event in a room
{
    cave_system.at(z).at(x).at(y).setEvent(event);
    //sets the event in the room at the specified coordinates
}
Event *cave::getEvent(int x, int y, int z) const //returns the event in a room
{
    return cave_system.at(z).at(x).at(y).getEvent();//returns the event in the room at the specified coordinates
}
void cave::removeEvent(int x, int y, int z)//removes an event from a room
{
    cave_system.at(z).at(x).at(y).removeEvent();//removes the event from the room at the specified coordinates
}
bool cave::isOccupied(int x, int y, int z) const//checks if a room is occupied
{
    return cave_system.at(z).at(x).at(y).isOccupied();//returns true if the room at the specified coordinates is occupied
}

