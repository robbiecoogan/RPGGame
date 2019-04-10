#include "Level.h"

#include <sstream>

Level::~Level()
{
	delete _gameBackground;
	delete _gameBackgroundRectangle;
	delete _currentMapLoc;
}
void Level::LoadContent()
{
	//inGame declarations
	_gameBackground = new Texture2D();
	_gameBackground->Load("Textures/Room1.Png", false);
	_gameBackgroundRectangle = new Rect(0.00f, 0.00f, 768, 768);
	_currentMapLoc = new Rect((_gameBackground->GetWidth() / 2) - (768 / 2), (_gameBackground->GetHeight() / 2) - (768 / 2), 768, 768);
}

void Level::Update(int elapsedTime)
{
	int screenWidth = Graphics::GetViewportWidth();
	int screenHeight = Graphics::GetViewportHeight();

	if (((screenWidth / 2) - (_gameBackgroundRectangle->Width / 2)) >= 0)//align along the X axis if it is more than 0
	{
		*_gameBackgroundRectangle = Rect((int)((screenWidth / 2) - (_gameBackgroundRectangle->Width / 2)), (int)(_gameBackgroundRectangle->Y), 768, 768);
	}
	else
	{
		*_gameBackgroundRectangle = Rect(0, (int)(_gameBackgroundRectangle->Y), _gameBackgroundRectangle->Width, _gameBackgroundRectangle->Height);
	}


	if (((screenHeight / 2) - (_gameBackgroundRectangle->Height / 2)) >= 0)//align along the Y axis if it is more than 0, this SHOULD be separate from previous statement
	{
		*_gameBackgroundRectangle = Rect((int)(_gameBackgroundRectangle->X), (int)((screenHeight / 2) - (_gameBackgroundRectangle->Height / 2)), 768, 768);
	}
	else
	{
		*_gameBackgroundRectangle = Rect((int)(_gameBackgroundRectangle->X), 0, _gameBackgroundRectangle->Width, _gameBackgroundRectangle->Height);
	}
	//the main room is in the center of the image, so to find the location of the main point, i have to find the center point, then minus the X and Y by half of 768
	

}

void Level::Draw(int elapsedTime)
{
	SpriteBatch::Draw(_gameBackground, /*nullptr*/_gameBackgroundRectangle, _currentMapLoc);
}