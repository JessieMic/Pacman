#include "SmartMove.h"

SmartMove::SmartMove(Board* _board)
{
	if (_board != nullptr)
	{
		n = _board->size();
		board = _board;//load board 
		row = _board->max_y;
		col = _board->max_x;
		distanceMap.resize(row, std::vector<int>(col, -1));
	}
}

void SmartMove::BFS(xy currPos)
{
	visited = new bool[n];
	distance = 0;

	for (int i = 0; i < n; i++)
		visited[i] = false;

	visited[xyToInt(currPos)]=true;
	queue.push_back(currPos);
	distanceMap[currPos.y][currPos.x] = 0;

	while (!queue.empty())
	{
		currPos = queue.front();
		queue.pop_front();
		checkAdj(currPos);
	}
}

void SmartMove::checkAdj(xy currPos)//this functions adds the distance on the distance map 
{//in each direction from the current position 
	xy adjPos;
	int visitPoint;

	distance++;

	for (int i = 0; i < (int)smartM::VERTICAL; i++)
	{
		adjPos.y = currPos.y + dirRow[i];
		adjPos.x = currPos.x + dirCol[i];
		
		if (checkValidAdj(adjPos))
		{
			visitPoint = xyToInt(adjPos);

			if (!visited[visitPoint])
			{
				if (board->getChar(adjPos.y, adjPos.x) != (char)gameObjects::WALL)
				{
					distanceMap[adjPos.y][adjPos.x] = distance;
					visited[visitPoint] = true;
					queue.push_back(adjPos);
				}
			}
		}
	}
}

bool SmartMove::checkValidAdj(xy pos)//checks to see if we are not abou tto look in an index that is not on the board
{
	if (pos.x >= 0 && pos.y >= 0)
	{
		if (pos.x < col && pos.y < row) 
			return true;
	}

	return false;
}


