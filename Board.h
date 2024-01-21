#ifndef _Board
#define _Board
#include "General.h"
#include "Gotoxy.h"
#include "ManageFile.h"

class Board
{
	char gameBoard[(int)boardSettings::ROW][(int)boardSettings::COL];
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	bool color = false;
	xy pacmanSP; //pacman spawn point
	int ghostCounter = 0; 
	xy ghostSP[4]; //ghosts spawn points
	xy infoSP; //lives and score spawn point
	int BreadForThisLevel;
	bool error = false;
public:

	static int min_x;
	static int max_x;
	static int min_y;
	static int max_y;
	//Board();
	void printBoard();
	void updateMinMax(int min_x, int max_x, int min_y, int max_y);
	char getChar (int x, int y)const;
	void changeChar(int x, int y, char c);

	void checkThatBoardIsfine(int pacman,int info);

	void toggleColor()
	{
		color = true;
	}
	bool loadLevel(string fileName);
	void addInfoToBoard(int col, int row);
	void fillWithBreadcrumbs();
	void cleanBoard();
	int getBreadCount()
	{
		return BreadForThisLevel;
	}

	xy getPacmanSP() //maybe split into getX getY ?
	{
		return pacmanSP;
	}
	int getGhostCounter()
	{
		return ghostCounter;
	}
	xy getGhostSP(int ghostNum)
	{
		return ghostSP[ghostNum];
	}
	xy getInfoSP()
	{
		return infoSP;
	}
	int size()
	{
		return max_x * max_y;
	}
};


#endif