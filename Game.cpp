#include "Game.h"

bool Game::init()//char* FileName)
{
	char key;
	LIVES = 3;
	SCORE = 0;

	Menu mainMenu;

	key = mainMenu.options();

	if (key == (char)keys::EXIT)
	{
		return false;
	}
		
	else if (key == (char)keys::PLAY_C)
	{
		color = true;
	}
	 
	if (key != (char)keys::EXIT && fileNames.size()>0)
	{
		if (saveMode)
		{
			stepsFile = new ManageFile;
			resultFile = new ManageFile;
		}


		// pick difficulty
		level = mainMenu.pickLevel();
		
		/// load the board
		key = mainMenu.howToPlay(); // asks if to play ABC order or to load level
		if (key != (char)keys::LOAD_BOARD) //if not loadboard, then we want to play by order of boards
		{
				
			int i;
			for (i = 0; i < fileNames.size(); i++)
			{
				if(!gameBoard.loadLevel(fileNames[i]))
				{
					return false;
				}

				if (saveMode) //open files for writing
				{
					stepsFile->setFileName(fileNames[i]+".steps");
					stepsFile->openFileForWriting();
					resultFile->setFileName(fileNames[i] + ".result");
					resultFile->openFileForWriting();
				}
				setAllObjects();
				run();
				clrscr();

				if (saveMode) //close files
				{
					stepsFile->closeFile();
					resultFile->closeFile();
				}

				if (LIVES < 1)
					break;
			}
			if (i == fileNames.size() && LIVES >=1)
			{
				gotoxy(15, 5);
				cout << "******      YOU WON THE GAME      ******";
				gotoxy(15, 6);
				cout << "******  PRESS ANY KEY TO GO BACK  ******";
				_getch();
				color = false;
			}	
		}
			
		else // choose spesific board
		{
			key = mainMenu.pickBoard(fileNames) - '0'; //beacuse it returns a char and we want int
			if (!gameBoard.loadLevel(fileNames[key]))
				return false;
			if (saveMode) //open files for writing
			{
				stepsFile->setFileName(fileNames[key] + ".steps");
				stepsFile->openFileForWriting();
				resultFile->setFileName(fileNames[key] + ".result");
				resultFile->openFileForWriting();
			}
			setAllObjects();
			run();
			color = false;
			if (saveMode) //open files for writing
			{
				stepsFile->closeFile();
				resultFile->closeFile();
			}
		}
	}
	else
	{
		clrscr();
		cout << "ERROR: NO BOARD FILES DETECTED." << endl << "PLEASE PUT BOARDS FILES WITH .screen AT WORKING DIR"<<endl;
		cout << "Press any key to quit.";
		_getch();
		return false;
	}
	return true;
}

void  Game::setAllObjects()
{
	player1 = new Pacman(gameBoard.getPacmanSP().x, gameBoard.getPacmanSP().y);
	
	ghostsNum = gameBoard.getGhostCounter();

	for (int i = 0; i < ghostsNum; i++) //creates the ghosts
	{
		ghosts[i] = new Ghost(gameBoard.getGhostSP(i).x, gameBoard.getGhostSP(i).y);
	}

	MAXSCORE += gameBoard.getBreadCount();
	infoXY = gameBoard.getInfoSP();

	if(color)
		colorGame();

	if(saveMode)
	{
		toggleManageFile();
	}

}

void Game::toggleManageFile()
{
	player1->getSaveObj(stepsFile);

	for (int i = 0; i < ghostsNum; i++)
		{
			ghosts[i]->getSaveObj(stepsFile);
		}

}

void Game::run()
{
	playing = true;
	char key; 
	char keepLastMoveKey; 
	moveCounter = 0;
	Point moveTo;
	
	gameBoard.printBoard();
	levelOfGhost();

	while (playing) 
	{
		checkForPress(key, keepLastMoveKey);

		checkIfEaten(key);

		printScore();

		objMovment();

		if(!isThereFruit)
			createFruit();
		
		drawFigures();//Draws Pacman and ghosts 

		checkIfEaten(key);

		gameStat();

		Sleep((int)general::PACE); // pace of the game

		if (saveMode)
		{
			stepsFile->WriteToFile("end\n");
		}

		moveCounter++;
	}
}

