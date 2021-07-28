/*
 * board.h
 *
 *  Created on: Apr 11, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
	#include "gameobject.h"
#endif /* GAMEOBJECT_ */

class Board : public GameObject
{
 public:
	//constructor and destructor
	Board();
	virtual ~Board();

	//refreshes the boards position on the screen
	virtual Grid draw(Grid& room);

	//moves the board to the right
	void inc_board_loc(Grid& room);

	//moves the board to the left
	void dec_board_loc(Grid& room);

 private:
	//made distinctly different from GameObject's height to eliminate any confusion.
	int distance_from_bottom;

};
