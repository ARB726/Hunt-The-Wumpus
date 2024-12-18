#include "bats.hpp"

Bats::Bats() {} // Default constructor for Bats class

std::string Bats::percept()
{
    // Returns the percept message when encountering bats
    return "You hear wings flapping.";
}

void Bats::encounter(player &player)
{
    int randomRoom = rand() % 4;
    switch (randomRoom)
    {
    case 0:
    {
        // Moves the player up if possible, otherwise moves down
        if (player.y - 1 > 0)
        {
            player.y--;
        }
        else
        {
            player.y++;
        }
        break;
    }
    case 1:
    {
        // Moves the player down if possible, otherwise moves up
        if (player.y + 1 < player.height)
        {
            player.y++;
        }
        else
        {
            player.y--;
        }
        break;
    }
    case 2:
    {
        // Moves the player left if possible, otherwise moves right
        if (player.x - 1 > 0)
        {
            player.x--;
        }
        else
        {
            player.x++;
        }
        break;
    }
    case 3:
    {
        // Moves the player right if possible, otherwise moves left
        if (player.x + 1 < player.width)
        {
            player.x++;
        }
        else
        {
            player.x--;
        }
        break;
    }
    default:
        break;
    }
}

char Bats::getSymbol() const
{
    // Returns the symbol representing bats
    return 'B';
}
