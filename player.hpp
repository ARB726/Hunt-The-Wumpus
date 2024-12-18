#ifndef player_HPP
#define player_HPP

struct player// struct for player
{
    int health = 3;//player health
    int arrows = 0;//player arrows
    bool has_gold = false;//boolean to determine if the player has gold
    bool has_won = false;//boolean to determine if the player has won
    bool killed_by_wumpus = false;//boolean to determine if the player was killed by the wumpus
    bool killed = false;//boolean to determine if the player was killed
    int x = 0;//horizontal add 1 to x we go right
    int y = 0;//vertical if we add 1 to y we go down
    int z = 0;//moving through the caves 
    int width = 0;//width of the cave
    int height = 0;//height of the cave
};
#endif