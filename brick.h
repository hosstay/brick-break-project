/*
 * brick.h
 *
 *  Created on: Apr 14, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
	#include "gameobject.h"
#endif /* GAMEOBJECT_H_ */

//The bricks at the top of the screen that react to stimulus from the ball
class Brick : public GameObject
{
 public:
	//constructor and destructor
	Brick();
	Brick(const bool e);
	virtual ~Brick();

	//setters and getters
	location get_start_point() const;
	void set_visible(bool b);
	bool get_visible() const;
	const int get_type() const;
	//redefined version of GameObject's set_loc that also sets start_point
	virtual void set_loc(int lx, int ly);

	//draws the brick on the screen based on its parameters
	virtual Grid draw(Grid& room);

	//removes the brick from the screen
	Grid remove_brick(Grid& room);

 private:
	//defines the top left corner of the brick
	location start_point;

	bool visible;
	//type of brick 0 = regular, 1 = explosive
	const int type;
};
