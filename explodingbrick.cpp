/*
 * explodingbrick.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#include "explodingbrick.h"

ExplodingBrick::ExplodingBrick(): Brick(1) {}

ExplodingBrick::~ExplodingBrick() {}

Grid ExplodingBrick::draw(Grid& room)
{

	for(int i = 0; i < get_height(); i++)
	{
		for(int j = 0; j < get_width(); j++)
			{
				room[get_loc().y + i].at(get_loc().x + j) = '%';
			}
	}

	return room;
}
