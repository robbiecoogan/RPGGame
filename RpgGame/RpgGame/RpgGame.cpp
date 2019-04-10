#include "RpgGame.h"
#include "Enemy.h"
#include "Player.h"
#include "Menus.h"
#include "Functions.h"

#include <sstream>

RpgGame::RpgGame(int argc, char* argv[]) : Game(argc, argv)
{
	Enemy1 = new Enemy();
	Player1 = new Player();
	Menu1 = new Menu();
	MyFunctions = new Functions();

	_frameCount = 0;
	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "RpgGame", 60);
	Input::Initialise();
	
	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
	
}


RpgGame::~RpgGame()
{
	delete _munchieBlueTexture;
	delete _munchieInvertedTexture;
	delete _munchieRect;
	delete _gameBackground;
	delete _gameBackgroundRectangle;
	delete Enemy1;
	delete Player1;
	delete Menu1;

}

void RpgGame::LoadContent()
{
	Enemy1->LoadContent();
	Player1->LoadContent();
	Menu1->LoadContent();

	// Load Munchie
	_munchieBlueTexture = new Texture2D();
	_munchieBlueTexture->Load("Textures/Munchie.tga", true);
	_munchieInvertedTexture = new Texture2D();
	_munchieInvertedTexture->Load("Textures/MunchieInverted.tga", true);
	_munchieRect = new Rect(100.0f, 450.0f, 12, 12);

	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	//inGame declarations
	_gameBackground = new Texture2D();
	_gameBackground->Load("Textures/Room1.Png", false);
	_gameBackgroundRectangle = new Rect(0.00f, 0.00f, 768, 768);
}
void RpgGame::Update(int elapsedTime)
{		
	//the menu is used even when the game is paused, meaning this still needs to be performed nonetheless.
	Menu1->Update(elapsedTime);
	//if the game is not paused, update the objects, now the game acts paused.
	if (!Menu1->_paused)
	{
		Enemy1->Update(elapsedTime);
		Player1->Update(elapsedTime);
	}
		
}
void RpgGame::Draw(int elapsedTime)
{
	SpriteBatch::BeginDraw(); // Starts Drawing
	//draw players and enemies when the game is not at the start menu.
	if (!Menu1->_startOfGame && !Menu1->_drawOptions)
	{
		delete Menu1
		SpriteBatch::Draw(_gameBackground, _gameBackgroundRectangle, nullptr);
		if _frameCount ]eeflvmfevpfmpenvnevn

		Enemy1->Draw(elapsedTime);//draw the enemy
		Player1->Draw(elapsedTime);//draw the Player
	}
		Menu1->Draw(elapsedTime);//draw the Menus

		std::stringstream debugDraw;
		if (MyFunctions->checkCollision(Enemy1->_enemyPosition->X, Enemy1->_enemyPosition->Y, Enemy1->_enemySourceRect->Width, Enemy1->_enemySourceRect->Height, Player1->_playerPosition->X, Player1->_playerPosition->Y, Player1->_playerSourceRect->Width, Player1->_playerSourceRect->Height))
		{
			debugDraw << "Is Player Colliding: True";
		}
		else
		{
			debugDraw << "Is Player Colliding: False";
		}
		Vector2* debugDrawPos = new Vector2(0, 64);
		SpriteBatch::DrawString(debugDraw.str().c_str(), debugDrawPos, Color::White);
		SpriteBatch::EndDraw(); // Ends Drawing
}