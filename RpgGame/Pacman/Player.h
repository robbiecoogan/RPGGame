#pragma once

#include "S2D/S2D.h"
using namespace S2D;

class Player
{
private:

	Texture2D* _playerTexture;//player image

	//Used for animations
	int _frameCount;

	//for gaining input from peripherals
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	//Data used for movement

	bool Wpressed;
	bool Spressed;
	bool Apressed;
	bool Dpressed;//you should see someone about that...


public:
	/// <summary> Destroys any data associated with the class. </summary>
	virtual ~Player();
	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	void virtual Draw(int elapsedTime);

	//int static X();
	int static SetX(int newX);
	//int static Y();
	int static SetY(int newY);
	//int static GetWidth();
	//int static GetHeight();
	
	int _originalPos;
	int mustBeLocation;
	Vector2* _playerPosition = new Vector2(0,0);
	Rect* _playerSourceRect = nullptr;
	Vector2* relativePos = new Vector2(256,256);//the position that is changed so the player stays in the middle of the screen.

	//player collision box
	Rect* playerCollisionBox = new Rect(8, 8, 16, 16);//this results in a small box in the middle of the character

	int _playerDirection;//change direction from other object
	bool _isMoving;

	bool isCollisionW = false;
	bool isCollisionA = false;
	bool isCollisionS = false;
	bool isCollisionD = false;


	bool helmEquipped = false;
	int arrayHelmNum = -1;
};