#pragma once
#include "Level.h"

#include "S2D/S2D.h"
using namespace S2D;

class Wall
{
private:

	Texture2D* wallTexture = new Texture2D();
	Rect* wallRectangle = new Rect;

	

public:
	virtual ~Wall();

	void virtual LoadContent();

	void virtual Update(int elapsedTime, int posX, int posY);

	void virtual Draw(int elapsedTime);

	//for placing these blocks
	Vector2* wallPos = (0, 0);
	int myNumber = 0;
	bool canchecknum = false;
	Vector2* relativePos = (0, 0);//the relative position of these to the map

	//what viewport this block should be visible at
	Vector2* viewPos;
};