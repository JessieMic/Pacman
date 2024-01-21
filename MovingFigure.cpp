#include "MovingFigure.h"


void MovingFigure::changeDirection(int dir)
{
	enumDir = dir;
	switch (dir)
	{
	case (int)(direction::UP): // UP
		dirX = (int)dirX::UP;
		dirY = (int)dirY::UP;
		break;
	case (int)(direction::DOWN) : // DOWN
		dirX =(int)dirX::DOWN;
		dirY =(int)dirY::DOWN;
		break;
	case (int)(direction::LEFT) : // LEFT
		dirX = (int)dirX::LEFT;
		dirY = (int)dirY::LEFT;
		break;
	case (int)(direction::RIGHT) : // RIGHT
		dirX = (int)dirX::RIGHT;
		dirY = (int)dirY::RIGHT;
		break;
	case (int)(direction::DONT_CHANGE) : //Dont touch the diraction
		break;
	default: //case of wrong input and also the STAY option
		dirX = 0;
		dirY = 0;
		enumDir = -1;
	}

}


bool MovingFigure::printBreadIfBehind(Board& b)
{
	Point currPos = getPos();
	char c = b.getChar(currPos.getY(), currPos.getX());
	if (c == (char)gameObjects::BREADCRUM) //print breadcrum if we hid it
	{
		gotoxy(currPos.getX(), currPos.getY());

		if (MovingFigure::usingColor)//color breadcrumb
			SetConsoleTextAttribute(hConsole, (char)colors::DARK_YELLOW);
		cout << (char)gameObjects::BREADCRUM;
		return true;
	}
	return false;
}

// returns the DIR
int MovingFigure::move(Board& b)
{
	erase();
	printBreadIfBehind(b);
	char c;
	bool legitMove = false;
	int dir;


	if (moveCount % (int)ghost::g_moveC == 0) //random a diracton
	{
		dir = rand() % 4;
		moveCount = 1;
	}
	else //continue moving same dir
	{
		dir = -1;
		moveCount++;
	}

	while (!legitMove)
	{
		Point moveTo = nextMoveOfFigure(dir);
		c = b.getChar(moveTo.getY(), moveTo.getX());
		if ((c != (char)gameObjects::SPACE) && (c != (char)gameObjects::BREADCRUM) && (c != (char)gameObjects::NOTBREAD))
		{
			dir = rand() % 4;
		}
		else
		{
			pos.addToXY(dirX, dirY); //moving our point

			draw();
			legitMove = true;

			return dir;
		}
	}

	
}

void MovingFigure::addDirToPos()
{
	pos.addToXY(dirX, dirY);
}