void Game::levelOfGhost()
{
	if (level != (char)levels::NOVICE)
	{
		Game::smartM = new SmartMove(&gameBoard);

		for (int i = 0; i < ghostsNum; i++)
		{
			ghosts[i]->getSmartMove(smartM);
		}
	}
}

void Game::createFruit()
{
	if (rand() % 120==1)
	{
		Game::gFruit=new Fruit();

		if (saveMode)
			gFruit->getSaveObj(stepsFile);

		gFruit->spawn(gameBoard);
		if (color)
			gFruit->toggleColor();
		isThereFruit = true;
		
	}
}



void Game::gameStat() // check if game should be over
{
	if(isThereFruit)
		if(gFruit->deleteOverTime())
		{
			gFruit->switchToPrevChar(gameBoard);//deletes the fruit visually 
			delete gFruit;
			isThereFruit = false;
			if (saveMode)
			{
				stepsFile->WriteToFile("DF ");
			}
		}

	if (LIVES < 1 || SCORE >= MAXSCORE)
	{
		clrscr();
		deleteEndOfMap();
		if (SCORE == MAXSCORE)
		{
			gotoxy(15,5);
			cout << "******    LEVEL WON !!    ******";
			playing = false;
			gotoxy(20, 10);
			cout << "PRESS ANY KEY TO CONTINUE";

			
			if (saveMode) 
			{
				resultFile->WriteToFile("Finish ");
				resultFile->WriteToFile(moveCounter);
				resultFile->WriteToFile('\n');
			}
			
			
		}

		if (LIVES < 1)
		{
			gotoxy(15,5);
			cout << "******    GAME OVER    ******"<<endl;
			playing = false;
			gotoxy(20, 10);
			cout << "PRESS ANY KEY TO RETURN TO MENU" << endl;

			if (saveMode) 
			{
				resultFile->WriteToFile("GAMEOVER");
				resultFile->WriteToFile('\n');
			}
		}
		if(color)
			SetConsoleTextAttribute(hConsole, (char)colors::WHITE);
		_getch(); //return value ignored on purpuse, only checking for any key pressed
	}
}

void Game::deleteEndOfMap()
{
	for (int i = 0; i < ghostsNum; i++) //creates the ghosts
		{
			delete ghosts[i];
		}
		delete player1;

		if (isThereFruit)
		{
			delete gFruit;
			isThereFruit = false;
		}
			
		if (smartGhosts)
			delete smartM;		
}

void Game::checkIfEaten(char& key) //checks if the ghosts touch the player
{
	for (int i = 0; i < ghostsNum; i++)
	{
		if (player1->getPos() == ghosts[i]->getPos())
		{
			LIVES--;
			player1->erase();
			for (int i = 0; i < ghostsNum; i++)
				ghosts[i]->erase();
			
			key = 's';

			//add to result the time of death
			if (saveMode) 
			{
				resultFile->WriteToFile("Death ");
				resultFile->WriteToFile(moveCounter);
				resultFile->WriteToFile('\n');
			}
			


			player1->resetPos();
			for (int i = 0; i < ghostsNum; i++)
				ghosts[i]->resetPos();

			if (LIVES != 0) //reset and play animation
			{
				if(!silentFlag)
					flashAnimation();
			}
			break;
		}
		if (isThereFruit && (ghosts[i]->getPos() == gFruit->getPos()))
		{
			delete gFruit;
			isThereFruit = false;
		}
	}

	if (isThereFruit && (player1->getPos() == gFruit->getPos()))
	{
		int bonusPoints = gFruit->getBonus();
		MAXSCORE += bonusPoints;
		SCORE += bonusPoints;

		delete gFruit;
		isThereFruit = false;
	}
}

void Game::flashAnimation()
{
	for (int i = 0; i < 2; i++) //flashy
	{
		drawFigures();
		Sleep((int)general::PACE * 2);
		player1->erase();
		for (int i = 0; i < ghostsNum; i++)
			ghosts[i]->erase();
		Sleep((int)general::PACE * 2);
	}
}

