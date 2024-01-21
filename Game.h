#ifndef _Game
#define _Game

#include "Pacman.h"
#include "General.h"
#include "Ghost.h"
#include "Menu.h"
#include "Board.h"
#include "Fruit.h"
#include "SmartMove.h"
#include "ManageFile.h"

//Class that makes the whole game run
class Game
{
	vector<string> fileNames;
	Pacman* player1=nullptr;
	Ghost* ghosts[4] = {};  //4 points to 'not created yet' ghosts
	int ghostsNum=0; // ghosts in play
	bool color = false;
	int LIVES;
	Fruit* gFruit=nullptr;
	bool isThereFruit = false;
	bool smartGhosts = false;
	SmartMove* smartM=nullptr;
	char level;
	int moveCounter;
	bool playing = true;
	//Menu mainMenu;
	Board gameBoard;
	int SCORE=0;
	int MAXSCORE=0; //ACCORDING TO BREADCRUMBS
	xy infoXY;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	bool saveMode = false;
	bool silentFlag = false;
	ManageFile* stepsFile;
	ManageFile* resultFile;

	
public:
	Game() { scanForFiles(); }
	void levelOfGhost();
	void createFruit();
	bool init();//
	void run();//Runs the whole game 
	void checkForPress(char &key,char &keepLastKey);//Gets a move from player and moves if needed 
	void drawFigures() ;//draws figure of pac ghost 
	void printScore() ;
	void objMovment();
	void flashAnimation();//Everytime pacman gets hit there is a flash animation
	void checkIfEaten(char& key);
	void gameStat();//checks to see if game won/lost
	void colorGame();//switches game to color mode 
	void scanForFiles(); //look for files in working-dir and load into <fileNames>
	void setAllObjects(); //allocate the dynamic objects, and set their XY, color, and the right MAXSCORE
	void deleteEndOfMap();
	void loadMode(bool silent);
	void turnOnSaveMode() { saveMode = true; }
	void toggleManageFile();
	void loadMode_readStep(string& input, int& currGhost, int pacmanTOD[], int& currDeath, bool& testFailedFlag);
	bool loadMode_readResult(bool& FilesError, string& input, int pacmanTOD[], int& numTOD, int& finishTime);
	bool loadMode_endCondition(bool& testFailedFlag, int& i);
	Game(const Game& s) = delete;//cancel copy
	Game& operator=(const Game& s) = delete;
	~Game()
	{
		if (saveMode)
		{
			delete stepsFile;
			delete resultFile;
		}
	}
};

#endif