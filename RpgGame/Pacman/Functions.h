#pragma once

#include "S2D/S2D.h"
using namespace S2D;

class Functions
{
private:

public:
	/// <summary> Destroys any data associated with the class. </summary>
	virtual ~Functions();

	static bool checkCollision(int obj1X, int obj1Y, int obj1Width, int obj1Height, int obj2X, int obj2Y, int obj2Width, int obj2Height);

};