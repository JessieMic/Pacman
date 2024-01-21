#include "Board.h"


int Board::min_x = 0;
int Board::max_x = 0;
int Board::min_y = 0;
int Board::max_y = 0;

void Board::updateMinMax(int nmin_x, int nmax_x, int nmin_y, int nmax_y)
{
	Board::min_x = nmin_x;
	Board::max_x = nmax_x;
	Board::min_y = nmin_y;
	Board::max_y = nmax_y;
}

void Board::printBoard()
{
	if (color == false)
	{
		for (int i = 0; i < max_y; i++)
		{
			for (int j = 0; j < max_x; j++)
			{
				if (gameBoard[i][j] != (char)gameObjects::INFO && gameBoard[i][j] != (char)gameObjects::NOTBREAD)
				{

					std::cout << gameBoard[i][j];
				}
				else
					std::cout << " ";
			}
			std::cout << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < max_y; i++)
		{
			for (int j = 0; j < max_x; j++)
			{
				if (gameBoard[i][j] == (char)gameObjects::BREADCRUM)
				{
					SetConsoleTextAttribute(hConsole, (char)colors::DARK_YELLOW);
					std::cout << gameBoard[i][j];
				}
				else if (gameBoard[i][j] != (char)gameObjects::INFO && gameBoard[i][j] != (char)gameObjects::NOTBREAD)
				{
					SetConsoleTextAttribute(hConsole, (char)colors::BLUE);
					std::cout << gameBoard[i][j];
				}
				else
					std::cout << " ";
			}
			std::cout << std::endl;
		}
		
	}
}


char Board::getChar (int x, int y) const
{
	return gameBoard[x][y];
}

void Board::changeChar(int row, int col, char c)
{
	gameBoard[row][col] = c;
}

void Board::cleanBoard()
{
	for (int row = 0; row < max_y; row++)
	{
		for (int col = 0; col < max_x; col++)
			changeChar(row, col, '\0');
	}
}


bool Board::loadLevel(string fileName)
{
	fileName += ".screen";

	ManageFile boardFile;
	boardFile.setFileName(fileName);

	if (!boardFile.openFileForReading())
		return false;

	cleanBoard();
	
	char c;
	int row = 0; //rows
	int col = 0; //col index
	//inFile.get(c);
	boardFile.getChar(c);
	bool firstLine=true;
	int maxCol = (int)boardSettings::COL, maxRow= (int)boardSettings::ROW;
	ghostCounter = 0;
	int numOfPacman = 0;
	int numOfInfo = 0;
	
	while (!boardFile.eof())//(!(inFile.eof())) 
	{
		if (col > (int)boardSettings::COL || row > (int)boardSettings::ROW)
		{
			cout << "\nMAX COL IS " << (int)boardSettings::COL << " MAX ROW IS " << (int)boardSettings::ROW <<endl;
			return false;
		}
		if (c != '\n')
		{
			if(gameBoard[row][col] != (char)gameObjects::NOTBREAD && col < maxCol && row < maxRow)
			{
				gameBoard[row][col] = c;
				if (c == (char)gameObjects::PACMAN)
				{
					pacmanSP.y = row;
					pacmanSP.x = col;
					gameBoard[row][col] = (char)gameObjects::NOTBREAD; //no breadcrumb
					numOfPacman++;
				}
				else if (c == (char)gameObjects::GHOST)
				{
					ghostSP[ghostCounter].y = row;
					ghostSP[ghostCounter].x = col;
					ghostCounter++;
					gameBoard[row][col] = (char)gameObjects::NOTBREAD; //no breadcrumb
				}
				else if (c == (char)gameObjects::INFO)
				{
					addInfoToBoard(col, row); //j = col i = row
					infoSP.y = row;
					infoSP.x = col;
					numOfInfo++;
				}
				// for space / wall / notbread do nothing.
				col++;
			}
			else if (c == (char)gameObjects::INFO)
			{
				infoSP.y = row;
				infoSP.x = col;
				col++;
				numOfInfo++;
			}
			else
				col++;
				
		}
		else if (firstLine) //set the max colom size for all of the board.
		{
			maxCol = strlen(gameBoard[row]);
			firstLine = false;
			col = 0;
			row++;
		}
		else if(c == '\n' && col!=0) //&& col < maxCol)
		{
			while (col < maxCol)
			{
				gameBoard[row][col] = (char)gameObjects::NOTBREAD;
				col++;
			}
			col = 0;
			row++;
		}	
		boardFile.getChar(c);
		//inFile.get(c);
		
	}
	boardFile.closeFile();

	checkThatBoardIsfine(numOfPacman,numOfInfo);
	
	if (error)
		return false;

	maxRow = row;
	maxCol = strlen(gameBoard[0]);
	updateMinMax(0, maxCol, 0, maxRow);
	fillWithBreadcrumbs();
	return true;
}

void Board::checkThatBoardIsfine(int pacman, int info)
{
	int line=0;

	if(pacman != 1)
	{
		gotoxy(5, line);
		cout << "\nTHERE SHOULD BE ONE PACMAN";
		error = true;
		line+=2;
	}
	if(ghostCounter< (int)ghost::minGhost || ghostCounter>(int)ghost::maxGhost)
	{
		gotoxy(5,line);
		cout << "\nTHERE SHOULD BE AT LEAST ONE AND UP TO FOUR GHOSTS";
		error = true;
		line+=2;
	}
	if(info != 1)
	{
		gotoxy(5, line);
		cout << "\nTHERE SHOULD BE ONLY ONE & TO PLACE THE INFO OF THE GAME";
		error = true;
		line+=2;
	}

	if (error)
	{
		gotoxy(5, line);
		cout << "\nPLEASE MAKE SURE THE .SCREEN FILES ARE IN THE CORRECT FORMAT";
		line += 2;
	}
	
}

void Board::addInfoToBoard(int col , int row)
{
	int i, j;
	for (i = row; i < (row + 3) && i < (int)boardSettings::ROW; i++)
	{
		for (j = col; j < (col + 20) && j< (int)boardSettings::COL; j++)
		{
			gameBoard[i][j] = '&';
		}
	}
}

void Board::fillWithBreadcrumbs()
{
	int col, row;
	int count = 0;
	for (row = 0; row < Board::max_y; row++)
	{
		for (col = 0; col < Board::max_x; col++)
		{
			if (gameBoard[row][col] == (char)gameObjects::SPACE)
			{
				gameBoard[row][col] = (char)gameObjects::BREADCRUM;
				count++;
			}
				
		}
	}
	BreadForThisLevel = count;
}
