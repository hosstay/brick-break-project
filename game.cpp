/*
 * game.cpp
 *
 *  Created on: Apr 7, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#include "game.h"

//changing height/width here requires changing the starting values in constructors of GameObjects or
//they won't be centered. Also will need to reallocate bricks as they are hard placed based on these values.
Game::Game(): height(20), width(50), num_of_bricks(24), rows_of_bricks(4), columns_of_bricks(6)
{
	//resize multidimensional char vector to h:20 and w:50 to hold the "screen"
	room.resize(height, std::vector<char>(width));

	//fill space with empty strings
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			room[i].at(j) = ' ';
		}
	}

	//fill top row with border
	for (int i = 0; i < width; i++){room[0].at(i) = '-';}

	//fill bottom row with border
	for (int i = 0; i < width; i++){room[height - 1].at(i) = '-';}

	//fill left most row with border
	for (int i = 1; i < height - 1; i++){room[i].at(0) = '|';}

	//fill right most row with border
	for (int i = 1; i < height - 1; i++){room[i].at(width - 1) = '|';}

	//dynamically allocate game objects
	board = new Board;
	ball = new Ball;

	for( int i = 0; i < num_of_bricks; i++)
	{
		//set bricks 3, 6, 7, 11, 14, and 16 to explosive
		if( i == 2 || i == 5 || i == 6 || i == 10 || i == 13 || i == 15 )
		{
			bricks.push_back(new ExplodingBrick);
		//and the rest to regular bricks
		}else
			bricks.push_back(new Brick);
	}

	//put the board on the screen
	room = board->draw(room);

	//put moving objects onto the object list for redrawing
	object_list.push_back(board);
	object_list.push_back(ball);

	//set the dimensions for each brick
	const int br_width = bricks.at(1)->get_width();
	const int br_height = bricks.at(1)->get_height();

	//Rows and columns were decided by what looked pretty in the room that had been made.
	//Any alteration to the size of the room will need different values
	for( int i = 0; i < rows_of_bricks; i++)
	{
		for( int j = 0; j < columns_of_bricks; j++)
		{
			//for every brick polymorphically set their location
			bricks.at((columns_of_bricks * i) + j)->set_loc(1 + (br_width * j), 1 + (br_height * i));
		}
	}

	//for every brick polymorphically draw them and set them to visible
	for( int i = 0; i < num_of_bricks; i++)
	{
		room = bricks.at(i)->draw(room);
		bricks.at(i)->set_visible(true);
	}
}

Game::~Game()
{
	//delete dynamically allocated game objects
	delete board;
	delete ball;

	for( int i = 0; i < num_of_bricks; i++)
	{
		delete bricks.at(i);
	}
}

int Game::get_width() const
{
	return width;
}

void Game::draw_screen()
{
	//output 'room' by cycling through every point in the vector and outputting it.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout<<room[i].at(j);
		}
		std::cout<<"\n";
	}
}

void Game::refresh_screen()
{
	//polymorphically draw game objects to the screen. as more game objects that need refreshing every second
	//are added, such as items dropping from bricks, this will prove useful to draw them all.
	for( int i = 0; i < 2; i++)
	{
		object_list.at(i)->draw(room);
	}

	//see if a brick has been hit or not.
	process_bricks(ball->get_hit());
}

void Game::move_board(char ch)
{
	//move board right
	if( ch == 'l')
	{board->inc_board_loc(room);}

	//move board left
	if( ch == 'j')
	{board->dec_board_loc(room);}
}

char Game::get_input() const
{
	char ch;

	//cin operation should be executed within stipulated period of time
	//This would not work on windows.
	//source:
	//stackoverflow.com/questions/18552029/how-to-make-reading-from-stdcin-timeout-after-a-particular-amount-of-time
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(0, &readSet);
	struct timeval tv = {1, 0};  // 1 second(s), 0 microseconds;
	if (select(0+1, &readSet, NULL, NULL, &tv) < 0) perror("select");

	bool b = (FD_ISSET(0, &readSet)) ? !!(std::cin>>ch) : false;

	//input is char for ch, thus return good value
	if(b==1)
		return ch;

	//Either ch is not integer or no input for ch, thus return empty char
	else
		return ' ';
}

void Game::process_bricks(location hit)
{
	//current position to check for hit
	int currentx;
	int currenty;

	//standard height and width of a brick
	int b_height = bricks.at(0)->get_height();
	int b_width = bricks.at(0)->get_width();

	//rotate through each brick
	for( int k = 0; k < num_of_bricks; k++)
	{
		//set the current position to the top left of this brick
		currentx = bricks.at(k)->get_start_point().x;
		currenty = bricks.at(k)->get_start_point().y;

		//rotate through the columns and rows of the brick and check for a hit
		for( int i = 0; i < b_height; i++)
		{
			for( int j = 0; j < b_width; j++)
			{
				//if hit location is within area of brick, remove that brick from the screen.
				if( currentx + j == hit.x && currenty + i == hit.y)
				{
					//if brick is explosive remove the bricks on all sides of it
					if( bricks.at(k)->get_type() == 1 )
					{
						if((k - columns_of_bricks) > 0)
						{
							room = bricks.at(k - columns_of_bricks)->remove_brick(room);
						}
						if((k + columns_of_bricks) < num_of_bricks)
						{
							room = bricks.at(k + columns_of_bricks)->remove_brick(room);
						}
						if((k - 1) > 0)
						{
							room = bricks.at(k - 1)->remove_brick(room);
						}
						if((k + 1) < num_of_bricks)
						{
							room = bricks.at(k + 1)->remove_brick(room);
						}
						room = bricks.at(k)->remove_brick(room);
					//otherwise just remove brick
					}else
						room = bricks.at(k)->remove_brick(room);

				}
			}
		}
	}
}

bool Game::check_for_win()
{
	bool flag = false;

	//checks each brick for visibility
	for( int i = 0; i < num_of_bricks; i++)
	{
		flag = bricks.at(i)->get_visible();

		//if even a single brick is visible player has not won so exit for loop.
		if(flag){i = num_of_bricks;}
	}

	return !flag;
}

int Game::play_game()
{
	//user input
	char ch;

	//used for keeping time
	time_t start, end;

	//grabs the game object locations for the first time
	refresh_screen();

	//draw the screen
	draw_screen();

	//main loop
	do{

		//get input from user and make sure nothing happens until a second has passed.
		time (&start);
		ch = get_input();
		time (&end);
		while(difftime(end, start) < 1)
		{
			//keep refreshing end time until a second has passed.
			time (&end);
		}

		//if the user entered j or l then move left or right respectively
		move_board(ch);

		//clear cin buffer (try and reduce double moving from multiple inputs)
		std::cin.clear();

		//refresh screen
		refresh_screen();

		//clear screen (barbaric, but worked better for my purposes than anything else I found)
		std::cout << std::string( 100, '\n' );

		//redraw the screen
		draw_screen();

		//if the ball hits the ground the player loses
		if(ball->get_hit().x == -100)
		{
			std::cout<<"YOU LOSE";
			return 0;
		}

		//if all bricks are gone the player wins
		if(check_for_win())
		{
			std::cout<<"YOU WIN";
			return 0;
		}

	//quit if player enters q
	}while(ch != 'q');

	std::cout<<"YOU QUIT";

	return 0;
}
