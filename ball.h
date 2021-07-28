/*
 * ball.h
 *
 *  Created on: Apr 13, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */


#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
	#include "gameobject.h"
#endif /* GAMEOBJECT_ */

//used to keep track of ball's direction
enum direction { N, NE, E, SE, S, SW, W, NW };

//the ball that travels around the screen and reacts to different surfaces.
class Ball : public GameObject
{
 public:
	//constructor and destructor
	Ball();
	virtual ~Ball();

	//setters and getters
	location get_hit();

	//refreshes the balls position on the screen
	Grid draw(Grid& room);

 private:
	//private functions only used in ball
	//moves the ball using its current speed and direction.
	//this is a very large function that takes care of every possibility in its direction and surface it's hitting.
	void move_ball(Grid& room);

	//counting functions for choosing new direction based on where the ball hit the board.
	int left_count() const;
	int right_count() const;

	//direction of ball
	direction dir;

	//location that the ball hit a brick, if it did or to signal that the ball hit the bottom of the screen.
	location hit;

};
