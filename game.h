/*
 * game.h
 *
 *  Created on: Apr 7, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#ifndef VECTOR_
#define VECTOR_
	#include <vector>
#endif /* VECTOR_ */

#ifndef BALL_H_
#define BALL_H_
	#include "ball.h"
#endif /* BALL_H_ */

#ifndef BOARD_H_
#define BOARD_H_
	#include "board.h"
#endif /* BOARD_H_ */

#ifndef BRICK_H_
#define BRICK_H_
	#include "brick.h"
#endif /* BRICK_H_ */

#ifndef EXPLODINGBRICK_H_
#define EXPLODINGBRICK_H_
	#include "explodingbrick.h"
#endif /* EXPLODINGBRICK_H_ */

#ifndef IOSTREAM_
#define IOSTREAM_
	#include <iostream>
#endif /* IOSTREAM_ */

//used in timed input
#ifndef SYS_SELECT_H_
#define SYS_SELECT_H_
	#include <sys/select.h>
#endif /* SYS_SELECT_H_ */

//time
#ifndef CTIME_
#define CTIME_
	#include <ctime>
#endif /* CTIME_ */

//perror
#ifndef CSTDIO_
#define CSTDIO_
	#include <cstdio>
#endif /* CSTDIO_ */

//makes passing multidimensional vector 'room' look nicer
#ifndef GRID_
#define GRID_
	typedef std::vector< std::vector<char> > Grid;
#endif /* GRID_ */

//Main class of the program which uses all the other classes to make the game run. The user only
//needs to create the game object and then call play game.
class Game
{
 public:
	//constructor and destructor
	Game();
	virtual ~Game();

	//getter
	int get_width() const;

	//plays game: refreshes the board every second with the ball moving in its current direction. When the ball hits
	//			  a surface it rebounds in the expected direction. If the user enters j or l the board will move right
	//            or left, but never out of bounds. If the user enters q the game will quit. If a brick is hit it will
	//            be removed and if it is explosive it will remove the adjacent bricks with it. If the ball hits the
	//            bottom of the screen the player loses. If all the bricks are removed the player wins.
	int play_game();

 private:
	//private functions only used within game
	//outputs the current 'room' on the screen;
	void draw_screen();

	//gets new positions from different game objects and checks if a brick has been hit or not and completes the necessary actions
	void refresh_screen();

	//based on users input, moves the board either to the left or right on the screen.
	void move_board(char ch);

	//prompts user for input that should be executed within 1 second. This is used so that cin does not infinitely wait for input,
	//stopping the entire program. Instead it waits for 1 second and if input is given it will act on it, and if input is not
	//given then it will output a ' ' char which does nothing.
	//!!!!This will not work on windows!!!!
	//source:
	//stackoverflow.com/questions/18552029/how-to-make-reading-from-stdcin-timeout-after-a-particular-amount-of-time
	char get_input() const;

	//checks the area controlled by each brick to see if the hit location that the ball flagged is within its domain. If it is
	//then it removes the brick (if it is an explosive brick it destroyed the ones adjacent as well).
	void process_bricks(location hit);

	//checks each brick for visibility, and if all are invisible the player has won.
	bool check_for_win();

	//variables
	//holds the 'screen' in multidimensional vector
	Grid room;

	//holds the objects of the game for refresh. Only holds ball and board for now, but at
	//a later date an object for items that drop from bricks could be added as well as other
	//such functionality and could be pushed onto this list in the constructor and then the
	//draw function would need no change. Brick isn't in here because it only needs to be
	//drawn once when it's created.
	std::vector<GameObject*> object_list;

	//board, ball, and brick pointers to objects ( dynamically allocated objects set in constructor )
	Board *board;
	Ball *ball;
	//receives both regular brick objects and exploding brick objects and does actions
	//on all of them in loops via polymorphism
	std::vector<Brick*> bricks;

	//width and height of playable area, 'room' area.
	const int height;
	const int width;
	//number and layout of bricks on the screen
	const int num_of_bricks;
	const int rows_of_bricks;
	const int columns_of_bricks;
};

