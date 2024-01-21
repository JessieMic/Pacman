#ifndef _Fruit
#define _Fruit
#include "General.h"
#include "MovingFigure.h"
#include "Board.h"
#include <cstdlib>

//Class that handles the ghosts

class Fruit : public MovingFigure
{
	char figure;
public:

	Fruit(int x=0, int y=0 , char _figure = (char)gameObjects::FRUIT + rand() % 5)
		:MovingFigure(x, y, _figure) {
		setColor((char)colors::GREEN);
		figure = _figure;
	};

	void spawn(Board& b);

	bool deleteOverTime();

	int getBonus()
	{
		int points = figure - '0';
		return points;
	}
	
	virtual int move(Board& b)
	{
		int i=MovingFigure::move(b);
		if (saving)
		{
			save->WriteToFile("F ");
			save->WriteToFile(enumDir);
		}
		return i;
	}

	void switchToPrevChar(Board& b);

};

#endif