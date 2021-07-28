/*
 * brick.cpp
 *
 *  Created on: Apr 14, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#include "brick.h"

//0 = starting posX (reset), 0 = starting posY (reset), 8 = width, 2 = height, 0 = velocity (not used)
Brick::Brick(): GameObject(0, 0, 8, 2, 0), visible(false), type(0)
{
	start_point.x = 0;
	start_point.y = 0;
}

Brick::Brick(const bool e): GameObject(0, 0, 8, 2, 0), visible(false), type(e)
{
	start_point.x = 0;
	start_point.y = 0;
}

Brick::~Brick() {}

void Brick::set_loc(int lx, int ly)
{
	GameObject::set_loc(lx, ly);
	start_point.x = lx;
	start_point.y = ly;
}

location Brick::get_start_point() const
{
	return start_point;
}

void Brick::set_visible(bool b)
{
	visible = b;
}

bool Brick::get_visible() const
{
	return visible;
}

const int Brick::get_type() const
{
	return type;
}

Grid Brick::draw(Grid& room)
{

	for(int i = 0; i < get_height(); i++)
	{
		for(int j = 0; j < get_width(); j++)
			{
				room[get_loc().y + i].at(get_loc().x + j) = '#';
			}
	}

	return room;
}

Grid Brick::remove_brick(Grid& room)
{
	for(int i = 0; i < get_height(); i++)
	{
		for(int j = 0; j < get_width(); j++)
			{
				if(room[get_loc().y + i].at(get_loc().x + j) != '@')
				{
					room[get_loc().y + i].at(get_loc().x + j) = ' ';
				}
			}
	}
	return room;
}