void Game::printScore() //print Lives and Score 
{ 
	if(color)
		SetConsoleTextAttribute(hConsole, (char)colors::RED);
	gotoxy(infoXY.x, infoXY.y);
	cout << "LIVES: " << LIVES << endl;
	gotoxy(infoXY.x, infoXY.y+1);
	cout << "SCORE: " << SCORE << endl;
}

void Game::drawFigures() 
{
	if (isThereFruit)
		gFruit->draw();
	player1->draw();
	for (int i = 0; i < ghostsNum; i++)
	{
		ghosts[i]->draw();
	}
}

void Game::objMovment()
{
	if (moveCounter % 2 == 0)
	{
		if(level!=(char)levels::NOVICE)
			smartM->BFS(player1->getXY()); //if smart only
		for (int i = 0; i < ghostsNum; i++)
			ghosts[i]->pickMovement(level,gameBoard);
	}

	if (moveCounter % 5 == 0)
	{
		if (isThereFruit)
			gFruit->move(gameBoard);
	}

}

void Game::checkForPress(char &key,char &keepLastMoveKey)
{
	if(_kbhit())
	{
		key=_getch();//Gets from player the move 
	}

	if (key == (int)general::ESC) //If player presses ESC to pause game 
		{
			gotoxy(1, 25); 
			cout << "GAME IS PAUSED. PRESS ESC TO RESUME" << endl;
			key = 0;
			while (key != (int)general::ESC)
			{
				key = _getch();
			}

			gotoxy(1, 25); 
			cout << "                                    " << endl;
			key = keepLastMoveKey;
		}
		
	if (player1->moveReq(key, gameBoard, SCORE))
		keepLastMoveKey = key;
	else
		player1->moveReq(keepLastMoveKey,gameBoard, SCORE);
}

void Game::colorGame() //tell all objects to use their colors
{
	for (int i = 0; i < ghostsNum; i++)
		ghosts[i]->toggleColor();
	player1->toggleColor();
	gameBoard.toggleColor();
}

void Game::scanForFiles()
{
	string path = ".";
	string name;
	for (const auto& file : std::filesystem::directory_iterator::directory_iterator(path))
	{
		if (file.path().filename().string().find(".screen") != -1)
		{
			name = file.path().filename().string();
			name.resize(name.size() - 7); //7 cuz ".screen" is 7 chars
			fileNames.push_back(name);
		}
	}

	// sort by ABC(not sure if needed)
	std::sort(fileNames.begin(), fileNames.end());
}


void Game::loadMode(bool silent)
{
	silentFlag = silent;
	int i = 0;
	char c='0';//uselss?
	bool testFailedFlag = false;
	bool FilesError = false;
	stepsFile = new ManageFile;
	resultFile = new ManageFile;
	LIVES = 3;
	SCORE = 0;
	for (i = 0; i < fileNames.size(); i++) //maybe a while ?
	{
		stepsFile->setFileName(fileNames[i] + ".steps");
		resultFile->setFileName(fileNames[i] + ".result");
	 	int pacmanTOD[3] = {}; //time of death
		int numTOD=0; // number of time of death
		int finishTime=0;
		moveCounter = 0;
		string input;
		int currGhost = 0;
		int currDeath = 0;

		if(!gameBoard.loadLevel(fileNames[i])) //load the level - gameboard
		{
			FilesError = true;
				break;
		}
		if (!stepsFile->openFileForReading()) //open step file
		{
			FilesError = true;
			break;
		}

		if (silentFlag)
		{
			if (!loadMode_readResult(FilesError, input, pacmanTOD, numTOD, finishTime)) //read the result file, false if there was a problem with the file, true if done
				break;
		}

		setAllObjects();
		
		if(!silentFlag)
			gameBoard.printBoard(); //print the board if we are not playing on 'silent'
		
		while (!stepsFile->eof()) //play the game till no more file to read
		{
			loadMode_readStep(input, currGhost, pacmanTOD, currDeath, testFailedFlag);
		} //end of this screen

		if (stepsFile->eof() && LIVES > 0 && silentFlag) // meaning - we finished the steps file, and won the level (lives>0)
		{
			if (finishTime != moveCounter)
				testFailedFlag = true;
		}

		deleteEndOfMap(); //delete on everything allocated

		//if gameover use break
		stepsFile->closeFile();
		if(silentFlag)
			resultFile->closeFile();
		
		clrscr();
		if (loadMode_endCondition(testFailedFlag,i)) //if we hit the end condition
			break;
	}
	
	if (FilesError)
	{
		cout << "The program stopped: Error With The Files" <<endl;
	}
	delete stepsFile;
	delete resultFile;
}

