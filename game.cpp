#include <iostream>

#include "game.hpp"
#include "gold.hpp"
#include "bats.hpp"
#include "stalactites.hpp"
#include "wumpus.hpp"
#include "escape_rope.hpp"
#include "arrow.hpp"
#include "Ladder.hpp"

// game implementation
int rand_range(int max)// Returns a random number between 0 and max
{
	return rand() % max;// Returns a random number between 0 and max
}
void game::check_position(int &x, int &y, int z)//checks if a position is valid
{
	bool valid = false;//checks if a position is valid
	bool reroll = false;//checks if a position is valid
	do
	{
		if (this->cave_system.isOccupied(x, y, z) == true)//checks if a position is valid
		{
			reroll = true;
			x = rand_range(this->width);//rerolls the x coordinate
			y = rand_range(this->height);//rerolls the y coordinate
		}
		if (reroll == true)
		{
			reroll = false;
		}
		else
		{
			valid = true;
		}

	} while (!valid);
}

void game::create_event(Event *event, int z) {
    // Generate random x and y coordinates within the game dimensions
    int x = rand_range(this->width);
    int y = rand_range(this->height);

    // Check if the position (x, y, z) is valid for placing the event
    this->check_position(x, y, z);

    // Set the event in the cave system at the specified coordinates
    this->cave_system.setEvent(x, y, z, event);

    // If the event is the adventurer ('E'), set the adventurer's starting position
    if (event->getSymbol() == 'E') {
        this->adventurer.x = x;
        this->adventurer.y = y;
        this->adventurer.z = 0;
        this->start_x = x;
        this->start_y = y;
    }
}

//game constructor
game::game(int width, int height, bool debug, int num_rooms) 
    : width(width), height(height), debug(debug), num_rooms(num_rooms) 
{
    // Set the dimensions of the adventurer's area
    this->adventurer.width = width;
    this->adventurer.height = height;

    // Initialize the cave system with the specified width, height, and number of rooms
    this->cave_system = cave(width, height, num_rooms);

    // Create and place the EscapeRope event in the cave
    create_event(new EscapeRope(), 0);

    // Create and place the Wumpus event in a random room
    create_event(new Wumpus(), rand_range(num_rooms));

    // Create and place the Gold event in a random room
    create_event(new Gold(), rand_range(num_rooms));

    // Loop through each room to create and place events
    for (int i = 0; i < num_rooms; i++) {
        // Create and place two Bats events in the current room
        create_event(new Bats(), i);
        create_event(new Bats(), i);

        // Create and place two Stalactites events in the current room
        create_event(new Stalactites(), i);
        create_event(new Stalactites(), i);

        // Create and place two Arrow events in the current room
        create_event(new Arrow(), i);
        create_event(new Arrow(), i);

        // Create and place Ladder events in appropriate rooms
        if (i > 0 && i < num_rooms - 1) {
            // Create and place an up and down Ladder in middle rooms
            create_event(new Ladder(true), i);
            create_event(new Ladder(false), i);
        } else if (i == 0) {
            // Create and place an up Ladder in the first room
            create_event(new Ladder(true), i);
        } else if (i == num_rooms - 1) {
            // Create and place a down Ladder in the last room
            create_event(new Ladder(false), i);
        }
    }
}


