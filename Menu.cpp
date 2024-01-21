#include "Menu.h"

Menu::Menu() : menu{
					"              **************************************\n"
					"              *                                    *\n"
					"              *      1. PLAY GAME - NO COLOR       *\n"
					"              *      2. PLAY GAME - WITH COLOR     *\n"
					"              *      8. INSTRUCTIONS               *\n"
					"              *      9. EXIT                       *\n"
					"              *                                    *\n"
					"              **************************************\n"
},
rules{
					"              ************************************************\n"
					"              *                                              *\n"
					"              *                  ~ RULES ~                   *\n"
					"              *                                              *\n"
					"              *   PACMAN MUST EAT ALL THE BREAD CRUMBS       *\n"
					"              *   IN ORDER TO WIN.                           *\n"
					"              *   HE MUST ESCAPE FROM THE GHOSTS.            *\n"
					"              *   IF HE GETS CAUGHT BY ONE THEN HE LOSES     *\n"
					"              *   ONE OF HIS LIVES, HE HAS 3 LIVES OVERALL.  *\n"
					"              *   ONCE PACMAN HAS NO LIVES ITS GAME OVER.    *\n"
					"              *                                              *\n"
					"              *                ~CONTROLS ~                   *\n"
					"              *                                              *\n"
					"              *    W - UP        ESC - PAUSE GAME            *\n"
					"              *    X - DOWN                                  *\n"
					"              *    D - RIGHT                                 *\n"
					"              *    A - LEFT                                  *\n"
					"              *    S - STAY                                  *\n"
					"              *                                              *\n"
					"              *                    PRESS ANY KEY TO GO BACK  *\n"
					"              *                                              *\n"
					"              ************************************************\n"
},
levels{
	"              ********************************\n"
	"              *                              *\n"
	"              *          PICK LEVEL          *\n"
	"              *          (a) BEST            *\n"
	"              *          (b) GOOD            *\n"
	"              *          (c) NOVICE          *\n"
	"              *                              *\n"
	"              ********************************\n"
},

howTo{
	"              ********************************\n"
	"              *                              *\n"
	"              * How would you like to play?  *\n"
	"              *                              *\n"
	"              *     (1) All levels by order  *\n"
	"              *                              *\n"
	"              *     (2) Choose a level       *\n"
	"              ********************************\n"
}

{};

char Menu::options()
{
	char key;

	while (true)
	{
		clrscr();
		gotoxy(0, 5);

		cout << menu << endl;

		key = _getch();

		if (key == (char)keys::RULES)
		{
			gotoxy(0, 1);

			cout << rules << endl;

			key = _getch();
		}

		else if (key == (char)keys::PLAY || key == (char)keys::PLAY_C || key == (char)keys::EXIT)
		{
			clrscr();
			return key;
		}

	}
}

char Menu::pickLevel()
{
	char key;

	while (true)
	{
		clrscr();
		gotoxy(0, 5);

		cout << levels << endl;

		key = _getch();

		for (int i = 0; i < 3; i++)
		{
			if (levelKeys[i] == tolower(key))
			{
				clrscr();
				return key;
			}
		}
	}
}

char Menu::howToPlay()
{
	char key;

	while (true)
	{
		clrscr();
		gotoxy(0, 5);

		cout << howTo << endl;

		key = _getch();

		if (key == '1' || key == '2')
		{
			clrscr();
			return key;
		}
			
	}
}



//gets list of files as a vector,prints them, and returns the key for the file
char Menu::pickBoard(vector<string> filesNames)
{
	char key;
	clrscr();
	int row = 0;
	for (vector<string>::iterator it = filesNames.begin(); it != filesNames.end(); ++it)
	{
		cout << "*" << row+1 << ". " << *it << " *" << endl;
		row++;
	}
	while (true)
	{
		key = _getch();
		for (int i = 0; i < row; i++)
		{
			if (key-'0' > 0 && key - '0' <= row)
			{
				clrscr();
				return key-1;
			}
		}
	}
}