
#include "General.h"
#include "Game.h"


bool checkArg(int argc, char* argv[]);
void chooseGameMode(int argc, char* argv[]);

void main(int argc, char* argv[])
{
	srand(time(NULL));
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	if (!checkArg(argc, argv))
	{
		cout << "Please use the following format: pacman.exe -load|-save [-silent]"<<endl;
	}
	else
	{
		chooseGameMode(argc, argv);
	}
}

bool checkArg(int argc, char* argv[])
{
	if (argc == 1) // nothing entered for the command prompt
		return true;
	if (argc > 3) // illegal
	{
		return false;
	}
	if(strcmp(argv[(int)gameMode::MODE], "-load")!=(int)gameMode::SAME && strcmp(argv[(int)gameMode::MODE], "-save") != (int)gameMode::SAME)
		return false;
	
	return true;
}

void chooseGameMode(int argc, char* argv[])
{
	bool running = true;
	if (argc == 1) // nothing entered for the command prompt
	{
		while (running)
		{
			Game thePacmanGame;
			running=thePacmanGame.init();
		}
	}
	else if (strcmp(argv[1], "-load")==0)
	{
		bool silent;
		if (argc > 2 && strcmp(argv[2], "-silent")==0)
		{
			silent = true;
		}
		else
		{
			silent = false;
		}
		Game thePacmanGame;
		thePacmanGame.loadMode(silent);
	}
	else if (strcmp(argv[1], "-save")==0)
	{
		while (running)
		{
			Game thePacmanGame;
			thePacmanGame.turnOnSaveMode();
			running=thePacmanGame.init();
		}
	}

}