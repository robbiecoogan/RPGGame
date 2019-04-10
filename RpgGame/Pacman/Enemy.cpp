#include "Enemy.h"
#include "HeadBubble.h"
#include "Player.h"

#include <sstream>
#include <iostream>

Enemy::~Enemy()
{
	delete _enemyTexture;
	delete _enemyPosition;
	delete _enemySourceRect;
	delete relativePos;
	delete myMapPos;
	delete enemyCollisionBox;
	delete myRandomPos;
	delete MyHeadBubble;
	delete nyeh;
}
void Enemy::LoadContent()
{
	
	_enemyTexture = new Texture2D();
	_enemyTexture->Load("Textures/EnemySheet.Png", false);
	_enemyPosition = new Vector2(0, 0);
	_enemySourceRect = new Rect(0.0f, 0.0f, 32, 32);

	myMapPos = new Vector2(1536, 768);
	changeFrame1 = rand() % 120 + 1;
	changeFrame2 = rand() % 120 + 1;
	changeFrame3 = rand() % 120 + 1;
	changeFrame4 = rand() % 120 + 1;

	shouldIMove = 0;
	MyHeadBubble->LoadContent();

	nyeh = new SoundEffect();
	nyeh->Load("Sounds/nyeh.wav");
}

void Enemy::Update(int elapsedTime)
{
	MyHeadBubble->Update(elapsedTime);
	
	*MyHeadBubble->bubblePos = Vector2(_enemyPosition->X - 32, _enemyPosition->Y - 36);

	if (isPlayerWithinDistance == true)
	{
		MyHeadBubble->canDrawText = true;
		
		if (chooseSay == 0)
		{
			chooseSay = rand() % 3 + 1;
		}
		if (chooseSay == 1)
		{
			MyHeadBubble->whatToSay = ("L2P Scrub");
			chooseSay = -1;
			soundOnce = true;
			cout << "Yeah";
		}
		if (chooseSay == 2)
		{
			MyHeadBubble->whatToSay = ("Get Rekt!");
			chooseSay = -1;
			soundOnce = true;
			cout << "Yeah";
		}
		if (chooseSay == 3)
		{
			MyHeadBubble->whatToSay = ("Fight IRL");
			chooseSay = -1;
			soundOnce = true;
			cout << "Yeah";
		}
	}

	//can i set my position?
	if (myRandomPos->X != -1)
	{
		relativePos->X = myRandomPos->X * 32;
		myRandomPos->X = -1;//dont do this twice
	}
	if (myRandomPos->Y != -1)
	{
		relativePos->Y = myRandomPos->Y * 32;
		myRandomPos->Y = -1;//dont do this twice
	}



	if ((_timecount == changeFrame1 || _timecount == changeFrame2 || _timecount == changeFrame3 || _timecount == changeFrame4) && isMoving == false)
	{
		enemy1Direction = rand() % 4 + 1;
	}

	if ((_timecount == changeFrame1 || _timecount == changeFrame2 || _timecount == changeFrame3 || _timecount == changeFrame4) && shouldIMove < 4)
	{
			shouldIMove = rand() % 4 + 1;//this will randomize 0 though 4. 1,2, and 3 is false, 4 is true.
			if (shouldIMove == 4 && enemy1Direction == 1)//down
			{
				isMoving = true;
				mustBeLocation = relativePos->Y + 32;
			}
			else if (shouldIMove == 4 && enemy1Direction == 2)//left
			{
				isMoving = true;
				mustBeLocation = relativePos->X - 32;
			}
			else if (shouldIMove == 4 && enemy1Direction == 3)//right
			{
				isMoving = true;
				mustBeLocation = relativePos->X + 32;
			}
			else if (shouldIMove == 4 && enemy1Direction == 4)//up
			{
				isMoving = true;
				mustBeLocation = relativePos->Y - 32;
			}

	}

	if (shouldIMove == 4 && enemy1Direction == 1)//down
	{
		//first of all can we move down?
		if (!(relativePos->Y >= (768 - 32)))
		{
			int newRelativePos = relativePos->Y;//to make the decimal 'relativePos' into an integer for checking...
			if ((newRelativePos < mustBeLocation))//if the mob is not at the final location yet...
			{
				relativePos->Y += 0.1 * elapsedTime;//move down constantly
			}
			else
			{
				//relativePos->Y = mustBeLocation;
				isMoving = false;
				shouldIMove = 0;
			}
		}
		else//move them to the next Screen
		{
			*myMapPos = Vector2(myMapPos->X, myMapPos->Y + 768);
			if (myMapPos->Y > 1536)
			{
				myMapPos->Y = 0;
			}
			relativePos->Y =  0;
			mustBeLocation = 32;
		}
	}
	else if (shouldIMove == 4 && enemy1Direction == 2)//left
	{
		//first of all, can we move Left?
		if (!(relativePos->X < 0))
		{
			int newRelativePos = relativePos->X;
			if ((newRelativePos > mustBeLocation))//if the mob is not at the final location yet...
			{
				relativePos->X -= 0.1 * elapsedTime;//move left constantly
			}
			else
			{
				//relativePos->X = mustBeLocation;
				isMoving = false;
				shouldIMove = 0;
			}
		}
		else//move them to the next Screen
		{
			*myMapPos = Vector2(myMapPos->X - 768, myMapPos->Y);
			if (myMapPos->X < 0)
			{
				myMapPos->X = 1536;
			}
			relativePos->X = 768 - 32;
			mustBeLocation = 704;
		}
	}
	else if (shouldIMove == 4 && enemy1Direction == 3)//right
	{
		//first of all, can we move Right?
		if (!(relativePos->X >= (768 - 32)))
		{
			int newRelativePos = relativePos->X;
			if ((newRelativePos < mustBeLocation))//if the mob is not at the final location yet...
			{
				relativePos->X += 0.1 * elapsedTime;//move right constantly
			}
			else
			{
				//relativePos->X = mustBeLocation;
				isMoving = false;
				shouldIMove = 0;
			}
		}
		else//move them to the next Screen
		{
			*myMapPos = Vector2(myMapPos->X + 768, myMapPos->Y);
			if (myMapPos->X > 1536)
			{
				myMapPos->X = 0;
			}
			relativePos->X = 0;
			mustBeLocation = 32;
		}
	}
	else if (shouldIMove == 4 && enemy1Direction == 4)//up
	{
		//first of all, can we move up?
		if (!(relativePos->Y <= 32))
		{
			int newRelativePos = relativePos->Y;
			if ((newRelativePos > mustBeLocation))//if the mob is not at the final location yet...
			{
				relativePos->Y -= 0.1 * elapsedTime;//move up constantly
			}
			else
			{
				//relativePos->Y = mustBeLocation;
				isMoving = false;
				shouldIMove = 0;
			}
		}
		else//move them to the next Screen
		{
			*myMapPos = Vector2(myMapPos->X, myMapPos->Y - 768);
			if (myMapPos->Y < 0)
			{
				myMapPos->Y = 1536;
			}
			relativePos->Y = 768 - 32;
			mustBeLocation = 704;
		}
	}

	
	_timecount++;
	if (_timecount > 120)
	{
		_timecount = 0;
	}

	//idle animations
	if (enemy1Direction == 1)//down
	{
		*_enemySourceRect = Rect(32, 0.0f, 32, 32);
	}
	if (enemy1Direction == 2)//left
	{
		*_enemySourceRect = Rect(32, 32, 32, 32);
	}
	if (enemy1Direction == 3)//right
	{
		*_enemySourceRect = Rect(32, 64, 32, 32);
	}
	if (enemy1Direction == 4)//up
	{
		*_enemySourceRect = Rect(32, 96, 32, 32);
	}

	if (isMoving == true)
	{
		//moving animations
		if (enemy1Direction == 1)//down
		{
			int newTimeCount = _timecount / 2;
			if ((newTimeCount >= 0) && newTimeCount < 15)//frame 1
			{
				*_enemySourceRect = Rect(32, 0.0f, 32, 32);
			}
			if (newTimeCount >= 15 && newTimeCount < 30)//frame 2
			{
				*_enemySourceRect = Rect(0, 0.0f, 32, 32);
			}
			if (newTimeCount >= 30 && newTimeCount < 45)//frame 3
			{
				*_enemySourceRect = Rect(32, 0.0f, 32, 32);
			}
			if (newTimeCount >= 45 && newTimeCount < 60)//frame 4
			{
				*_enemySourceRect = Rect(64, 0.0f, 32, 32);
			}
		}

		if (enemy1Direction == 2)//left
		{
			int newTimeCount = _timecount / 2;
			if ((newTimeCount >= 0) && newTimeCount < 15)//frame 1
			{
				*_enemySourceRect = Rect(32, 32, 32, 32);
			}
			if (newTimeCount >= 15 && newTimeCount < 30)//frame 2
			{
				*_enemySourceRect = Rect(0, 32, 32, 32);
			}
			if (newTimeCount >= 30 && newTimeCount < 45)//frame 3
			{
				*_enemySourceRect = Rect(32, 32, 32, 32);
			}
			if (newTimeCount >= 45 && newTimeCount < 60)//frame 4
			{
				*_enemySourceRect = Rect(64, 32, 32, 32);
			}
		}

		if (enemy1Direction == 3)//right
		{
			int newTimeCount = _timecount / 2;
			if ((newTimeCount >= 0) && newTimeCount < 15)//frame 1
			{
				*_enemySourceRect = Rect(32, 64, 32, 32);
			}
			if (newTimeCount >= 15 && newTimeCount < 30)//frame 2
			{
				*_enemySourceRect = Rect(0, 64, 32, 32);
			}
			if (newTimeCount >= 30 && newTimeCount < 45)//frame 3
			{
				*_enemySourceRect = Rect(32, 64, 32, 32);
			}
			if (newTimeCount >= 45 && newTimeCount < 60)//frame 4
			{
				*_enemySourceRect = Rect(64, 64, 32, 32);
			}
		}

		if (enemy1Direction == 4)//up
		{
			int newTimeCount = _timecount / 2;
			if ((newTimeCount >= 0) && newTimeCount < 15)//frame 1
			{
				*_enemySourceRect = Rect(32, 96, 32, 32);
			}
			if (newTimeCount >= 15 && newTimeCount < 30)//frame 2
			{
				*_enemySourceRect = Rect(0, 96, 32, 32);
			}
			if (newTimeCount >= 30 && newTimeCount < 45)//frame 3
			{
				*_enemySourceRect = Rect(32, 96, 32, 32);
			}
			if (newTimeCount >= 45 && newTimeCount < 60)//frame 4
			{
				*_enemySourceRect = Rect(64, 96, 32, 32);
			}
		}
	}

	//update the values of the collision box
	*enemyCollisionBox = Rect(_enemyPosition->X, _enemyPosition->Y, 10, 10);

}

void Enemy::Draw(int elapsedTime)
{
	SpriteBatch::Draw(_enemyTexture, _enemyPosition, _enemySourceRect);// Draws Enemy
	if (isPlayerWithinDistance == true)
	{
		MyHeadBubble->Draw(elapsedTime);
		if (soundOnce == true)
		{
			Audio::Play(nyeh);
			soundOnce = false;
		}
	}
}