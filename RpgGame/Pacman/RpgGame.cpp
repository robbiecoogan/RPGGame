#include "RpgGame.h"
#include "Enemy.h"
#include "Player.h"
#include "Menus.h"
#include "Functions.h"
#include "Level.h"

#include <sstream>
#include <iostream>

RpgGame::RpgGame(int argc, char* argv[]) : Game(argc, argv)
{
	
	Player1 = new Player();
	Menu1 = new Menu();
	MyFunctions = new Functions();
	MyLevel = new Level();
	enemySpawn = 10;
	playerCanUpdate = true;
	bumper = new SoundEffect();
	backgroundMusic = new SoundEffect();

	for (int i = 0; i <= amountofwalls; i++)//assign unique IDs to all the walls so they can be placed correctly
	{
		WallArray[i].myNumber = i+1;
		WallArray[i].canchecknum = true;
	}
	for (int i = 0; i <= helmAmount ; i++)//assign unique IDs to all the helms so they can be placed correctly
	{
		HelmArray[i].myID = i;
		HelmArray[i].canCheckNum = true;
	}



	_frameCount = 0;
	//Initialise important Game aspects
	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "RpgGame", 60);
	Input::Initialise();

	



	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}


RpgGame::~RpgGame()
{
	delete enemyArray;
	delete Player1;
	delete Menu1;
	delete MyFunctions;
	delete MyLevel;
	delete WallArray;
	delete HelmArray;
	delete bumper;
	delete _stringPosition;
	delete enemyArray;
	delete backgroundMusic;
}

