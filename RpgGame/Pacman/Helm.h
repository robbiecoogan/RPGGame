#pragma once

#include "S2D/S2D.h"
using namespace S2D;

class Helm
{
private:
	Texture2D* helm;

	bool doOnce = true;

	int frameCount = 0;
public:
	/// <summary> Destroys any data associated with the class. </summary>
	virtual ~Helm();
	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	void virtual Draw(int elapsedTime);

	int helmType = 1;

	Vector2* helmPosition = new Vector2(0,0);
	Vector2* relativePos = new Vector2(0, 0);
	int myID = 1;
	bool equipped = false;//if this is true, it wont be stuck to the ground, and will be equipped to the player
	bool canCheckNum = false;
	Rect* helmRect;

	Vector2* myDrawPosition;//what port on the map this will be drawn at
};