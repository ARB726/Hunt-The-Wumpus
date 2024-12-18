#ifndef GAME_HPP
#define GAME_HPP
using namespace std;
#include <vector>
#include "cave.hpp"
// game interface
class game {
private:
	// TODO declare a 2D vector of Room objects:

	// Suggested member variables:
	int width;				// width of the game grid
	int height;				// height of the game grid
	bool debug;				// debug mode or not
	player adventurer;			// player object
	cave cave_system;				// cave object
	int num_rooms;			// number of rooms in the cave
	int start_x;			// starting x-coordinate of the player
	int start_y;			// starting y-coordinate of the player


	// TODO Feel free to add more member variables if you'd like

public:
	// Suggested functions (there are no required functions here):
	
	/*
	 * Function: Constructor
	 * Description: Constructs game object with a grid matching the given
	 * 		width and height
	 * Parameters:
	 * 		width (int): Width of the grid
	 * 		height (int): Height of the grid
	 * 		debug (bool): Whether or not debug mode should be enabled
	 */
	game(int width, int height, bool debug, int num_rooms);

	/*
	 * Function: display_game
	 * Description: Displays the game grid in the terminal
	 */
	void display_game() const;

	/*
	 * Function: check_win
	 * Description: Determines whether the player has won the game
	 * Returns (bool): True if the player has won, false otherwise
	 */
	bool check_win() const;

	/*
	 * Function: check_lose
	 * Description: Determines whether the player has lost the game
	 * Returns (bool): True if the player has lost, false otherwise
	 */
	bool check_lose() const;

	/*
	 * Function: is_direction
	 * Description: Returns true if the given character is a valid direction
	 * 		character (w/a/s/d) and false otherwise
	 * Parameters:
	 * 		c (char): The character to check
	 * Returns (bool): Boolean indicating whether the character is a valid
	 * 		direction character (w/a/s/d)
	 */
	bool is_direction(char c);

	/*
	 * Function: to_lower
	 * Description: Converts a given character to lowercase. Used to standardize
	 * 		a user's character input.
	 * Parameters:
	 * 		direction (char): Character to convert to lowercase
	 * Returns (char): Character converted to lowercase
	 */
	char to_lower(char direction);

	/*
	 * Function: can_move_in_direction
	 * Description: Determines whether the player can move in the given
	 * 		direction, based on their current location and the size of the
	 * 		grid.
	 * Parameters:
	 * 		direction (char): Direction the player wishes to move in
	 * Returns (bool): True if the player can move in the given direction
	 * 		without moving off the grid. False otherwise.
	 */
	bool can_move_in_direction(char direction);

	/*
	 * Function: is_valid_action
	 * Description: Determines whether the given action is valid.
	 * Parameters:
	 * 		action (char): Action the player wishes to perform.
	 * Returns (bool): True if the requested action is valid. False otherwise.
	 */
	bool is_valid_action(char action);

	/*
	 * Function: print_action_error
	 * Description: Prints a clear error message associated with the user's
	 * 		provided invalid action
	 * Parameters:
	 * 		action (char): Invalid action that the user requested
	 */
	void print_action_error(char action);

	/*
	 * Function: get_player_action
	 * Description: Prompts the player for their action for the turn and
	 * 		returns it as a char (w, a, s, d, or f). If the player enters
	 * 		an invalid action, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid action provided by the player.
	 */
	char get_player_action();

	/*
	 * Function: get_arrow_fire_direction
	 * Description: Prompts the player for the direction they want to fire an
	 * 		arrow (w, a, s, or d) and returns it as a char. If the player enters
	 * 		an invalid direction, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid direction provided by the player.
	 */
	char get_arrow_fire_direction();

	/*
	 * Function: move_up
	 * Description: Moves the player up one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_up();

	/*
	 * Function: move_down
	 * Description: Moves the player down one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_down();

	/*
	 * Function: move_left
	 * Description: Moves the player left one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_left();

	/*
	 * Function: move_right
	 * Description: Moves the player right one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_right();

	/*
	 * Function: move
	 * Description: Moves the player in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to move the player (a for
	 * 			west, s for south, d for east, w for north).
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move(char direction);

	/*
	 * Function: fire_arrow_up
	 * Description: Fires an arrow upward
	 * Post-condition: Arrow is fired upward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_up();

	/*
	 * Function: fire_arrow_down
	 * Description: Fires an arrow downward
	 * Post-condition: Arrow is fired downward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_down();

	/*
	 * Function: fire_arrow_left
	 * Description: Fires an arrow leftward
	 * Post-condition: Arrow is fired leftward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_left();

	/*
	 * Function: fire_arrow_right
	 * Description: Fires an arrow rightward
	 * Post-condition: Arrow is fired rightward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_right();

	/*
	 * Function: fire_arrow
	 * Description: Fires an arrow in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to fire arrow (a for
	 * 			west, s for south, d for east, w for north).
	 * Post-condition: Arrow is fired. Wumpus is killed if hit and moves if
	 * 		missed.
	 */
	void fire_arrow(char direction);

	/*
	 * Function: play_game
	 * Description: Runs one full iteration of the game
	 */
	void play_game();
	/*
	Function: check_position
	Description: check if the player is in the same room as the wumpus
	Parameters:
		x(int): x-coordinate of the player
		y(int): y-coordinate of the player
		z(int): number of rooms
	*/
	void check_position(int& x, int& y,int z);
	/*
	Function: create_event
	Description: create an event in the room
	Parameters:
		event(Event*): event to be created
		z(int): number of rooms
	*/
	void create_event(Event*event,int z);
	/*
	Function: check_hit_wumpus
	Description: check if the player hit the wumpus
	Parameters:
		x(int): x-coordinate of the player
		y(int): y-coordinate of the player
	*/
	void check_hit_wumpus(int x,int y);
	/*
	Function: move_wumpus
	Description: move the wumpus to a random room
	*/

	void move_wumpus();
	/*
	Function: check_hit_bat
	Description: check if the player encouters the wumpus
	Parameters:
		x(int): x-coordinate of the player
		y(int): y-coordinate of the player
	*/
	bool tic_tac_toe();

};
#endif