void game::display_game() const {
    // Print two empty lines for spacing
    std::cout << std::endl << std::endl;

    // Display the number of arrows remaining for the adventurer
    std::cout << "Arrows remaining: " << this->adventurer.arrows << std::endl;

    // Create the top border of the game board
    std::string row_border = "--";
    for (int i = 0; i < this->width; ++i) {
        row_border += "-----";
    }

    // Print the top border
    std::cout << row_border << std::endl;

    // Loop through each row of the game board
    for (int x = 0; x < this->height; ++x) {
        std::cout << "||";

        // Loop through each column of the game board
        for (int y = 0; y < this->width; ++y) {
            if (this->debug == false) {
                // In non-debug mode
                if (x == this->adventurer.x && y == this->adventurer.y) {
                    // Display the adventurer's position
                    std::cout << "*";
                } else if (this->cave_system.isOccupied(x, y, this->adventurer.z) == true) {
                    // Display symbols for specific events if occupied
                    if (this->cave_system.getEvent(x, y, this->adventurer.z)->getSymbol() == '^') {
                        std::cout << "^";
                    } else if (this->cave_system.getEvent(x, y, this->adventurer.z)->getSymbol() == 'v') {
                        std::cout << "v";
                    }
                } else {
                    // Display empty space
                    std::cout << " ";
                }
            } else {
                // In debug mode
                if (x == this->adventurer.x && y == this->adventurer.y) {
                    // Display the adventurer's position
                    std::cout << "*";
                } else if (this->cave_system.isOccupied(x, y, this->adventurer.z) == true) {
                    // Display the symbol of the event occupying the position
                    std::cout << this->cave_system.getEvent(x, y, this->adventurer.z)->getSymbol();
                } else {
                    // Display empty space
                    std::cout << " ";
                }
            }
            std::cout << " ||";
        }
        std::cout << std::endl;
        std::cout << row_border << std::endl;
    }
}


bool game::check_win() const//checks if the player has won
{
	return this->adventurer.has_won;//returns true if the player has won
}

bool game::check_lose() const {
    // Check if the adventurer's health is less than or equal to 0
    if (this->adventurer.health <= 0) {
        // Return true if the adventurer has no health left, indicating a loss
        return true;
    } else {
        // Return false if the adventurer still has health remaining
        return false;
    }
}


bool game::is_direction(char c) {
    // Checks if a character is a valid direction (w, a, s, or d)
    return c == 'w' || // 'w' for moving up
           c == 'a' || // 'a' for moving left
           c == 's' || // 's' for moving down
           c == 'd';   // 'd' for moving right
}


// Converts the given direction character to lowercase
char game::to_lower(char direction) {
    // Currently, this function simply returns the input character as it is.
    return direction;
}

// Checks if the adventurer can move in the specified direction
bool game::can_move_in_direction(char direction) {
    switch (direction) {
        case 'w': {
            // Check if moving up is within bounds
            if (this->adventurer.x - 1 < 0) {
                return false; // Cannot move up, out of bounds
            } else {
                return true; // Can move up
            }
            break;
        }
        case 's': {
            // Check if moving down is within bounds
            if (this->adventurer.x + 1 < this->adventurer.height) {
                return true; // Can move down
            } else {
                return false; // Cannot move down, out of bounds
            }
            break;
        }
        case 'a': {
            // Check if moving left is within bounds
            if (this->adventurer.y - 1 < 0) {
                return false; // Cannot move left, out of bounds
            } else {
                return true; // Can move left
            }
            break;
        }
        case 'd': {
            // Check if moving right is within bounds
            if (this->adventurer.y + 1 < this->adventurer.width) {
                return true; // Can move right
            } else {
                return false; // Cannot move right, out of bounds
            }
            break;
        }
        default:
            // If the direction is not valid, return false
            break;
    }
    return false; // Return false if none of the cases match
}



// Checks if the given action is valid
bool game::is_valid_action(char action) {
    if (this->is_direction(action)) {
        // If the action is a direction, check if the adventurer can move in that direction
        char direction = action;
        return this->can_move_in_direction(direction);
    } else if (action == 'f') {
        // If the action is to fire an arrow, check if the adventurer has arrows remaining
        return this->adventurer.arrows > 0;
    }
    // If the action is neither a direction nor firing an arrow, it is invalid
    return false;
}

// Prints an error message based on the invalid action
void game::print_action_error(char action) {
    if (this->is_direction(action)) {
        // If the action is a direction but invalid, inform the player they can't move in that direction
        std::cout << "You can't move in that direction!" << std::endl << std::endl;
    } else if (action == 'f') {
        // If the action is to fire an arrow but there are no arrows left, inform the player
        std::cout << "You're out of arrows!" << std::endl << std::endl;
    } else {
        // If the action is invalid, inform the player
        std::cout << std::endl << "That's an invalid input!" << std::endl << std::endl;
    }
}


