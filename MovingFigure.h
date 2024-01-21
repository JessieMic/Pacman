#ifndef _MovingFigure
#define _MovingFigure
#include "Point.h"
#include "Board.h"
#include "ManageFile.h"

//a class for eveything thats moves on the board. used by the pacman and ghost and fruit

class MovingFigure
{
protected:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Point pos;
	char figure;
	int spawnPoint[2]; //save the Default position to start the game
	int dirX = 0, dirY = 0, enumDir=-5;
	bool usingColor = false;
	char color=(char)colors::WHITE;
	int moveCount = 0;
	ManageFile* save=nullptr;
	bool saving = false;
public:
	MovingFigure(int x = 0, int y = 0, char _figure = (char)gameObjects::PACMAN) :pos(x, y), figure(_figure)
	{
		spawnPoint[0] = x;
		spawnPoint[1] = y;
	};
	
	void getSaveObj(ManageFile* s)
	{
		saving = true;
		save = s;
	}

	bool printBreadIfBehind(Board& b);

	void changeDirection(int dir);
	
	virtual int move(Board& b);

	void addDirToPos();

	void setSpawnPoint(int x,int y){ // change spawn point
		spawnPoint[0] = x;
		spawnPoint[1] = y;
	}
	
	void resetPos() { setPos(spawnPoint[0], spawnPoint[1]); } //go back to spawn point

	void setPos(int x, int y)
	{
		pos.setXY(x, y);
	}

	void setColor(char _color) { color = _color; }

	void toggleColor()
	{
		MovingFigure::usingColor = true;// usingColor = 1;
	}

	void draw() //change to darw alone
	{
		
		gotoxy(pos.getX(),pos.getY());
		if (usingColor == true)
			SetConsoleTextAttribute(hConsole, color); // X stands for the color
		cout << figure;
	}


	void erase() //change to darw alone
	{
		gotoxy(pos.getX(), pos.getY());
		cout << (char)gameObjects::SPACE;
	}
	
	Point nextMoveOfFigure(int dir)
	{
		changeDirection(dir); // SET THE REQUSTED DIR
		Point nextMovePoint = pos;
		nextMovePoint.addToXY(dirX, dirY);
		return nextMovePoint;
	}

	Point getPos() { return pos; }

	xy getXY()
	{
		xy coordinate;
		coordinate.x = pos.getX();
		coordinate.y = pos.getY();

		return coordinate;
	}

	

};


#endif