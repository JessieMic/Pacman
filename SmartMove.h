#ifndef _SmartMove
#define _SmartMove

#include "General.h"
#include "Board.h"

//This class allows ghost to be smart and search the shortest path to pacman
//It uses the concept of BFS as follows:
//Each run of BFS we update the distanceMap that is in the size of the board game.
//distanceMap has the distance from pacman to each point that he can go to on the board
//The main idea is that the ghost will read that map and go to the path that has the shortest distance.

class SmartMove
{
	Board* board=nullptr;
	int row;//y
	int col;//x
	std::vector<std::vector<int>> distanceMap;
	bool* visited=nullptr;
;
	std::list<xy> queue;
	int distance;
	int n;//The number of nodes


	int dirRow[4] = { (int)dirY::UP,(int)dirY::DOWN,(int)dirY::LEFT,(int)dirY::RIGHT };
	int dirCol[4] = { (int)dirX::UP,(int)dirX::DOWN,(int)dirX::LEFT,(int)dirX::RIGHT };


public:
	SmartMove(Board* _board);

	void BFS(xy currPos);

	int xyToInt(xy pos)
	{
		return col * pos.y + pos.x;
	}

	void checkAdj(xy currPos);

	bool checkValidAdj(xy pos);

	int getDis(int y,int x)
	{
		return distanceMap[y][x];
	}

	SmartMove(const SmartMove& s) = delete;//cancel copy
	SmartMove& operator=(const SmartMove& s) = delete;

	~SmartMove() { delete[] visited; }
};


#endif