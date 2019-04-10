#include "Helm.h"

#include <sstream>
#include <iostream>

Helm::~Helm()
{
	delete helm;
	delete helmRect;
	delete helmPosition;
	delete relativePos;
	delete myDrawPosition;
}
void Helm::LoadContent()
{
	helm = new Texture2D();
	helm->Load("Textures/Helm1.Png", false);
	helmPosition = new Vector2(0, 0);
	helmRect = new Rect(0, 0, 32, 32);

	relativePos = new Vector2(0, 0);
	myDrawPosition = new Vector2(768, 0);
}

void Helm::Update(int elapsedTime)
{
	//animate to rotate on the spot
	if (equipped == false)//rotate on the spot
	{
		if ((frameCount >= 0) && frameCount < 10)
		{
			*helmRect = Rect(0, 0.00f, 32, 32);
		}
		if (frameCount >= 10 && frameCount < 20)
		{
			*helmRect = Rect(0, 32, 32, 32);
		}
		if (frameCount >= 20 && frameCount < 30)
		{
			*helmRect = Rect(0, 96, 32, 32);
		}
		if (frameCount >= 30 && frameCount < 40)
		{
			*helmRect = Rect(0, 64, 32, 32);
		}
	}


	if (canCheckNum == true)//initialise what helmet it should look like
	{
		canCheckNum = false;
		if (myID == 0)
		{
			helmType = 0;
			*relativePos = Vector2(448, 352);
		}
		if (myID == 1)
		{
			helmType = 1;
			*relativePos = Vector2(160, 416);
		}

		if (helmType == 0)
		{
			if (doOnce == true)
			{
				helm->Load("Textures/Helm1.Png", false);
				doOnce = false;
			}
		}
		if (helmType == 1)
		{
			if (doOnce == true)
			{
				helm->Load("Textures/Helm2.Png", false);
				doOnce = false;
			}
		}
		
	}
	frameCount++;
	if (frameCount > 40)
	{
		frameCount = 0;
	}
}

void Helm::Draw(int elapsedTime)
{
	SpriteBatch::Draw(helm, helmPosition, helmRect);// Draws helmet
}