/*
 * board.cpp
 *
 *  Created on: Apr 11, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#include "board.h"

//25 = starting LocX (center), 0 = starting LocY (not used), 8 = width, 1 = height (not used) 1 = starting velocity
Board::Board(): GameObject(25, 0, 8, 1, 6), distance_from_bottom(3) {}

Board::~Board() {}

Grid Board::draw(Grid& room)
{
	//getting height and width
	int height = room.size();
	int width = room[0].size();

	//remove old board location
	for(int i = 0; i < width; i++)
	{
		if(room[height - distance_from_bottom].at(i) == '=')
		{
			room[height - distance_from_bottom].at(i) = ' ';
		}
	}

	//add new board location to grid
	for(int i = 0; i < get_width(); i++)
	{
		room[height - distance_from_bottom].at((get_loc().x - (get_width() / 2)) + i) = '=';
	}

	return room;
}

void Board::inc_board_loc(Grid& room)
{
	int width = room[0].size();

	//make sure board doesn't go out of bounds
	if( (get_loc().x + get_speed()) + (get_width() / 2) < width - 1)
	{
		set_locX((get_loc()).x + get_speed());
	}
	else
	{
		set_locX(((width - 1) - (get_width() / 2)));
	}
}

void Board::dec_board_loc(Grid& room)
{
	//make sure board doesn't go out of bounds
	if( (get_loc().x - get_speed()) - (get_width() / 2) > 1)
	{
		set_locX(get_loc().x - get_speed());
	}
	else
	{
		set_locX(((1) + (get_width() / 2)));
	}
}
