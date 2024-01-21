#ifndef _Ghost
#define _Ghost
#include "General.h"
#include "MovingFigure.h"
#include "Board.h"
#include <cstdlib>
#include "SmartMove.h"

//Class that handles the ghosts

class Ghost : public MovingFigure
{
	int moveCount = (int)ghost::g_moveC;
	SmartMove* smartM = nullptr;
	
	int dirRow[4] = { (int)dirY::UP,(int)dirY::DOWN,(int)dirY::LEFT,(int)dirY::RIGHT };
	int dirCol[4] = { (int)dirX::UP,(int)dirX::DOWN,(int)dirX::LEFT,(int)dirX::RIGHT };

public:

	
	Ghost(int x , int y, char _figure = (char)gameObjects::GHOST) 
		:MovingFigure(x, y,_figure)
	{
		setColor((char)colors::RED);
	};

	void getSmartMove(SmartMove* sm)
	{
		smartM = sm;
	}


	void step(Board& b) //making a full step
	{
		erase();
		printBreadIfBehind(b);
		pos.addToXY(dirX, dirY);
		draw();
	}

	void pickMovement(char level, Board& b); //calling the right function of movment for the ghost, accurding to the level picked

	int getSmartDir();

	
};

#endif