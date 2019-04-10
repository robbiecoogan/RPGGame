#include "Functions.h"

#include <sstream>

Functions::~Functions()
{

}


bool Functions::checkCollision(int obj1X, int obj1Y, int obj1Width, int obj1Height, int obj2X, int obj2Y, int obj2Width, int obj2Height)
{
	//where there is nothing  in the if statement, that means there is no collision, on the else, that will return true if there is a collision
	if ((obj2X + obj2Width) < obj1X)//checking left of obj1
	{
		return 0;
		//no collision
	}
	else if ((obj2Y + obj2Height) < obj1Y)//checking above obj1
	{
		return 0;
		//no collision
	}
	else if (obj2X > (obj1X + obj1Width))//checking right of obj1
	{
		return 0;
		//no collision
	}
	else if (obj2Y > (obj1Y + obj1Height))//checking below obj1
	{
		return 0;
		//no collision
	}
	else
	{
		return 1;
	}
}