void Game::loadMode_readStep(string& input, int& currGhost, int pacmanTOD[],int& currDeath, bool& testFailedFlag)
{
	char c;
	stepsFile->getString(input); //get the start of the next line. 
	while (!stepsFile->eof() && input != "end") // one full loop        
	{
		if (input == "NF") // create a new fruit
		{
			
			stepsFile->getString(input);
			int x = stoi(input);
			stepsFile->getString(input);
			int y = stoi(input);
			stepsFile->getString(input);
			char z = input[0];
			gFruit = new Fruit(x, y, z);
			isThereFruit = true;
		}
		if (input == "P") // update pacman 
		{
			stepsFile->getString(input);
			int dir = stoi(input);
			player1->moveReq(player1->moveKeys[dir], gameBoard, SCORE);
			if (silentFlag)
				player1->erase();
		}
		if (input == "G") 
		{
			stepsFile->getString(input);
			int dir = stoi(input);
			ghosts[currGhost]->erase();
			if (!silentFlag)
				ghosts[currGhost]->printBreadIfBehind(gameBoard);
			ghosts[currGhost]->changeDirection(dir);
			ghosts[currGhost]->addDirToPos();
			currGhost++;
		}
		if (input == "F") // update fruit
		{
			gFruit->erase();
			if (!silentFlag)
				gFruit->printBreadIfBehind(gameBoard);
			stepsFile->getString(input);
			int dir = stoi(input);
			gFruit->changeDirection(dir);
			gFruit->addDirToPos();

		}
		if (input == "DF") // update fruit
		{
			if (!silentFlag)
				gFruit->switchToPrevChar(gameBoard);//deletes the fruit visually 
			delete gFruit;
			isThereFruit = false;

		}
		if (!silentFlag)
			checkIfEaten(c);
		else
		{
			for (int i = 0; i < ghostsNum; i++)
			{
				if (player1->getPos() == ghosts[i]->getPos())
				{
					LIVES--;
					if (pacmanTOD[currDeath] != moveCounter)
					{
						testFailedFlag = true;

					}
					player1->resetPos();
					for (int i = 0; i < ghostsNum; i++)
						ghosts[i]->resetPos();
					currDeath++;
				}
			}
		}
		stepsFile->getString(input);
	}

	currGhost = 0; //back to first ghost


	if (!silentFlag)
	{
		printScore();
		drawFigures();
		//checkIfEaten(c); //??
		Sleep((int)general::PACE / 2); // pace of the game
	}

	if (silentFlag && SCORE != MAXSCORE)
		moveCounter++;

}

bool Game::loadMode_readResult(bool& FilesError,string& input, int pacmanTOD[], int& numTOD, int& finishTime)
{
	if (!resultFile->openFileForReading())
	{
		FilesError = true;
		return false;// break;
	}
	resultFile->getString(input);
	while (!resultFile->eof())
	{
		if (input == "Death") //use enum?
		{
			resultFile->getString(input);
			pacmanTOD[numTOD] = stoi(input);
			numTOD++;
		}
		else if (input == "Finish")
		{
			resultFile->getString(input);
			finishTime = stoi(input);
		}
		resultFile->getString(input);
	}
	resultFile->closeFile();
	return true;
}

bool Game::loadMode_endCondition(bool& testFailedFlag, int &i)
{
	if (testFailedFlag == true)
	{
		cout << "Test Failed!";
		return true;
	}

	if (LIVES < 1 || i == fileNames.size() - 1)
	{
		if (silentFlag)
		{
			cout << "Test Passed!";
			return true;
		}
		else if (LIVES < 1)
		{
			clrscr();
			cout << "******    GAME OVER    ******" << endl;
			return true;
		}
		else if (i == fileNames.size() - 1)
		{

			clrscr();
			cout << "******    GAME WON!    ******" << endl;
			return true;
		}
	}
	return false;
}