#pragma once

#include "S2D/S2D.h"
using namespace S2D;

class HeadBubble
{
private:
	

public:
	/// <summary> Destroys any data associated with the class. </summary>
	virtual ~HeadBubble();
	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	void virtual Draw(int elapsedTime);

	Vector2* bubblePos;
	Rect* bubbleRect;
	Texture2D* bubbleTexture;
	bool canDrawText = false;
	string whatToSay;
};