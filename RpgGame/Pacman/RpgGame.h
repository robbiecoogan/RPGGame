#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

#include "S2D/S2D.h"
#include "Enemy.h"
#include "Player.h"
#include "Menus.h"
#include "Functions.h"
#include "Level.h"
#include "Wall.h"
#include "Helm.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

class RpgGame : public Game
{
private:

	//gain input
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	//amount of mobs to spawn
	Enemy enemyArray[10];//enemy array for storing enemies that can be referenced
	int enemySpawn;//the amount of enemies to spawn at the start of the game

	//general usage data
	int screenWidth;
	int screenHeight;

	// Data to represent Munchie
	int _frameCount;
	/*Rect* _munchieRect;
	Texture2D* _munchieBlueTexture;
	Texture2D* _munchieInvertedTexture;*/

	bool checkPlayerCollision = false;

	bool randomize = true;

	// Position for String
	Vector2* _stringPosition = new Vector2(10.0f, 25.0f);


	//Data used for movement
	int _originalPos;
	bool Wpressed;
	bool Spressed;
	bool Apressed;
	bool Dpressed;//you should see someone about that...
	int _playerDirection;
	bool _isMoving;

	SoundEffect* bumper;
	SoundEffect* nyeh;
	SoundEffect* backgroundMusic;
	
	bool playerCanUpdate;//in case the player is going to collide with a wall or is going to go off screen

public:
	/// <summary> Constructs the Pacman class. </summary>
	RpgGame(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~RpgGame();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);

	Enemy* Enemy1;
	Player* Player1;
	Menu* Menu1;
	Functions* MyFunctions;
	Level* MyLevel;

	int amountofwalls = 46;//the amount of Walls in the game
	Wall WallArray[46];
	int helmAmount = 2;//the amount of helms in the game
	Helm HelmArray[2];


	bool doOnce = true;//for sounds not freaking out
	bool setHelmPos = true;

};