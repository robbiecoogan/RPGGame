#pragma once

#include "S2D/S2D.h"
using namespace S2D;

class Level
{
private:

public:
	virtual ~Level();

	void virtual LoadContent();

	void virtual Update(int elapsedTime);

	void virtual Draw(int elapsedTime);
	Texture2D* _gameBackground = new Texture2D();
	Rect* _gameBackgroundRectangle = new Rect(0,0,0,0);
	Rect* _currentMapLoc = new Rect(0,0,0,0);//Stores the current map location on the map file
};