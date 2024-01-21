#include "Ghost.h"


void Ghost::pickMovement(char level, Board& b)
{
	int dir;

	if (level == ((char)levels::BEST))//Plays only smart
	{

		dir = getSmartDir();
		changeDirection(dir);

		step(b);

	}
	else if (level == ((char)levels::GOOD))//hald AI half mindless 
	{
		if (Ghost::moveCount < 5)
		{
			dir=move(b); //moving dumb
			moveCount++;

		}
		else if (Ghost::moveCount < 25)
		{
			dir = getSmartDir();
			changeDirection(dir);
			step(b);
			moveCount++;
		}
		else
		{
			moveCount = 0;
			dir=move(b);
		}

	}
	else if (level == ((char)levels::NOVICE))//play with no special AI
	{
		dir= move(b);
		
	}

	if (saving)
	{
		save->WriteToFile("G ");
		save->WriteToFile(enumDir);
	}

}

int Ghost::getSmartDir()//reads distanceMap from SmartM class and pick the shortest path direction for ghost 
{
	xy currPos=getXY();
	int currDis;
	int currentMinDis=Board::max_x*Board::max_y, currMinIndex=0;

	for(int i = 0; i < (int)smartM::VERTICAL; i++)
	{
		if(currPos.y+dirRow[i]>=0 && currPos.x+dirCol[i]>=0 && currPos.y+dirRow[i] < Board::max_y && currPos.x+dirCol[i] < Board::max_x)
		{
			currDis=smartM->getDis(currPos.y+dirRow[i], currPos.x+dirCol[i]);
			if (currDis != -1 && currDis < currentMinDis)
			{
				currentMinDis = currDis;
				currMinIndex = i;
			}
		}
	}

	return currMinIndex;
}
