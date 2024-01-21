#ifndef _PointClass
#define _PointClass
#include "Gotoxy.h"
#include "General.h"

//Class that allows us to create an obj that is a point on the screen with the class gotoxy

class Point 
{
	int x, y;

public:
	Point(int _x = 0, int _y = 0)
		:x(_x), y(_y) {} // Constructor

	void setXY(int _x, int _y) { //set X and Y manually
		x = _x;
		y = _y;
	}

	void addToXY(int _x, int _y)
	{
		x = x + _x;
		y = y+ _y;
	}

	int getX() const {return x;}

	int getY() const {return y;}



	bool operator==(const Point& p2){
		return((x == p2.x) && (y == p2.y));
	}

};


#endif // !_PointClass
