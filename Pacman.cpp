#include "Pacman.h"

//moveReq returns False if the wrong key was pressed. updates the board and the SCORE accordingly.
bool Pacman::moveReq(char dir, Board& b, int& SCORE)
{
	//check for right key.
	//checks if move can be called accurding to dir
	// if yes calls move to to the move and update board
	int diraction = dirOfKey(dir);
	if (diraction == -1)
		return false; //not the right key to move pacman

	char c;
	
	moveTo = nextMoveOfFigure(diraction); // change the diraction, and check where would we move
	c = b.getChar(moveTo.getY() , moveTo.getX()); //get the next char
	if (c == (char)gameObjects::SPACE || c == (char)gameObjects::NOTBREAD) //legit move into a empty space
	{
			move(b);
			
			return true;
	}
	else if (c == (char)gameObjects::BREADCRUM) //legit move into a BREADCRUMB
	{
			SCORE++;
			move(b); //moves knows to remove the breadcumb
			
			return true;
	}
	else
	{
			checkForTunnels(b); // teleports pacman if relevant
			c = b.getChar(moveTo.getY(), moveTo.getX()); //check if landed on a breadcrumb
			if (c == (char)gameObjects::BREADCRUM) 
			{
				SCORE++;
				b.changeChar(moveTo.getY(), moveTo.getX(), (char)gameObjects::SPACE);//remove the breadcrumb
			}
			if (saving) // maybe not?
			{
				save->WriteToFile("P ");
				save->WriteToFile(enumDir);
			}
			return true;
	}
	
	
	return true;   //includes the - c == (char)gameObjects::WALL
}

int Pacman::move(Board& b) //makes the move if called, and updates the board. 
{
	//gets board. if bread, now = ' '
	erase();
	pos.addToXY(dirX, dirY);
	draw();
	if (saving)
	{
		save->WriteToFile("P ");
		save->WriteToFile(enumDir);
	}
	if (b.getChar(moveTo.getY(), moveTo.getX()) == (char)gameObjects::BREADCRUM)
	{
		b.changeChar(moveTo.getY(), moveTo.getX(), (char)gameObjects::SPACE);//remove the breadcrumb
		return 1; //eat a bread
	}
	return 0; // sucess but not eat a bread

}

int Pacman::dirOfKey(char dir)
{
	for (int i = 0; i < 5; i++)//Checks to see if the key is for this pacman
	{
		if (tolower(dir) == moveKeys[i]) // check for if the right key
		{
			return i;
		}
	}
	return -1;
}

void Pacman::checkForTunnels(Board& b)//checks to see if we are about to enter a tunnel
{

	if (moveTo.getX() < Board::min_x && b.getChar(moveTo.getY(), Board::max_x - 1)!=(char)gameObjects::WALL) //CHANGE TO THE GLOBAL MIN AND MAX
	{
		erase();
		setPos(Board::max_x-1, moveTo.getY());
		moveTo.setXY(Board::max_x-1, moveTo.getY());
		draw();
	}

	if (moveTo.getY() < Board::min_y && b.getChar(Board::max_y - 1, moveTo.getX()) != (char)gameObjects::WALL) //CHANGE TO THE GLOBAL MIN AND MAX
	{
		erase();
		setPos(moveTo.getX(), Board::max_y-1);
		moveTo.setXY(moveTo.getX(), Board::max_y-1);
		draw();
	}

	else if (moveTo.getY() >= Board::max_y && b.getChar(Board::min_y, moveTo.getX()) != (char)gameObjects::WALL) //CHANGE TO THE GLOBAL MIN AND MAX
	{
		erase();
		setPos(moveTo.getX(), Board::min_y);
		moveTo.setXY(moveTo.getX(), Board::min_y);
		draw();
	}

	else if (moveTo.getX() >= Board::max_x && b.getChar(moveTo.getY(), Board::min_x) != (char)gameObjects::WALL) //CHANGE TO THE GLOBAL MIN AND MAX
	{
		erase();
		setPos(Board::min_x, moveTo.getY());
		moveTo.setXY(Board::min_x, moveTo.getY());
		draw();
	}
}