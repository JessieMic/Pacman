#ifndef _gotoxy
#define _gotoxy

#include <iostream>
#include "Point.h"

using std::cout; 
using std::endl;

#include <windows.h>
#include <process.h>

void gotoxy(int x, int y);

void clrscr();
#endif