void RpgGame::LoadContent()
{
	for (int i = 0; i < enemySpawn; i++)
	{
		enemyArray[i].LoadContent();
	}	
	for (int i = 0; i < amountofwalls; i++)
	{
		WallArray[i].LoadContent();
	}
	
	Player1->LoadContent();
	Menu1->LoadContent();
	MyLevel->LoadContent();
	for (int i = 0; i < helmAmount; i++)
	{
		HelmArray[i].LoadContent();
	}

	// Set string position
	*_stringPosition = Vector2(10.0f, 25.0f);

	//Load Sounds
	bumper->Load("Sounds/bump.wav");
	backgroundMusic->Load("Sounds/BackgroundMusic.wav");

	//play backgroudn music
	backgroundMusic->SetLooping(true);
	Audio::Play(backgroundMusic);
}
void RpgGame::Update(int elapsedTime)
{		
	Input::MouseState* mouse = Input::Mouse::GetState();
	//if (mouse->LeftButton == Input::ButtonState::PRESSED)

	//the menu is used even when the game is paused, meaning this still needs to be performed nonetheless.
	if (!(!Menu1->_startOfGame && !Menu1->_drawOptions))
	{
		Menu1->Update(elapsedTime);
	}

	//if the game is not paused, update the objects, now the game acts paused.
	if (!Menu1->_paused)
	{
		if (_frameCount % 2 == 0)//save on processing power by making the enemy only update every 2 frames
		{
			for (int i = 0; i < enemySpawn; i++)//update each enemy
			{
				enemyArray[i].Update(elapsedTime);
				*enemyArray[i]._enemyPosition = Vector2(MyLevel->_gameBackgroundRectangle->X + enemyArray[i].relativePos->X, MyLevel->_gameBackgroundRectangle->Y + enemyArray[i].relativePos->Y);
			}
		}

		if (_frameCount % 2 == 0)//save on processing power by making the helm only update every 2 frames
		{
			for (int i = 0; i < helmAmount; i++)//update each helm
			{
				HelmArray[i].Update(elapsedTime);
			}
		}

		//check if the player pressing a certain key will move him off screen, if not, move normally
		playerCanUpdate = true;//reset this value for each frame
		if (keyboardState->IsKeyDown(Input::Keys::W) && Player1->relativePos->Y -1 < 0 && Player1->_isMoving == false)//check W
		{
			Player1->relativePos->Y = (768 - 32);
			Player1->_originalPos = 768;
			Player1->mustBeLocation = 768;
			*MyLevel->_currentMapLoc = Rect(MyLevel->_currentMapLoc->X, MyLevel->_currentMapLoc->Y - 768, 768, 768);
			if (Player1->helmEquipped == true)
			{
				HelmArray[Player1->arrayHelmNum].myDrawPosition->Y = MyLevel->_currentMapLoc->Y;
			}
			playerCanUpdate = false;
		}
		else if (keyboardState->IsKeyDown(Input::Keys::S) && (Player1->relativePos->Y + Player1->_playerSourceRect->Height) + 1 > MyLevel->_gameBackgroundRectangle->Height && Player1->_isMoving == false)//check S
		{
			Player1->relativePos->Y = 0;
			Player1->_originalPos = 0;
			Player1->mustBeLocation = 0;
			*MyLevel->_currentMapLoc = Rect(MyLevel->_currentMapLoc->X, MyLevel->_currentMapLoc->Y + 768, 768, 768);
			if (Player1->helmEquipped == true)
			{
				HelmArray[Player1->arrayHelmNum].myDrawPosition->Y = MyLevel->_currentMapLoc->Y;
			}
			playerCanUpdate = false;
		}
		else if (keyboardState->IsKeyDown(Input::Keys::A) && Player1->relativePos->X - 1 < 0 && Player1->_isMoving == false)//check A
		{
			Player1->relativePos->X = (768 - 32);
			Player1->_originalPos = (768 - 32);
			Player1->mustBeLocation = (768 - 32);
			*MyLevel->_currentMapLoc = Rect(MyLevel->_currentMapLoc->X - 768, MyLevel->_currentMapLoc->Y, 768, 768);
			if (Player1->helmEquipped == true)
			{
				HelmArray[Player1->arrayHelmNum].myDrawPosition->X = MyLevel->_currentMapLoc->X;
			}
			playerCanUpdate = false;
		}
		else if (keyboardState->IsKeyDown(Input::Keys::D) && (Player1->relativePos->X + Player1->_playerSourceRect->Width) + 1 > MyLevel->_gameBackgroundRectangle->Width && Player1->_isMoving == false)//check D
		{
			Player1->relativePos->X = 0;
			Player1->_originalPos = 0;
			Player1->mustBeLocation = 0;
			*MyLevel->_currentMapLoc = Rect(MyLevel->_currentMapLoc->X + 768, MyLevel->_currentMapLoc->Y, 768, 768);
			if (Player1->helmEquipped == true)
			{
				HelmArray[Player1->arrayHelmNum].myDrawPosition->X = MyLevel->_currentMapLoc->X;
			}
			playerCanUpdate = false;
		}

		if (MyLevel->_currentMapLoc->X == 768 && MyLevel->_currentMapLoc->Y == 0)//only do this if the wall is visible on screen
		{
			//check to see if the player is going to collide with a wall when he tries to move, if so, dont move
			if (keyboardState->IsKeyDown(Input::Keys::W))//check W for collision
			{
				for (int i = 0; i < amountofwalls; i++)
				{
					if (MyFunctions->checkCollision(Player1->relativePos->X + 16, Player1->relativePos->Y, 0, 0, WallArray[i].relativePos->X, WallArray[i].relativePos->Y, 32, 32/*i know the width and height of the walls, so 32!*/))
					{
						Player1->isCollisionW = true;
						Player1->_playerDirection = 2; //nice effect to change the player direction to up without moving
						if (doOnce == true)
						{
							Audio::Play(bumper);//Play a bump sound, not like Pokemon at all...
							doOnce = false;
						}
					}
				}
			}
			if (keyboardState->IsKeyDown(Input::Keys::A))//check A for collision
			{
				for (int i = 0; i < amountofwalls; i++)
				{
					if (MyFunctions->checkCollision(Player1->relativePos->X, Player1->relativePos->Y + 16, 0, 0, WallArray[i].relativePos->X, WallArray[i].relativePos->Y, 32, 32/*i know the width and height of the walls, so 32!*/))
					{
						Player1->isCollisionA = true;
						Player1->_playerDirection = 1; //nice effect to change the player direction to left without moving
						if (doOnce == true)
						{
							Audio::Play(bumper);//Play a bump sound, not like Pokemon at all...
							doOnce = false;
						}
					}
				}
			}
			if (keyboardState->IsKeyDown(Input::Keys::S))//check S for collision
			{
				for (int i = 0; i < amountofwalls; i++)
				{
					if (MyFunctions->checkCollision(Player1->relativePos->X + 16, Player1->relativePos->Y + 32, 0, 0, WallArray[i].relativePos->X, WallArray[i].relativePos->Y, 32, 32/*i know the width and height of the walls, so 32!*/))
					{
						Player1->isCollisionS = true;
						Player1->_playerDirection = 0; //nice effect to change the player direction to down without moving
						if (doOnce == true)
						{
							Audio::Play(bumper);//Play a bump sound, not like Pokemon at all...
							doOnce = false;
						}
					}
				}
			}
			if (keyboardState->IsKeyDown(Input::Keys::D))//check D for collision
			{
				for (int i = 0; i < amountofwalls; i++)
				{
					if (MyFunctions->checkCollision(Player1->relativePos->X + 32, Player1->relativePos->Y + 16, 0, 0, WallArray[i].relativePos->X, WallArray[i].relativePos->Y, 32, 32/*i know the width and height of the walls, so 32!*/))
					{
						Player1->isCollisionD = true;
						Player1->_playerDirection = 3; //nice effect to change the player direction to right without moving
						if (doOnce == true)
						{
							Audio::Play(bumper);//Play a bump sound, not like Pokemon at all...
							doOnce = false;
						}
					}
				}
			}
		}

		if (keyboardState->IsKeyUp(Input::Keys::W) && keyboardState->IsKeyUp(Input::Keys::A) && keyboardState->IsKeyUp(Input::Keys::S) && keyboardState->IsKeyUp(Input::Keys::D))//check all keys to see if bump sound can be reused
		{
			doOnce = true;
		}


		if (playerCanUpdate)
		{
			Player1->Update(elapsedTime);
		}


		//if the level goes into negative viewing, it will not show entities correctly, meanign we should stop this by making it wrap around.
		if (MyLevel->_currentMapLoc->X < 0)
		{
			MyLevel->_currentMapLoc->X = 1536;
		}
		if (MyLevel->_currentMapLoc->Y < 0)
		{
			MyLevel->_currentMapLoc->Y = 1536;
		}
		if (MyLevel->_currentMapLoc->X > 1536)
		{
			MyLevel->_currentMapLoc->X = 0;
		}
		if (MyLevel->_currentMapLoc->Y > 1536)
		{
			MyLevel->_currentMapLoc->Y = 0;
		}
		
		MyLevel->Update(elapsedTime);
	}
	for (int i = 0; i < amountofwalls; i++)
	{
		WallArray[i].Update(elapsedTime, MyLevel->_currentMapLoc->X, MyLevel->_currentMapLoc->Y);
		*WallArray[i].wallPos = Vector2(MyLevel->_gameBackgroundRectangle->X + WallArray[i].relativePos->X, MyLevel->_gameBackgroundRectangle->Y + WallArray[i].relativePos->Y);
	}
	
	*Player1->_playerPosition = Vector2(MyLevel->_gameBackgroundRectangle->X + Player1->relativePos->X, MyLevel->_gameBackgroundRectangle->Y + Player1->relativePos->Y);

	if (setHelmPos == true)
	{
		for (int i = 0; i < helmAmount; i++)//set position of Helmets
		{
			if (HelmArray[i].equipped == false)
			{
				*HelmArray[i].helmPosition = Vector2(MyLevel->_gameBackgroundRectangle->X + HelmArray[i].relativePos->X, MyLevel->_gameBackgroundRectangle->Y + HelmArray[i].relativePos->Y);
			}
			if (Player1->helmEquipped == true)
			{
				*HelmArray[Player1->arrayHelmNum].helmPosition = *Player1->_playerPosition;
				*HelmArray[Player1->arrayHelmNum].helmRect = *Player1->_playerSourceRect;
			}

		}
		//setHelmPos = false;
	}

	//equip the helm - this needs to be after the above statement
	for (int i = 0; i < helmAmount; i++)
	{
		if (HelmArray[i].myDrawPosition->X == MyLevel->_currentMapLoc->X && HelmArray[i].myDrawPosition->Y == MyLevel->_currentMapLoc->Y)//check when the helm is on screen
		{
			if (keyboardState->IsKeyDown(Input::Keys::R) && Player1->helmEquipped == true)//if there is a helmet equipped
			{
				//drop the helm
				*HelmArray[Player1->arrayHelmNum].relativePos = Vector2(Player1->relativePos->X, Player1->relativePos->Y + 5);//place below the cahracters head, for effect
				HelmArray[Player1->arrayHelmNum].equipped = false;//put old helm on the floor
				*HelmArray[Player1->arrayHelmNum].helmRect = Rect(0,0,32,32);//make helm face front

				Player1->helmEquipped = false;
				HelmArray[i].canCheckNum = false;
				Player1->arrayHelmNum = -1;


			}
			if (keyboardState->IsKeyDown(Input::Keys::E) && MyFunctions->checkCollision(HelmArray[i].relativePos->X, HelmArray[i].relativePos->Y, 32, 32, Player1->relativePos->X + 8, Player1->relativePos->Y + 8, 16, 16))//if the helm collides with the player
			{
				if (Player1->helmEquipped == false)//if a helm is not equipped when colliding
				{
					Player1->arrayHelmNum = i;//this holds the value in the array that the current helm is at.
					HelmArray[i].equipped = true;
					Player1->helmEquipped = true;
					
				}
			}

			if (HelmArray[i].equipped == true)
			{
				*HelmArray[i].helmPosition = Vector2(Player1->_playerPosition->X, Player1->_playerPosition->Y);
			}
		}
	}

	for (int i = 0; i < enemySpawn; i++)
	{
		if (MyFunctions->checkCollision(enemyArray[i]._enemyPosition->X - 32, enemyArray[i]._enemyPosition->Y - 32, 96,96, Player1->_playerPosition->X + 8, Player1->_playerPosition->Y + 8, Player1->_playerSourceRect->Width - 8, Player1->_playerSourceRect->Height - 8))//is player within range of enemy
		{
			enemyArray[i].isPlayerWithinDistance = true;
			cout << "Within distance\n";
		}
		else
		{
			enemyArray[i].isPlayerWithinDistance = false;
			cout << "Not Within distance\n";
			enemyArray[i].chooseSay = rand() % 3 + 1;
		}
	}
	

}
void RpgGame::Draw(int elapsedTime)
{
	SpriteBatch::BeginDraw(); // Starts Drawing
	//draw players and enemies when the game is not at the start menu.
	if (!Menu1->_startOfGame && !Menu1->_drawOptions)
	{
		MyLevel->Draw(elapsedTime);

		if (randomize == true)
		{
			for (int i = 0; i < enemySpawn; i++)
			{
				*enemyArray[i].myRandomPos = Vector2(enemyArray[i].myRandomPos->X = rand() % 24, enemyArray[i].myRandomPos->X = rand() % 24);
			}
			randomize = false;//never becomes true again, meaning they only get randomized once
		}

		for (int i = 0; i < enemySpawn; i++)//draw enemies
		{
			//if the enemies are currently in view
			if (enemyArray[i].myMapPos->X == MyLevel->_currentMapLoc->X && enemyArray[i].myMapPos->Y == MyLevel->_currentMapLoc->Y)
			{
				enemyArray[i].Draw(elapsedTime);//draw the enemy
			}
		}

		for (int i = 0; i < amountofwalls; i++)//draw walls
		{
			if (WallArray[i].viewPos->X == MyLevel->_currentMapLoc->X && WallArray[i].viewPos->Y == MyLevel->_currentMapLoc->Y)
			{
				WallArray[i].Draw(elapsedTime);
			}
		}




		for (int i = 0; i < helmAmount; i++)
		{

			if (Player1->helmEquipped == true)
			{
				Player1->Draw(elapsedTime);//draw the Player
				HelmArray[Player1->arrayHelmNum].Draw(elapsedTime);
			}

			if (HelmArray[i].myDrawPosition->X == MyLevel->_currentMapLoc->X && HelmArray[i].myDrawPosition->Y == MyLevel->_currentMapLoc->Y)
			{
				if (HelmArray[i].equipped == false)
				{
					HelmArray[i].Draw(elapsedTime);
				}
			}

		}

		if (Player1->helmEquipped == false)
		{
			Player1->Draw(elapsedTime);//draw the Player
		}

	}
	else
	{
		Menu1->Draw(elapsedTime);//draw the Menus
	}


	std::stringstream debugDraw;

	for (int i = 0; i < enemySpawn; i++)//check if the player is colliding with ANY enemy
	{
		//if the enemy is in view, calculate collision
		if (enemyArray[i].myMapPos->X == MyLevel->_currentMapLoc->X && enemyArray[i].myMapPos->Y == MyLevel->_currentMapLoc->Y)
		{
			if (MyFunctions->checkCollision(Player1->playerCollisionBox->X, Player1->playerCollisionBox->Y, Player1->playerCollisionBox->Width, Player1->playerCollisionBox->Height, enemyArray[i].enemyCollisionBox->X, enemyArray[i].enemyCollisionBox->Y, Player1->playerCollisionBox->Width, Player1->playerCollisionBox->Height))
			{
				checkPlayerCollision = true;
			}
		}
	}

	std::stringstream currentRectInfoDraw;

	currentRectInfoDraw << "Level X port: " << MyLevel->_currentMapLoc->X << "   Y Port: " << MyLevel->_currentMapLoc->Y;
	Vector2* posDrawPosition = new Vector2(0, 64);
	SpriteBatch::DrawString(currentRectInfoDraw.str().c_str(), posDrawPosition, Color::White);

	SpriteBatch::DrawString(debugDraw.str().c_str(), &Vector2(0, 64), Color::White);
	SpriteBatch::EndDraw(); // Ends Drawing
}