// Prompts the player to input an action and validates the input
char game::get_player_action() {
    char action;
    bool first = true;
    do {
        if (!first) {
            char previous_action = action;
            this->print_action_error(previous_action); // Print an error if the previous action was invalid
        }
        first = false;

        // Prompt the player for an action
        std::cout << std::endl << std::endl << "What would you like to do?" << std::endl << std::endl;
        std::cout << "w: move up" << std::endl;
        std::cout << "a: move left" << std::endl;
        std::cout << "s: move down" << std::endl;
        std::cout << "d: move right" << std::endl;
        std::cout << "f: fire an arrow" << std::endl;

        std::cin >> action;
        action = this->to_lower(action); // Convert the input to lowercase
    } while (!this->is_valid_action(action)); // Continue until a valid action is input

    return action;
}

// Prompts the player to input a direction for firing an arrow and validates the input
char game::get_arrow_fire_direction() {
    char direction;
    bool first = true;
    do {
        if (!first) {
            std::cout << std::endl << "That's an invalid input!" << std::endl << std::endl;
        }
        first = false;

        // Prompt the player for a direction to fire the arrow
        std::cout << std::endl << std::endl << "What direction would you like to fire the arrow?" << std::endl << std::endl;
        std::cout << "w: up" << std::endl;
        std::cout << "a: left" << std::endl;
        std::cout << "s: down" << std::endl;
        std::cout << "d: right" << std::endl;

        std::cin >> direction;
        direction = this->to_lower(direction); // Convert the input to lowercase
    } while (!this->is_direction(direction)); // Continue until a valid direction is input

    return direction;
}

// Moves the adventurer up
void game::move_up() {
    this->adventurer.x--;
}

// Moves the adventurer down
void game::move_down() {
    this->adventurer.x++;
}

// Moves the adventurer left
void game::move_left() {
    this->adventurer.y--;
}

// Moves the adventurer right
void game::move_right() {
    this->adventurer.y++;
}


// Moves the adventurer in the specified direction
void game::move(char direction) {
    if (direction == 'w') {
        // Move up
        this->move_up();
    } else if (direction == 'a') {
        // Move left
        this->move_left();
    } else if (direction == 'd') {
        // Move right
        this->move_right();
    } else {
        // Move down
        this->move_down();
    }
}

// Moves the Wumpus to a random room
void game::move_wumpus() {
    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            // Check if the current position is occupied
            if (this->cave_system.isOccupied(x, y, this->adventurer.z) == true) {
                // Check if the event at the current position is the Wumpus
                if (this->cave_system.getEvent(x, y, this->adventurer.z)->getSymbol() == 'W') {
                    // Generate a random room number to move the Wumpus to
                    int randomRoom = rand_range(this->num_rooms);
                    // Remove the Wumpus from the current position
                    this->cave_system.removeEvent(x, y, this->adventurer.z);
                    // Create a new Wumpus event in the random room
                    create_event(new Wumpus(), randomRoom);
                }
            }
        }
    }
}

// Checks if the Wumpus is hit at the specified position
void game::check_hit_wumpus(int x, int y) {
    // Check if the specified position is occupied
    if (this->cave_system.isOccupied(x, y, this->adventurer.z) == true) {
        // Check if the event at the specified position is the Wumpus
        if (this->cave_system.getEvent(x, y, this->adventurer.z)->getSymbol() == 'W') {
            // Set the adventurer's win status to true
            this->adventurer.has_won = true;
            std::cout << "You have killed the Wumpus!" << std::endl;
        }
    }
}


