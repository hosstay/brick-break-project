/*
 * main.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 *  Description: This is a Brick Break-like ASCII game. The board is represented by ='s at the bottom
 *  			 of the screen and the user can move it by hitting j or l on the keyboard and then
 *  			 hitting enter. The @ symbol is a ball that moves in a direction on the screen and
 *  			 bounces off the various surfaces. If the ball touches a brick(#) it will disappear.
 *  			 exploding bricks(%) will also remove its adjacent bricks. When the ball hits a
 *  			 surface it bounces in the expected direction. Depending on where it hits the board
 *  			 it may fly back the way it came or continue onwards, this gives the user a little
 *  			 control of where the ball goes. The object of the game is to destroy all the bricks.
 *  			 If the ball hits the floor the player loses. The user can hit q and then enter at
 *  			 any time to quit the game. To get the game to look right in the console window in
 *  			 eclipse it is best if you have it clipped to the bottom of the eclipse screen and
 *  			 resize the console window until the whole box fits in vertically, with about two
 *  			 lines of extra room at the bottom for the input and when it newlines after the enter
 *  			 key. This eliminates a lot of jittering. The game class utilizes polymorphism in a
 *  			 few places and is moderately flexible to adding new types of bricks, or in the future
 *  			 even adding items or some other functionality.
 *
 *  Sources: I used a function that times out a cin statement if it passes a certain amount of time.
 *  		 I found this function on the website stackoverflow and was posted by user Jeremy Friesner.
 *  		 The post is public domain. The function, which is implemented inside game.cpp, also
 *  		 has this information. This function does not work on windows. Link to the post in question:
 *  		 stackoverflow.com/questions/18552029/how-to-make-reading-from-stdcin-timeout-after-a-particular-amount-of-time
 */

#ifndef GAME_H_
#define GAME_H_
	#include "game.h"
#endif /* GAME_H_ */

int main(void)
{
	//game objects and general playing functions are completely encapsulated in game
	//interface. User only needs to create game and run it.
	Game game;

	return game.play_game();
}
