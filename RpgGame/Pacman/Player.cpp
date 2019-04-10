#include "Player.h"
#include "Menus.h"
#include "Functions.h"
#include "Level.h"
#include "RpgGame.h"

#include <sstream>
#include <iostream>

Player::~Player()
{
	delete _playerTexture;
	delete _playerSourceRect;
	delete relativePos;
	delete _playerPosition;
	delete keyboardState;
	delete playerCollisionBox;
}
void Player::LoadContent()
{
	_playerTexture = new Texture2D();
	_playerTexture->Load("Textures/CharSpriteSheet.Png", false);
	_playerPosition = new Vector2(256, 256);
	_playerSourceRect = new Rect(0.0f, 0.0f, 32, 32);
}

void Player::Update(int elapsedTime)
{
	//basic animation
	if (keyboardState->IsKeyDown(Input::Keys::W))//if w pressed
	{
		_playerDirection = 2;
		_isMoving = true;
	}
	if (keyboardState->IsKeyDown(Input::Keys::A))//if a pressed
	{
		_playerDirection = 1;
		_isMoving = true;
	}
	if (keyboardState->IsKeyDown(Input::Keys::S))//if s pressed
	{
		_playerDirection = 0;
		_isMoving = true;
	}
	if (keyboardState->IsKeyDown(Input::Keys::D))//if d pressed
	{
		_playerDirection = 3;
		_isMoving = true;
	}


	//Movement control in grid
	if (isCollisionW == false)
	{
		if (keyboardState->IsKeyDown(Input::Keys::W) && (!Spressed) && (!Wpressed) && (!Apressed) && (!Dpressed))
		{
			Wpressed = true;
			mustBeLocation = relativePos->Y - 32;
		}
		if (Wpressed)
		{
			_isMoving = true;
			_playerDirection = 2;
			if ((relativePos->Y > mustBeLocation + 2))//if we are further down the screen than -32 of our original position
			{
				if (!(keyboardState->IsKeyDown(Input::Keys::LEFTSHIFT)))//check to see if not running
				{
					relativePos->Y -= 0.1 * elapsedTime;//move up the screen
				}
				else//if the player IS running
				{
					relativePos->Y -= 0.2 * elapsedTime;//move fast up the screen
					_frameCount++;//make the frames go up faster, so the character animates faster!
				}
			}
			else//if the player has reached the position
			{
					Wpressed = false;
					_isMoving = false;
					relativePos->Y = mustBeLocation;
			}
		}
	}
	if (isCollisionS == false)
	{
		if (keyboardState->IsKeyDown(Input::Keys::S) && (!Spressed) && (!Wpressed) && (!Apressed) && (!Dpressed))
		{
			Spressed = true;
			mustBeLocation = (relativePos->Y + 32);
		}
		if (Spressed)
		{
			_isMoving = true;
			_playerDirection = 0;
			if ((relativePos->Y < mustBeLocation - 2))//if we are further up the screen than +32 of our original position
			{
				if (!(keyboardState->IsKeyDown(Input::Keys::LEFTSHIFT)))//check to see if not running
				{
					relativePos->Y += 0.1 * elapsedTime;//move down the screen
				}
				else//if the player IS running
				{
					relativePos->Y += 0.2 * elapsedTime;//move fast down the screen
					_frameCount++;//make the frames go up faster, so the character animates faster!
				}
			}
			else//if the player has reached the position
			{
				Spressed = false;
				_isMoving = false;
				relativePos->Y = mustBeLocation;
			}
		}
	}
	if (isCollisionA == false)
	{
		if (keyboardState->IsKeyDown(Input::Keys::A) && (!Spressed) && (!Wpressed) && (!Apressed) && (!Dpressed))
		{
			Apressed = true;
			mustBeLocation = relativePos->X - 32;
		}
		if (Apressed)
		{
			_isMoving = true;
			_playerDirection = 1;
			if ((relativePos->X > mustBeLocation + 2))//if we are to the right than -32 of our original position
			{
				if (!(keyboardState->IsKeyDown(Input::Keys::LEFTSHIFT)))//check to see if not running
				{
					relativePos->X -= 0.1 * elapsedTime;//move Left on the screen
				}
				else//if the player IS running
				{
					relativePos->X -= 0.2 * elapsedTime;//move fast left the screen
					_frameCount++;//make the frames go up faster, so the character animates faster!
				}
			}
			else//if the player has reached the position
			{
				Apressed = false;
				_isMoving = false;
				relativePos->X = mustBeLocation;
			}
		}
	}
	if (isCollisionD == false)
	{
		if (keyboardState->IsKeyDown(Input::Keys::D) && (!Spressed) && (!Wpressed) && (!Apressed) && (!Dpressed))
		{
			Dpressed = true;
			mustBeLocation = (relativePos->X + 32);
		}
		if (Dpressed)
		{
			_isMoving = true;
			_playerDirection = 3;
			if ((relativePos->X < mustBeLocation - 2))//if we are further to the left than +32 of our original position
			{
				if (!(keyboardState->IsKeyDown(Input::Keys::LEFTSHIFT)))//check to see if not running
				{
					relativePos->X += 0.1 * elapsedTime;//move right on the screen
				}
				else//if the player IS running
				{
					relativePos->X += 0.2 * elapsedTime;//move fast right on the screen
					_frameCount++;//make the frames go up faster, so the character animates faster!
				}
			}
			else//if the player has reached the position
			{
				Dpressed = false;
				_isMoving = false;
				relativePos->X = mustBeLocation;
			}
		}
	}
	//end of movement control in grid

	//Direction Control
	if (_isMoving)
	{
		if (_playerDirection == 0)//0 = down
		{
			if ((_frameCount >= 0) && _frameCount < 15)
			{
				*_playerSourceRect = Rect(0, 0.00f, 32, 32);
			}
			if (_frameCount >= 15 && _frameCount < 30)
			{
				*_playerSourceRect = Rect(32, 0.00f, 32, 32);
			}
			if (_frameCount >= 30 && _frameCount < 45)
			{
				*_playerSourceRect = Rect(64, 0.00f, 32, 32);
			}
			if (_frameCount >= 45 && _frameCount  < 60)
			{
				*_playerSourceRect = Rect(32, 0.00f, 32, 32);
			}
		}
		if (_playerDirection == 1)//1 = left
		{
			if ((_frameCount >= 0) && _frameCount < 15)
			{
				*_playerSourceRect = Rect(0.00f, 32, 32, 32);
			}
			if (_frameCount >= 15 && _frameCount < 30)
			{
				*_playerSourceRect = Rect(32, 32, 32, 32);
			}
			if (_frameCount >= 30 && _frameCount < 45)
			{
				*_playerSourceRect = Rect(64, 32, 32, 32);
			}
			if (_frameCount >= 45 && _frameCount  < 60)
			{
				*_playerSourceRect = Rect(32, 32, 32, 32);
			}
		}

		if (_playerDirection == 2)//2 = up
		{
			if ((_frameCount >= 0) && _frameCount < 15)
			{
				*_playerSourceRect = Rect(0.00f, 96, 32, 32);
			}
			if (_frameCount >= 15 && _frameCount < 30)
			{
				*_playerSourceRect = Rect(32, 96, 32, 32);
			}
			if (_frameCount >= 30 && _frameCount < 45)
			{
				*_playerSourceRect = Rect(64, 96, 32, 32);
			}
			if (_frameCount >= 45 && _frameCount  < 60)
			{
				*_playerSourceRect = Rect(32, 96, 32, 32);
			}
		}
		if (_playerDirection == 3)//3 = right
		{
			if ((_frameCount >= 0) && _frameCount < 15)
			{
				*_playerSourceRect = Rect(0.00f, 64, 32, 32);
			}
			if (_frameCount >= 15 && _frameCount < 30)
			{
				*_playerSourceRect = Rect(32, 64, 32, 32);
			}
			if (_frameCount >= 30 && _frameCount < 45)
			{
				*_playerSourceRect = Rect(64, 64, 32, 32);
			}
			if (_frameCount >= 45 && _frameCount  < 60)
			{
				*_playerSourceRect = Rect(32, 64, 32, 32);
			}
		}
	}

	//idle animations
	if (!_isMoving)
	{
		if (_playerDirection == 0 && (keyboardState->IsKeyUp(Input::Keys::S)))//0 = down
		{
			*_playerSourceRect = Rect(32, 0.00f, 32, 32);
		}
		if (_playerDirection == 1 && (keyboardState->IsKeyUp(Input::Keys::A)))//1 = Left
		{
			*_playerSourceRect = Rect(32, 32, 32, 32);
		}
		if (_playerDirection == 2 && (keyboardState->IsKeyUp(Input::Keys::W)))//2 = Up
		{
			*_playerSourceRect = Rect(32, 96, 32, 32);
		}
		if (_playerDirection == 3 && (keyboardState->IsKeyUp(Input::Keys::D)))//3 = Right
		{
			*_playerSourceRect = Rect(32, 64, 32, 32);
		}
	}
	_frameCount++;
	if (_frameCount > 60)
	{
		_frameCount = 0;
	}
	

	//update the values of the collision box
	*playerCollisionBox = Rect(_playerPosition->X, _playerPosition->Y, 10, 10);

	isCollisionW = false;
	isCollisionA = false;
	isCollisionS = false;
	isCollisionD = false;

}

void Player::Draw(int elapsedTime)
{
	std::stringstream playerPosDraw;
	playerPosDraw << "Player X: " << _playerPosition->X << "Player Y: " << _playerPosition->Y;
	Vector2* posDrawPosition = new Vector2(0,32);
	SpriteBatch::DrawString(playerPosDraw.str().c_str(), posDrawPosition, Color::White);
	SpriteBatch::Draw(_playerTexture, _playerPosition, _playerSourceRect);// Draws Player
}