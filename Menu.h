#ifndef _Menu
#define _Menu
#include "General.h"
#include "Gotoxy.h"


class Menu
{
	char menu[(int)boardSettings::MENU_S];
	char rules[(int)boardSettings::RULES_S];
	char levels[(int)boardSettings::LEVELS_S];
	char howTo[(int)boardSettings::HOWTO];
	char levelKeys[3] = { (char)levels::BEST,(char)levels::GOOD,(char)levels::NOVICE};
public:
	Menu();
	char options();
	char pickLevel();
	char pickBoard(vector<string> filesnames);
	char howToPlay();
};


#endif