bool game::tic_tac_toe()//plays a game of tic-tac-toe
{
	std::cout << "You have encountered the Wumpus!" << std::endl;
	std::cout << "You must play a game of tic-tac-toe to defeat it." << std::endl;
	std::cout << "If you win, you will defeat the Wumpus and win the game." << std::endl;
	std::cout << "If you lose, you will lose a life." << std::endl;
	std::cout << "Good luck!" << std::endl;
	int taken[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};//array to keep track of taken moves
	char board[3][3] = {{'1', '2', '3'},
						{'4', '5', '6'},
						{'7', '8', '9'}}; // Tic-tac-toe board
	int turn = 0;//keeps track of the turn
	bool win = false;//checks if the game has been won
	int wumpus_turn = 0;//keeps track of the Wumpus's turn
	while (!win)//loops until the game is won
	{
		cout << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
		cout << "-+-+-" << endl;
		cout << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
		cout << "-+-+-" << endl;
		cout << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
		int move;//stores the move
		if (turn % 2 == 0)//checks if it is the player's turn
		{
			cout << "Player 1's turn" << endl;//prints the player's turn
			cin >> move;//gets the player's move
			while (move < 1 || move > 9)//checks if the move is valid
			{
				cout << "Invalid move. Try again." << endl;
				cin >> move;//gets the player's move
			}
			taken[move - 1] = 1;//marks the move as taken
		}
		else
		{
			cout << "Player 2's turn" << endl;//prints the player's turn
			move = rand() % 9;//gets a random move
			while (taken[move] == 1)//checks if the move is valid
			{
				move = rand() % 9;//gets a random move
			}
			taken[move] = 1;//marks the move as taken
		}

		char symbol;//stores the symbol
		if (turn % 2 == 0)//
		{
			symbol = 'X';
		}
		else
		{
			symbol = 'O';
		}
		switch (move)
		{
		case 1:
			board[0][0] = symbol;//sets the symbol on the board
			break;
		case 2:
			board[0][1] = symbol;
			break;
		case 3:
			board[0][2] = symbol;
			break;
		case 4:
			board[1][0] = symbol;
			break;
		case 5:
			board[1][1] = symbol;
			break;
		case 6:
			board[1][2] = symbol;
			break;
		case 7:
			board[2][0] = symbol;
			break;
		case 8:
			board[2][1] = symbol;
			break;
		case 9:
			board[2][2] = symbol;
			break;
		default:
			cout << "Invalid move. Try again." << endl;//prints an error message
			turn--;
			break;
		}
		turn++;
		if (turn >= 5)
		{
			if (board[0][0] == symbol && board[0][1] == symbol && board[0][2] == symbol)//checks if the player has won
			{
				win = true;//sets win to true
				cout << "Player " << (turn % 2) + 1 << " wins!" << endl;//prints the winning player
			}
			else if (board[1][0] == symbol && board[1][1] == symbol && board[1][2] == symbol)
			{
				win = true;
				cout << "Player " << (turn % 2) + 1 << " wins!" << endl;
			}
			else if (board[2][0] == symbol && board[2][1] == symbol && board[2][2] == symbol)
			{
				win = true;
				cout << "Player " << (turn % 2) + 1 << " wins!" << endl;
			}
			else if (board[0][0] == symbol && board[1][0] == symbol && board[2][0] == symbol)
			{
				win = true;
				cout << "Player " << (turn % 2) + 1 << " wins!" << endl;
			}
			else if (board[0][1] == symbol && board[1][1] == symbol && board[2][1] == symbol)
			{
				win = true;
				cout << "Player " << (turn % 2) + 1 << " wins!" << endl;
			}
			else if (board[0][2] == symbol && board[1][2] == symbol && board[2][2] == symbol)
			{
				win = true;
				cout << "Player " << (turn % 2) + 1 << " wins!" << endl;
			}
			else if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
			{
				win = true;
				cout << "Player " << (turn % 2) + 1 << " wins!" << endl;
			}
			else if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
			{
				win = true;
				cout << "Player " << (turn % 2) + 1 << " wins!" << endl;
			}
			else if (turn == 9)//checks if the game is a draw
			{
				cout << "It's a draw!" << endl;//prints a draw message
				break;
			}
		}
	}
	return win;//returns if the game has been won
}

