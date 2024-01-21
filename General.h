#ifndef _General
#define _General


//File that holds general setting of the game 

enum class general { ESC = 27, PACE = 100, maxMove=20};
enum class boardSettings { ROW = 24, COL = 58 ,MENU_S=425,RULES_S=1387, LEVELS_S = 377, HOWTO=377};
enum class ghost {g1_x=27, g2_x=32,g_y=12, g_moveC =20,maxGhost=4,minGhost=1};
enum class pacman {p_x=28,p_y=14};
enum class colors { YELLOW = 14, RED= 12 ,WHITE=15,DARK_YELLOW=6,BLUE=9,GREEN = 10};
enum class keys { PLAY = '1', PLAY_C = '2', RULES = '8', EXIT = '9', LOAD_BOARD='2'};
enum class gameObjects{BREADCRUM='.',PACMAN='@',GHOST='$',SPACE= ' ',WALL='#',INFO='&',NOTBREAD='%', FRUIT=53};
enum class direction {UP,DOWN,LEFT,RIGHT,DONT_CHANGE=-1};
enum class levels { BEST = 'a', GOOD='b',NOVICE='c'};
enum class smartM { VERTICAL=4};
enum class dirX { UP = 0, DOWN = 0, LEFT = -1, RIGHT = 1 };
enum class dirY { UP = -1, DOWN = 1, LEFT = 0, RIGHT = 0 };
enum class gameMode { MODE = 1, LOADMODE = 2, SAME = 0,LOAD = 'l',SAVE = 's' , NORMAL = 'n' };

//GAME 110
#include <conio.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using std::vector;
using std::string;
using std::cout;
using std::endl;
#include <filesystem>



struct xy
{
	int x, y;
};




#endif