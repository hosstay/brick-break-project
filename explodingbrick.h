/*
 * explodingbrick.h
 *
 *  Created on: Apr 20, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#ifndef BRICK_H_
#define BRICK_H_
	#include "brick.h"
#endif /* BRICK_H_ */

//A version of brick with the special effect of removing all adjacent blocks
class ExplodingBrick : public Brick{
 public:
	//constructor and destructor
	ExplodingBrick();
	virtual ~ExplodingBrick();

	//draws the exploding brick on the screen based on its parameters
	virtual Grid draw(Grid& room);
};