// Fires an arrow upwards from the adventurer's position
void game::fire_arrow_up() {
    int delta_rooms = 0; // Tracks the number of rooms the arrow has traveled

    // Loop to move the arrow up through the rooms
    for (int i = this->adventurer.y; i > 0; i--) {
        // Check if the arrow has traveled more than 4 rooms
        if (delta_rooms > 4) {
            this->move_wumpus(); // Move the Wumpus if the arrow travels beyond 4 rooms
            return; // Exit the function
        } else {
            this->check_hit_wumpus(this->adventurer.x, i); // Check if the arrow hits the Wumpus
        }
        delta_rooms++; // Increment the number of rooms the arrow has traveled
    }

    // Move the Wumpus if the arrow travels less than 4 rooms
    if (delta_rooms < 4) {
        this->move_wumpus();
    }
}


// Fires an arrow downwards from the adventurer's position
void game::fire_arrow_down() {
    int delta_rooms = 0; // Tracks the number of rooms the arrow has traveled

    // Loop to move the arrow down through the rooms
    for (int i = this->adventurer.y; i < this->height; i++) {
        // Check if the arrow has traveled more than 4 rooms
        if (delta_rooms > 4) {
            this->move_wumpus(); // Move the Wumpus if the arrow travels beyond 4 rooms
            return; // Exit the function
        } else {
            this->check_hit_wumpus(this->adventurer.x, i); // Check if the arrow hits the Wumpus
        }
        delta_rooms++; // Increment the number of rooms the arrow has traveled
    }

    // Move the Wumpus if the arrow travels less than 4 rooms
    if (delta_rooms < 4) {
        this->move_wumpus();
    }
}

// Fires an arrow to the left from the adventurer's position
void game::fire_arrow_left() {
    int delta_rooms = 0; // Tracks the number of rooms the arrow has traveled

    // Loop to move the arrow left through the rooms
    for (int i = this->adventurer.x; i > 0; i--) {
        // Check if the arrow has traveled more than 4 rooms
        if (delta_rooms > 4) {
            this->move_wumpus(); // Move the Wumpus if the arrow travels beyond 4 rooms
            return; // Exit the function
        } else {
            this->check_hit_wumpus(i, this->adventurer.y); // Check if the arrow hits the Wumpus
        }
        delta_rooms++; // Increment the number of rooms the arrow has traveled
    }

    // Move the Wumpus if the arrow travels less than 4 rooms
    if (delta_rooms < 4) {
        this->move_wumpus();
    }
}

// Fires an arrow to the right from the adventurer's position
void game::fire_arrow_right() {
    int delta_rooms = 0; // Tracks the number of rooms the arrow has traveled

    // Loop to move the arrow right through the rooms
    for (int i = this->adventurer.x; i < width; i++) {
        // Check if the arrow has traveled more than 4 rooms
        if (delta_rooms > 4) {
            this->move_wumpus(); // Move the Wumpus if the arrow travels beyond 4 rooms
            return; // Exit the function
        } else {
            this->check_hit_wumpus(i, this->adventurer.y); // Check if the arrow hits the Wumpus
        }
        delta_rooms++; // Increment the number of rooms the arrow has traveled
    }

    // Move the Wumpus if the arrow travels less than 4 rooms
    if (delta_rooms < 4) {
        this->move_wumpus();
    }
}


// Fires an arrow in the specified direction and decrements the adventurer's arrow count
void game::fire_arrow(char direction) {
    if (direction == 'a') {
        // Fire arrow up
        this->fire_arrow_up();
    } else if (direction == 'w') {
        // Fire arrow left
        this->fire_arrow_left();
    } else if (direction == 's') {
        // Fire arrow right
        this->fire_arrow_right();
    } else {
        // Fire arrow down
        this->fire_arrow_down();
    }

    // Decrement the adventurer's arrow count
    this->adventurer.arrows--;
}

