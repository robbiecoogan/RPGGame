#include "Wall.h"

#include <sstream>

Wall::~Wall()
{
	delete wallTexture;
	delete wallPos;
	delete wallRectangle;
	delete relativePos;
}

void Wall::LoadContent()
{
	wallTexture = new Texture2D();
	wallTexture->Load("Textures/Wall1.Png", false);
	wallPos = new Vector2(0, 0);
	wallRectangle = new Rect(0.0f, 0.0f, 32, 32);

	viewPos = new Vector2(768, 0);
	relativePos = new Vector2(0, 0);
}

void Wall::Update(int elapsedTime, int posX, int posY)
{
	if (canchecknum = true)
	{
		if (myNumber > 0 && myNumber <= 10)//efficiency
		{
			if (myNumber == 1) { *relativePos = Vector2(416, 640); }
			if (myNumber == 2) { *relativePos = Vector2(416, 608); }
			if (myNumber == 3) { *relativePos = Vector2(416, 576); }
			if (myNumber == 4) { *relativePos = Vector2(416, 544); }
			if (myNumber == 5) { *relativePos = Vector2(416, 512); }
			if (myNumber == 6) { *relativePos = Vector2(448, 512); }
			if (myNumber == 7) { *relativePos = Vector2(480, 512); }
			if (myNumber == 8) { *relativePos = Vector2(512, 512); }
			if (myNumber == 9) { *relativePos = Vector2(544, 512); }
			if (myNumber == 10) { *relativePos = Vector2(544, 480); }
		}
		if (myNumber > 10 && myNumber <= 20)//efficiency
		{
			if (myNumber == 11) { *relativePos = Vector2(544, 448); }
			if (myNumber == 12) { *relativePos = Vector2(544, 416); }
			if (myNumber == 13) { *relativePos = Vector2(544, 384); }
			if (myNumber == 14) { *relativePos = Vector2(544, 352); }
			if (myNumber == 15) { *relativePos = Vector2(544, 320); }
			if (myNumber == 16) { *relativePos = Vector2(512, 288); }
			if (myNumber == 17) { *relativePos = Vector2(480, 256); }
			if (myNumber == 18) { *relativePos = Vector2(448, 256); }
			if (myNumber == 19) { *relativePos = Vector2(416, 224); }
			if (myNumber == 20) { *relativePos = Vector2(384, 224); }
		}
		if (myNumber > 20 && myNumber <= 30)//efficiency
		{
			if (myNumber == 21) { *relativePos = Vector2(352, 224); }
			if (myNumber == 22) { *relativePos = Vector2(320, 224); }
			if (myNumber == 23) { *relativePos = Vector2(288, 256); }
			if (myNumber == 24) { *relativePos = Vector2(256, 256); }
			if (myNumber == 25) { *relativePos = Vector2(224, 288); }
			if (myNumber == 26) { *relativePos = Vector2(192, 320); }
			if (myNumber == 27) { *relativePos = Vector2(192, 352); }
			if (myNumber == 28) { *relativePos = Vector2(160, 352); }
			if (myNumber == 29) { *relativePos = Vector2(128, 352); }
			if (myNumber == 30) { *relativePos = Vector2(96, 352); }
		}
		if (myNumber > 30 && myNumber <= 40)//efficiency
		{
			if (myNumber == 31) { *relativePos = Vector2(96, 384); }
			if (myNumber == 32) { *relativePos = Vector2(96, 416); }
			if (myNumber == 33) { *relativePos = Vector2(96, 448); }
			if (myNumber == 34) { *relativePos = Vector2(128, 448); }
			if (myNumber == 35) { *relativePos = Vector2(160, 448); }
			if (myNumber == 36) { *relativePos = Vector2(192, 448); }
			if (myNumber == 37) { *relativePos = Vector2(192, 480); }
			if (myNumber == 38) { *relativePos = Vector2(192, 512); }
			if (myNumber == 39) { *relativePos = Vector2(224, 512); }
			if (myNumber == 40) { *relativePos = Vector2(256, 512); }
		}
		if (myNumber > 40 && myNumber <= 50)//efficiency
		{
			if (myNumber == 41) { *relativePos = Vector2(288, 512); }
			if (myNumber == 42) { *relativePos = Vector2(320, 512); }
			if (myNumber == 43) { *relativePos = Vector2(320, 544); }
			if (myNumber == 44) { *relativePos = Vector2(320, 576); }
			if (myNumber == 45) { *relativePos = Vector2(320, 608); }
			if (myNumber == 46) { *relativePos = Vector2(320, 640); }
		}
		canchecknum = false;
	}

}

void Wall::Draw(int elapsedTime)
{
	SpriteBatch::Draw(wallTexture, wallPos, wallRectangle);// Draws Wall

	/*DEBUG CODE - this will display the number of each wall
	stringstream drawMyNum;
	drawMyNum << myNumber;
	Vector2* newVector = new Vector2(wallPos->X + 16, wallPos->Y + 16);
	SpriteBatch::DrawString(drawMyNum.str().c_str(), newVector, Color::White);*/
	
}