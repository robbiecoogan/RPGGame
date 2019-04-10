#pragma once

#include "HeadBubble.h"
#include "Player.h"

#include "S2D/S2D.h"
using namespace S2D;

class Enemy
{
	private:

		int shouldIMove;

		int enemy1Direction = rand() % 4 + 1;

		//used foor position and texture of the enemy
		Texture2D* _enemyTexture;

		//used for timing
		int _timecount = 0;

		bool isMoving = false;
		int originalPos;
		int mustBeLocation;

		SoundEffect* nyeh;
		bool soundOnce = true;//stop sounds from playing 60 times a second -_-

	public:
		/// <summary> Destroys any data associated with the class. </summary>
		virtual ~Enemy();
		/// <summary> All content should be loaded in this method. </summary>
		void virtual LoadContent();

		/// <summary> Called every frame - update game logic here. </summary>
		void virtual Update(int elapsedTime);

		void virtual Draw(int elapsedTime);

		Vector2* _enemyPosition;
		Rect* _enemySourceRect;
		Vector2* relativePos = new Vector2(256,256);

		Vector2* myMapPos;//the viewport on the map that this mob is located
		int changeFrame1, changeFrame2, changeFrame3, changeFrame4;//random frames that this enemy will choose to change direction
		//collision box
		Rect* enemyCollisionBox = new Rect(10, 10, 10, 10);//this results in a small box in the middle of the character

		Vector2* myRandomPos = new Vector2(-1,-1);

		HeadBubble* MyHeadBubble = new HeadBubble();
		bool isPlayerWithinDistance = false;
		int chooseSay = 0;

		
};