// Main game loop
void game::play_game() {
    while (!this->check_win() && !this->check_lose()) {
        // Print game board
        this->display_game();

        // Display percepts around adventurer's location
        if ((this->adventurer.x - 1) >= 0) {
            if (this->cave_system.isOccupied(this->adventurer.x - 1, this->adventurer.y, this->adventurer.z) == true) {
                std::cout << this->cave_system.getEvent(this->adventurer.x - 1, this->adventurer.y, this->adventurer.z)->percept() << std::endl;
            }
        }
        if ((this->adventurer.x + 1) < this->adventurer.width) {
            if (this->cave_system.isOccupied(this->adventurer.x + 1, this->adventurer.y, this->adventurer.z) == true) {
                std::cout << this->cave_system.getEvent(this->adventurer.x + 1, this->adventurer.y, this->adventurer.z)->percept() << std::endl;
            }
        }
        if ((this->adventurer.y - 1) >= 0) {
            if (this->cave_system.isOccupied(this->adventurer.x, this->adventurer.y - 1, this->adventurer.z) == true) {
                std::cout << this->cave_system.getEvent(this->adventurer.x, this->adventurer.y - 1, this->adventurer.z)->percept() << std::endl;
            }
        }
        if ((this->adventurer.y + 1) < this->adventurer.height) {
            if (this->cave_system.isOccupied(this->adventurer.x, this->adventurer.y + 1, this->adventurer.z) == true) {
                std::cout << this->cave_system.getEvent(this->adventurer.x, this->adventurer.y + 1, this->adventurer.z)->percept() << std::endl;
            }
        }

        // Get player action
        char action = this->get_player_action();

        // Process action
        if (this->is_direction(action)) {
            // W/A/S/D = move adventurer
            char direction = action;
            this->move(direction);
        } else {
            // F = prompt for arrow fire direction and fire arrow
            char direction = this->get_arrow_fire_direction();
            this->fire_arrow(direction);
        }

        // Check if the adventurer encounters an event
        if (this->cave_system.isOccupied(this->adventurer.x, this->adventurer.y, this->adventurer.z) == true) {
            this->cave_system.getEvent(this->adventurer.x, this->adventurer.y, this->adventurer.z)->encounter(this->adventurer);
            
            // Check if the event should be removed after encounter
            if (this->cave_system.isOccupied(this->adventurer.x, this->adventurer.y, this->adventurer.z) == true) {
                if ((this->adventurer.has_gold &&
                     this->cave_system.getEvent(this->adventurer.x, this->adventurer.y, this->adventurer.z)->getSymbol() == 'G') ||
                    this->cave_system.getEvent(this->adventurer.x, this->adventurer.y, this->adventurer.z)->getSymbol() == 'A') {
                    this->cave_system.removeEvent(this->adventurer.x, this->adventurer.y, this->adventurer.z);
                }
            }

            // If killed by Wumpus, play tic-tac-toe for a chance to survive
            int chance = rand() % 2;
            if (this->adventurer.killed_by_wumpus && chance == 0) {
                if (tic_tac_toe()) {
                    this->adventurer.killed_by_wumpus = false;
                    this->adventurer.killed = false;
                } else {
                    this->adventurer.health--;
                }
            }

            // Handle adventurer's death
            if (this->adventurer.killed) {
                if (this->adventurer.killed_by_wumpus == true) {
                    this->adventurer.killed_by_wumpus = false;
                    this->adventurer.health--;
                    move_wumpus();
                }
                if (this->adventurer.has_gold == true) {
                    this->adventurer.has_gold = false;
                    create_event(new Gold(), rand_range(num_rooms));
                }
                for (int i = 0; i < this->adventurer.arrows; i++) {
                    create_event(new Arrow(), rand_range(num_rooms));
                }
                this->adventurer.arrows = 0;
                this->adventurer.z = 0;
                this->adventurer.x = this->start_x;
                this->adventurer.y = this->start_y;
                this->adventurer.killed = false;
            }
        }
    }
}

