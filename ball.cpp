/*
 * ball.cpp
 *
 *  Created on: Apr 13, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#include "ball.h"

//25 = starting LocX (center), 15 = starting LocY, 1 = width (not used), 1 = height (not used), 1 = starting velocity
Ball::Ball() : GameObject(25, 15, 1, 1, 1), dir(NE)
{
	hit.x = -1;
	hit.y = -1;
}

Ball::~Ball() {}

location Ball::get_hit()
{
	return hit;
}

Grid Ball::draw(Grid& room)
{

	//remove old ball location
	room[get_loc().y].at(get_loc().x) = ' ';

	//move ball with current speed and direction
	move_ball(room);

	//add new ball location to grid
	room[get_loc().y].at(get_loc().x) = '@';

	return room;
}

void Ball::move_ball(Grid& room)
{
	//resetting hit location
	hit.y = -1;
	hit.x = -1;

	//heavily reduces function calls
	int locY = get_loc().y;
	int locX = get_loc().x;
	int speed = get_speed();

	//used in getting position of board ball hits
	int lcount;
	int rcount;

	if(dir == N)
	{
		//if it collides with something
		if( room[locY - speed].at(locX) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY - speed].at(locX) == '#' || room[locY - speed].at(locX) == '%')
			{
				hit.y = locY - speed;
				hit.x = locX;
			}
			dir = S;
			set_locY(locY + speed);
		}else
			set_locY(locY - speed);
	}

	if(dir == NE)
	{
		//if it collides with something on the Y axis
		if( room[locY - speed].at(locX) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY - speed].at(locX) == '#' || room[locY - speed].at(locX) == '%')
			{
				hit.y = locY - speed;
				hit.x = locX;
			}
			dir = SE;
			set_locY(locY + speed);
			set_locX(locX + speed);
		}
		//if it collides with something on the X axis
		else if( room[locY].at(locX + speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY].at(locX + speed) == '#' || room[locY].at(locX + speed) == '%')
			{
				hit.y = locY;
				hit.x = locX + speed;
			}
			dir = NW;
			set_locY(locY - speed);
			set_locX(locX - speed);
		//if it collides with something on the X/Y axis
		}else if( room[locY - speed].at(locX + speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY - speed].at(locX + speed) == '#' || room[locY - speed].at(locX + speed) == '%')
			{
				hit.y = locY - speed;
				hit.x = locX + speed;
			}
			dir = SW;
			set_locY(locY + speed);
			set_locX(locX - speed);
		}else
		{
			set_locY(locY - speed);
			set_locX(locX + speed);
		}
	}

	if(dir == E)
	{
		//if it collides with something
		if( room[locY].at(locX + speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY].at(locX + speed) == '#' || room[locY].at(locX + speed) == '%')
			{
				hit.y = locY;
				hit.x = locX + speed;
			}

			//change direction to NW or it will never change course
			dir = NW;
			set_locY(locY - speed);
			set_locX(locX - speed);
		}else
			set_locX(locX + speed);
	}

	if(dir == SE)
	{
		//if it collides with something on the Y axis
		if( room[locY + speed].at(locX) != ' ' )
		{
			//if it collides with the board on the Y axis
			if( room[locY + speed].at(locX) == '=' )
			{
				//count how many ='s are to the left and right to decide the new ball direction
				lcount = left_count();
				rcount = right_count();

				//if it collides with the left side of the board
				if(lcount <= 3)
				{
					dir = NE; //why?
					set_locY(locY - speed);
					set_locX(locX + speed);
				}
				//if it collides with the right side of the board
				else if(rcount <= 3)
				{
					//if it collides with the wall to the right as well (eliminates ball flying through wall and out of bounds)
					if( room[locY].at(locX + speed) != ' ' )
					{
						dir = NW;
						set_locY(locY - speed);
						set_locX(locX - speed);
					}
					dir = NE;
					set_locY(locY - speed);
					set_locX(locX + speed);
				}
				//if it collides with the middle of the board
				else
				{
					dir = NE;
					set_locY(locY - speed);
					set_locX(locX + speed);
				}
			//if it collides with the floor
			}else if( room[locY + speed].at(locX) == '-' )
			{
					hit.x = -100;
			}else
			{
				//if it collides with a brick, return position hit
				if( room[locY + speed].at(locX) == '#' || room[locY + speed].at(locX) == '%')
				{
					hit.y = locY + speed;
					hit.x = locX;
				}
				dir = NE;
				set_locY(locY - speed);
				set_locX(locX + speed);
			}
		}
		//if it collides with something on the X axis
		else if( room[locY].at(locX + speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY].at(locX + speed) == '#' || room[locY].at(locX + speed) == '%')
			{
				hit.y = locY;
				hit.x = locX + speed;
			}
			dir = SW;
			set_locY(locY + speed);
			set_locX(locX - speed);
		}
		//if it collides with something on the X/Y plane (CAN ONLY BE BOARD ON LEFT SIDE)
		else if( room[locY + speed].at(locX + speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY + speed].at(locX + speed) == '#' || room[locY + speed].at(locX + speed) == '%')
			{
				hit.y = locY + speed;
				hit.x = locX + speed;
			}
			dir = NW;
			set_locY(locY - speed);
			set_locX(locX - speed);
		}else
		{
			set_locY(locY + speed);
			set_locX(locX + speed);
		}
	}

	if(dir == S)
	{
		//if it collides with something
		if( room[locY + speed].at(locX) != ' ' )
		{
			//if it collides with the board
			if( room[locY + speed].at(locX) == '=' )
			{
				//count how many ='s are to the left and right to decide the new ball direction
				lcount = left_count();
				rcount = right_count();

				//if it collides with the left side of the board
				if(lcount <= 3)
				{
					dir = NW;
					set_locY(locY - speed);
					set_locX(locX - speed);
				}
				//if it collides with the right side of the board
				else if(rcount <= 3)
				{
					dir = NE;
					set_locY(locY - speed);
					set_locX(locX + speed);
				}
				//if it collides with the middle of the board
				else
				{
					dir = N;
					set_locY(locY - speed);
				}
			//if it collides with the floor
			}else if ( room[locY + speed].at(locX) == '-' )
			{
				hit.x = -100;
			}else
			{
				//if it collides with a brick, return position hit
				if( room[locY + speed].at(locX) == '#' || room[locY + speed].at(locX) == '%')
				{
					hit.y = locY + speed;
					hit.x = locX;
				}
				dir = N;
				set_locY(locY - speed);
			}
		}else
			set_locY(locY + speed);
	}

	if(dir == SW)
	{
		//if it collides with something on the Y axis
		if( room[locY + speed].at(locX) != ' ' )
		{
			//if it collides with the board on the Y axis
			if( room[locY + speed].at(locX) == '=' )
			{
				//count how many ='s are to the left and right to decide the new ball direction
				lcount = left_count();
				rcount = right_count();

				//if it collides with the left side of the board
				if(lcount <= 3)
				{
					//if it collides with the wall to the left as well (eliminates ball flying through wall and out of bounds)
					if( room[locY].at(locX - speed) != ' ' )
					{
						dir = NE;
						set_locY(locY - speed);
						set_locX(locX + speed);
					}
					dir = NW;
					set_locY(locY - speed);
					set_locX(locX - speed);
				}
				//if it collides with the right side of the board
				else if(rcount <= 3)
				{
					dir = NW; //why?
					set_locY(locY - speed);
					set_locX(locX - speed);
				}
				//if it collides with the middle of the board
				else
				{
					dir = NW;
					set_locY(locY - speed);
					set_locX(locX - speed);
				}
			//if it collides with the floor
			}else if ( room[locY + speed].at(locX) == '-')
			{
				hit.x = -100;
			}else
			{
				//if it collides with a brick, return position hit
				if( room[locY + speed].at(locX) == '#' || room[locY + speed].at(locX) == '%')
				{
					hit.y = locY + speed;
					hit.x = locX;
				}
				dir = NW;
				set_locY(locY - speed);
				set_locX(locX - speed);
			}
		}
		//if it collides with something on the X axis
		else if( room[locY].at(locX - speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY].at(locX - speed) == '#' || room[locY].at(locX - speed) == '%')
			{
				hit.y = locY;
				hit.x = locX - speed;
			}
			dir = SE;
			set_locY(locY + speed);
			set_locX(locX + speed);
		}
		//if it collides with something on the X/Y plane ..
		else if( room[locY + speed].at(locX - speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY + speed].at(locX - speed) == '#' || room[locY + speed].at(locX - speed) == '%')
			{
				hit.y = locY + speed;
				hit.x = locX - speed;
			}

			dir = NE;
			set_locY(locY - speed);
			set_locX(locX + speed);
		}else
		{
			set_locY(locY + speed);
			set_locX(locX - speed);
		}
	}

	if(dir == W)
	{
		//if it collides with something
		if( room[locY].at(locX - speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY].at(locX - speed) == '#' || room[locY].at(locX - speed) == '%')
			{
				hit.y = locY;
				hit.x = locX - speed;
			}
			//change direction to NE or it will never change coarse
			dir = NE;
			set_locY(locY - speed);
			set_locX(locX + speed);
		}else
			set_locX(locX - speed);
	}

	if(dir == NW)
	{
		//if it collides with something on the Y axis
		if( room[locY - speed].at(locX) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY - speed].at(locX) == '#' || room[locY - speed].at(locX) == '%')
			{
				hit.y = locY - speed;
				hit.x = locX;
			}
			dir = SW;
			set_locY(locY + speed);
			set_locX(locX - speed);
		}
		//if it collides with something on the X axis
		else if( room[locY].at(locX - speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY].at(locX - speed) == '#' || room[locY].at(locX - speed) == '%')
			{
				hit.y = locY;
				hit.x = locX - speed;
			}
			dir = NE;
			set_locY(locY - speed);
			set_locX(locX + speed);
		//if it collides with something on the X/Y axis
		}else if( room[locY - speed].at(locX - speed) != ' ' )
		{
			//if it collides with a brick, return position hit
			if( room[locY - speed].at(locX - speed) == '#' || room[locY - speed].at(locX - speed) == '%')
			{
				hit.y = locY - speed;
				hit.x = locX - speed;
			}
			dir = SE;
			set_locY(locY + speed);
			set_locX(locX + speed);
		}else
		{
			set_locY(locY - speed);
			set_locX(locX - speed);
		}
	}
}

int Ball::left_count() const
{
	int current = get_loc().x;
	int left_count = 0;

	//see how long the board to the left is.
	while(current == '=')
	{
		left_count++;
		current--;
	}

	return left_count;

}

int Ball::right_count() const
{
	int current = get_loc().x;
	int right_count = 0;

	//see how long the board to the right is.
	while(current == '=')
	{
		right_count++;
		current++;
	}

	return right_count;

}
