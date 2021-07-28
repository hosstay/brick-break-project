/*
 * gameobject.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#include "gameobject.h"

GameObject::GameObject(): speed(0), width(0), height(0)
{
	loc.x = 0;
	loc.y = 0;
}

GameObject::GameObject(int lx, int ly, int w, int h, int v): speed(v), width(w), height(h)
{
	loc.x = lx;
	loc.y = ly;
}

GameObject::~GameObject() {}

location GameObject::get_loc() const
{
	return loc;
}

void GameObject::set_loc(int lx, int ly)
{
	loc.x = lx;
	loc.y = ly;
}

void GameObject::set_locX(int lx)
{
	loc.x = lx;
}

void GameObject::set_locY(int ly)
{
	loc.y = ly;
}

int GameObject::get_speed() const
{
	return speed;
}

void GameObject::set_speed(int v)
{
	speed = v;
}

int GameObject::get_width() const
{
	return width;
}

int GameObject::get_height() const
{
	return height;
}
