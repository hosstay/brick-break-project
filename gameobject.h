/*
 * gameobject.h
 *
 *  Created on: Apr 7, 2016
 *      Author: Taylor, Hoss, x432z869
 *  Assignment: Project
 */

#ifndef VECTOR_
#define VECTOR_
	#include <vector>
#endif /* VECTOR_ */

//makes passing multidimensional vector 'room' look nicer
#ifndef GRID_
#define GRID_
	typedef std::vector< std::vector<char> > Grid;
#endif /* GRID_ */

struct location {
  int x;
  int y;
};

//abstract GameObject class that is the base class for
//Brick, Ball, Board, and any derived classes from those.
class GameObject
{
  public:
	//constructor & destructor
	GameObject();
	GameObject(int lx, int ly, int w, int h, int v);
	virtual ~GameObject();

	//getters and setters
	location get_loc() const;
	virtual void set_loc(int lx, int ly);
	void set_locX(int lx);
	void set_locY(int ly);
	int get_speed() const;
	void set_speed(int v);
	int get_width() const;
	int get_height() const;

	//virtual refreshing function for board, ball, and brick to overwrite
	//GameObject pure virtual since it should never be created by itself.
	virtual Grid draw(Grid &room) = 0;


  private:
	//used to hold the x and y coordinates of the object
	//(ball loc is its point) (brick loc points to top left corner) (board loc points to its center)
	location loc;

	//these three variables are not constant because in future development they might change via items.
	int speed;
	int width;
	int height;

};
