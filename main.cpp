/*
Author: Abdul Raziq
Date: 5/27/2024
Description: This is the main file for the game. It will prompt the user for the width and height of the game board,
 whether they want to play in debug mode, and then construct a game object and play the game.
*/







#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"
using namespace std;
/*
 * Function: get_width
 * Description: Prompts the user for the game board width (# of columns)
 * Returns (int): Valid width supplied by user
 */
int get_width() {
	int width;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid width!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Enter the game board width between 4 and 30: ";
		std::cin >> width;
	} while(width < 4 || width > 30);
	{
		cout<<"Please enter a valid width between 4 and 30: ";
		cin>>width;
	}
	return width;
}

/*
 * Function: get_height
 * Description: Prompts the user for the game board height (# of columns)
 * Returns (int): Valid height supplied by user
 */
int get_height() {
	int height;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid height!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Enter the game board height between 4 and 30: ";
		std::cin >> height;
	} while(height < 4 || height > 30);
	return height;
}
int get_rooms() {
	int height;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid Number of Rooms" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Enter the Number of Rooms between 3 and 20 ";
		std::cin >> height;
	} while(height < 3 || height > 20);
	return height;
}
/*
 * Function: get_debug
 * Description: Prompts the user whether they want to play in debug mode
 * Returns (bool): True if the user wants to play in debug mode. False
 * 		otherwise.
 */
bool get_debug() {
	int debug_input;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "Invalid input!" << std::endl <<
				std::endl;
		}
		first = false;
		std::cout << "Would you like to play in debug mode? (1-yes, 0-no): ";
		std::cin >> debug_input;
	} while(debug_input != 0 && debug_input != 1);
	return debug_input == 1;
}

int main()
{
	// Set the random seed
	srand(time(nullptr));
	
	// Ask user for width and height of game board
	int width = get_width();
	int height = get_height();
	int num_rooms = get_rooms();

	// Ask user whether they want debug mode
	bool debug = get_debug();

	// Construct game object
	game g(width, height, debug, num_rooms);
	

	//Play game
	g.play_game();

	return 0;
}
