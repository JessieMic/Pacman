#include "Fruit.h"


bool Fruit::deleteOverTime()
{
	if (moveCount == 19)
	{
		return true;
	}
	else
		return false;
}

void Fruit::spawn(Board& b)
{
	bool flag = true;
	int x, y;

	while (flag)
	{
		x = rand() % Board::max_x;
		y = rand() % Board::max_y;

		if (b.getChar(y,x) == (char)gameObjects::SPACE || b.getChar(y,x) == (char)gameObjects::BREADCRUM)
		{
			setPos(x, y);
			flag = false;
		}
	}

	if (saving)
	{
		save->WriteToFile("NF ");
		save->WriteToFile(x); //col
		save->WriteToFile(y); //row
		save->WriteToFile(figure); //the value
	}

}

void Fruit::switchToPrevChar(Board& b)//when fruit dies it makes sure to print what was under it 
{
	if (!printBreadIfBehind(b))
	{
		gotoxy(pos.getX(), pos.getY());
		cout << " ";
	}
}