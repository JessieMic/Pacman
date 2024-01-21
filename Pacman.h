#ifndef _Pacman
#define _Pacman
#include "MovingFigure.h"
#include "General.h"
#include "Board.h"

class Pacman : public MovingFigure
{
	Point moveTo;

	

public:
	char moveKeys[5] = { 'w','x','a','d','s' }; // up, down, left, right, STAY
	Pacman(int x= (int)pacman::p_x, int y= (int)pacman::p_y , char _figure = (char)gameObjects::PACMAN)
		:MovingFigure(x, y, _figure) {
		setColor((char)colors::YELLOW);
	};

	bool moveReq(char dir, Board& b, int& SCORE);

	virtual int move(Board& b) override; //virtual overriding the move in movingfigure

	int dirOfKey(char dir); //checks what diraction the user is trying to move and returns the releven key, returns -1 for invalid key
	
	void checkForTunnels(Board& b); //checks if the pacman is trying to move out of board bounds, and teleports him to the other side if possible

};


#endif