#include "Menus.h"

#include <sstream>

Menu::~Menu()
{
	delete _menuBackground;
	delete _menuRectangle;
	delete _startMenuTitle;
	delete _startMenuRectangle;
	delete _startMenuStartButton;
	delete _startMenuStartButtonRectangle;
	delete _loadButton;
	delete _loadButtonRectangle;
	delete _optionsButton;
	delete _optionsButtonRectangle;
	delete _startMenuBackground;
	delete _startMenuBackgroundRectangle;
	delete _optionsMenuRectangle;
	delete _optionsMenuBackground;
	delete _optionsSelectionDrawRectangle;
	delete _optionsSelectionDraw;
	delete _applyButton;
	delete _applyButtonRectangle;
	delete _backButton;
	delete _backButtonRectangle;
}
void Menu::LoadContent()
{
	screenWidth = (int)(Graphics::GetViewportWidth());
	screenHeight = (int)(Graphics::GetViewportHeight());
	// Set Start Menu Paramters
	_startMenuTitle = new Texture2D();
	_startMenuTitle->Load("Textures/GameTitle.Png", false);
	_startMenuRectangle = new Rect((Graphics::GetViewportWidth() * 0.5) - (115), (Graphics::GetViewportHeight() * 0.2), 230, 127);

	_startMenuStartButton = new Texture2D();
	_startMenuStartButton->Load("Textures/StartButton.Png", false);
	_startMenuStartButtonRectangle = new Rect(0.00f, 0.00f, 100, 40);
	_startButtonPos = new Vector2(430.0f, 260.0f);

	_startMenuBackground = new Texture2D();
	_startMenuBackground->Load("Textures/TitleBack.Png", false);
	_startMenuBackgroundRectangle = new Rect(0.00f, 0.00f, screenWidth, screenHeight);

	_loadButton = new Texture2D();
	_loadButton->Load("Textures/LoadButton.Png", false);
	_loadButtonRectangle = new Rect(0.00f, 0.00f, 100, 40);
	_loadButtonPos = new Vector2(430.0f, 310.0f);

	_optionsButton = new Texture2D();
	_optionsButton->Load("Textures/OptionsButton.Png", false);
	_optionsButtonRectangle = new Rect(0.00f, 0.00f, 100, 40);
	_optionsButtonPos = new Vector2(430.0f, 360.0f);

	//options menu parameters
	_optionsMenuBackground = new Texture2D();
	_optionsMenuBackground->Load("Textures/OptionsBackGround.Png", false);
	_optionsMenuRectangle = new Rect(250, 200, 500, 300);
	_optionsSelectionDraw = new Texture2D();
	_resolutionPos = new Vector2(300, 300);
	_fullscreenPos = new Vector2(300, 300);
	_optionsSelectionDraw->Load("Textures/OptionsBackGround.Png", false);
	_optionsSelectionDrawRectangle = new Rect(_resolutionPos->X * 1.18, _resolutionPos->Y - 10, 240, 30);
	_backButton = new Texture2D();
	_backButton->Load("Textures/BackButton.Png", false);
	_backButtonRectangle = new Rect(0.00f, 0.00f, 100, 40);
	_backButtonPos = new Vector2(430.0f, 360.0f);
	_applyButton = new Texture2D();
	_applyButton->Load("Textures/applyButton.Png", false);
	_applyButtonRectangle = new Rect(0.00f, 0.00f, 100, 40);
	_applyButtonPos = new Vector2(430.0f, 360.0f);

	// Set Pause Menu Paramters
	_menuBackground = new Texture2D();
	_menuBackground->Load("Textures/Transparency.png", false);
	_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_menuStringPosition = new Vector2((Graphics::GetViewportWidth() / 2.0f) + 50, Graphics::GetViewportHeight() / 3.0f);

	menuBeep = new SoundEffect();
	menuBeep->Load("Sounds/menuBeep.wav");
}

void Menu::Update(int elapsedTime)
{
	Input::MouseState* mouse = Input::Mouse::GetState();//for mouse input
	screenWidth = (int)(Graphics::GetViewportWidth());
	screenHeight = (int)(Graphics::GetViewportHeight());
	//Pause Menu control
	if (keyboardState->IsKeyDown(Input::Keys::P) && !_pKeyDown && !_startOfGame)
	{
		_pKeyDown = true;
		_paused = !_paused;
	}
	if (keyboardState->IsKeyUp(Input::Keys::P))
	{
		_pKeyDown = false;
	}

	//this controls the position of the main menu screen, it will resize depending on the window size.
	*_startMenuBackgroundRectangle =  Rect(0, 0, screenWidth, screenHeight);
	*_startMenuRectangle =  Rect((screenWidth * 0.4) - 30, (screenHeight * 0.3) - (63.5), 230, 127);
	*_startButtonPos =  Vector2((_startMenuRectangle->X + (115 - 50)), (_startMenuRectangle->Y) + 100);
	*_loadButtonPos =  Vector2((_startButtonPos->X), (_startButtonPos->Y) + 50);
	*_optionsButtonPos =  Vector2(_startButtonPos->X, (_loadButtonPos->Y) + 50);

	//options menu realigning to screen size - this is very important as options menu will change the screen size.
	*_optionsMenuRectangle =  Rect((screenWidth * 0.5) - 250, (screenHeight * 0.5) - 150, 500, 300);
	*_resolutionPos =  Vector2((_optionsMenuRectangle->X) + (_optionsMenuRectangle->Width * 0.2), (_optionsMenuRectangle->Y) + (_optionsMenuRectangle->Height * 0.3));
	*_fullscreenPos =  Vector2((_optionsMenuRectangle->X) + (_optionsMenuRectangle->Width * 0.2), (_optionsMenuRectangle->Y) + (_optionsMenuRectangle->Height * 0.4));
	*_applyButtonPos =  Vector2((_optionsMenuRectangle->X) + (_optionsMenuRectangle->Width * 0.5) - 50, (_optionsMenuRectangle->Y) + (_optionsMenuRectangle->Height * 0.5));
	*_backButtonPos =  Vector2((_optionsMenuRectangle->X) + (_optionsMenuRectangle->Width * 0.5) - 50, (_optionsMenuRectangle->Y) + (_optionsMenuRectangle->Height * 0.7));
	if (_selectedBox == 1 && _drawOptions)
	{
		*_optionsSelectionDrawRectangle =  Rect(_resolutionPos->X - 2, _resolutionPos->Y - 18, 240, 25);
		*_applyButtonRectangle =  Rect(0, 0.00f, 100, 40);
		*_backButtonRectangle =  Rect(0, 0.00f, 100, 40);
	}
	if (_selectedBox == 2 && _drawOptions)
	{
		*_optionsSelectionDrawRectangle =  Rect(_fullscreenPos->X - 2, _fullscreenPos->Y - 18, 150, 25);
		*_applyButtonRectangle =  Rect(0, 0.00f, 100, 40);
		*_backButtonRectangle =  Rect(0, 0.00f, 100, 40);
	}
	if (_selectedBox == 3 && _drawOptions)
	{
		*_optionsSelectionDrawRectangle =  Rect(_fullscreenPos->X - 2, _fullscreenPos->Y - 18, 0, 0);
		*_applyButtonRectangle =  Rect(100, 0.00f, 100, 40);
		*_backButtonRectangle =  Rect(0, 0.00f, 100, 40);
	}
	if (_selectedBox >= 4 && _drawOptions)
	{
		*_optionsSelectionDrawRectangle =  Rect(_fullscreenPos->X - 2, _fullscreenPos->Y - 18, 0, 0);
		*_applyButtonRectangle =  Rect(0, 0.00f, 100, 40);
		*_backButtonRectangle =  Rect(100, 0.00f, 100, 40);
		_selectedBox = 4;
	}

	//Start Menu Selection with keyboard
	if (keyboardState->IsKeyDown(Input::Keys::S) && !sIsDown)
	{
		_selectedBox = _selectedBox + 1;
		sIsDown = true;
		Audio::Play(menuBeep);
	}
	if (keyboardState->IsKeyUp(Input::Keys::S) && sIsDown)
	{
		sIsDown = false;
	}

	if (keyboardState->IsKeyDown(Input::Keys::W) && !wIsDown)
	{
		_selectedBox = _selectedBox - 1;
		wIsDown = true;
		Audio::Play(menuBeep);
	}
	if (keyboardState->IsKeyUp(Input::Keys::W) && wIsDown)
	{
		wIsDown = false;
	}

	//Start Menu selection with mouse
	if (!_drawOptions)
	{
		//start button
		if (mouse->X > _startButtonPos->X && mouse->X < (_startButtonPos->X + _startMenuStartButtonRectangle->Width) && mouse->Y > _startButtonPos->Y && mouse->Y < (_startButtonPos->Y + _startMenuStartButtonRectangle->Height) && _selectedBox !=1)
		{
			_selectedBox = 1;
			Audio::Play(menuBeep);
		}
		//Load Button
		else if (mouse->X > _loadButtonPos->X && mouse->X < (_loadButtonPos->X + _loadButtonRectangle->Width) && mouse->Y > _loadButtonPos->Y && mouse->Y < (_loadButtonPos->Y + _loadButtonRectangle->Height) && _selectedBox !=2)
		{
			_selectedBox = 2;
			Audio::Play(menuBeep);
		}
		//Options Button
		else if (mouse->X > _optionsButtonPos->X && mouse->X < (_optionsButtonPos->X + _optionsButtonRectangle->Width) && mouse->Y > _optionsButtonPos->Y && mouse->Y < (_optionsButtonPos->Y + _optionsButtonRectangle->Height) && _selectedBox !=3)
		{
			_selectedBox = 3;
			Audio::Play(menuBeep);
		}
	}



	//start the game with arrow keys
	if (keyboardState->IsKeyDown(Input::Keys::RETURN) && (_selectedBox == 1))
	{
		_startOfGame = false;
	}
	//start the game with mouse
	if (mouse->LeftButton == Input::ButtonState::PRESSED && mouse->X > _startButtonPos->X && mouse->X < (_startButtonPos->X + _startMenuStartButtonRectangle->Width) && mouse->Y > _startButtonPos->Y && mouse->Y < (_startButtonPos->Y + _startMenuStartButtonRectangle->Height))
	{
		_startOfGame = false;
	}

	//Select options menu with arrow keys
	if (keyboardState->IsKeyDown(Input::Keys::RETURN) && (_selectedBox == 3) && !_drawOptions)
	{
		_drawOptions = true;
		_selectedBox = 1;
	}
	//select options menu with mouse
	if (mouse->LeftButton == Input::ButtonState::PRESSED && mouse->X > _optionsButtonPos->X && mouse->X < (_optionsButtonPos->X + _optionsButtonRectangle->Width) && mouse->Y > _optionsButtonPos->Y && mouse->Y < (_optionsButtonPos->Y + _optionsButtonRectangle->Height))
	{
		_drawOptions = true;
		_selectedBox = 1;
	}


	//options menu with mouse
	if (mouse->X > _applyButtonPos->X && mouse->X < (_applyButtonPos->X + _applyButtonRectangle->Width) && mouse->Y > _applyButtonPos->Y && mouse->Y < (_applyButtonPos->Y + _applyButtonRectangle->Height) && _drawOptions && _selectedBox != 3)
	{
		_selectedBox = 3;
		Audio::Play(menuBeep);
	}
	if (mouse->X > _backButtonPos->X && mouse->X < (_backButtonPos->X + _backButtonRectangle->Width) && mouse->Y > _backButtonPos->Y && mouse->Y < (_backButtonPos->Y + _backButtonRectangle->Height) && _drawOptions && _selectedBox != 4)
	{
		_selectedBox = 4;
		Audio::Play(menuBeep);
	}
	//options menu clicking
	if (mouse->LeftButton == Input::ButtonState::PRESSED && mouse->X > _applyButtonPos->X && mouse->X < (_applyButtonPos->X + _applyButtonRectangle->Width) && mouse->Y > _applyButtonPos->Y && mouse->Y < (_applyButtonPos->Y + _applyButtonRectangle->Height) && _drawOptions)
	{
		
	}
	if (mouse->LeftButton == Input::ButtonState::PRESSED && mouse->X > _backButtonPos->X && mouse->X < (_backButtonPos->X + _backButtonRectangle->Width) && mouse->Y > _backButtonPos->Y && mouse->Y < (_backButtonPos->Y + _backButtonRectangle->Height) && _drawOptions)
	{
		_drawOptions = false;
	}





	if (_selectedBox == 1 && _drawOptions && (keyboardState->IsKeyDown(Input::Keys::A)) && !aIsDown)
	{
		aIsDown = true;
	}


	if (_selectedBox == -1)
	{
		*_startMenuStartButtonRectangle = Rect(0, 0.00f, 100, 40);
		*_loadButtonRectangle = Rect(0, 0.00f, 100, 40);
		*_optionsButtonRectangle = Rect(0, 0.00f, 100, 40);
	}

	if (_selectedBox == 1)
	{
		*_startMenuStartButtonRectangle =  Rect(100, 0.00f, 100, 40);
		*_loadButtonRectangle =  Rect(0.00f, 0.00f, 100, 40);
		*_optionsButtonRectangle =  Rect(0, 0.00f, 100, 40);
	}
	if (_selectedBox == 2)
	{
		*_loadButtonRectangle =  Rect(100, 0.00f, 100, 40);
		*_startMenuStartButtonRectangle =  Rect(0.00f, 0.00f, 100, 40);
		*_optionsButtonRectangle =  Rect(0, 0.00f, 100, 40);
	}
	if (_selectedBox == 3)
	{
		*_loadButtonRectangle =  Rect(0.00f, 0.00f, 100, 40);
		*_startMenuStartButtonRectangle =  Rect(0.00f, 0.00f, 100, 40);
		*_optionsButtonRectangle =  Rect(100, 0.00f, 100, 40);
	}
	if (_selectedBox < 1 && !(_selectedBox == -1))
	{
		_selectedBox = 1;
	}
	if (_selectedBox > 3 && !_drawOptions)
	{
		_selectedBox = 3;
	}

	/*if (_selectedBox == 1)
	{
		*_startMenuStartButtonRectangle =  Rect(100, 0.00f, 100, 40);
		*_loadButtonRectangle =  Rect(0.00f, 0.00f, 100, 40);
		*_optionsButtonRectangle =  Rect(0, 0.00f, 100, 40);
	}
	if (_selectedBox == 2)
	{
		*_loadButtonRectangle =  Rect(100, 0.00f, 100, 40);
		*_startMenuStartButtonRectangle =  Rect(0.00f, 0.00f, 100, 40);
		*_optionsButtonRectangle =  Rect(0, 0.00f, 100, 40);
	}
	if (_selectedBox == 3)
	{
		*_loadButtonRectangle =  Rect(0.00f, 0.00f, 100, 40);
		*_startMenuStartButtonRectangle =  Rect(0.00f, 0.00f, 100, 40);
		*_optionsButtonRectangle = Rect(100, 0.00f, 100, 40);
	}
	if (_selectedBox < 1)
	{
		_selectedBox = 1;
	}
	if (_selectedBox > 3 && !_drawOptions)
	{
		_selectedBox = 3;
	}*/
	//if the user presses enter with different boxes selected...
	if (_selectedBox == 2 && _drawOptions && (keyboardState->IsKeyDown(Input::Keys::RETURN)))
	{

	}
	if (_selectedBox == 3 && _drawOptions && (keyboardState->IsKeyDown(Input::Keys::RETURN)))
	{

	}
	if (_selectedBox >= 4 && _drawOptions && (keyboardState->IsKeyDown(Input::Keys::RETURN)))
	{
		_drawOptions = false;
		_startOfGame = true;
		_selectedBox = 2;
	}

}

void Menu::Draw(int elapsedTime)
{
	//draw start menu at start of the game
	if (_drawOptions)
	{
		SpriteBatch::Draw(_startMenuBackground, _startMenuBackgroundRectangle, nullptr);
		SpriteBatch::Draw(_optionsMenuBackground, _optionsMenuRectangle, nullptr);
		std::stringstream resolutionStream;//the string stream for the resolution
		resolutionStream << _currentRes;
		SpriteBatch::DrawString(resolutionStream.str().c_str(), _resolutionPos, Color::White);
		std::stringstream fullscreenStream;//the string stream for the resolution
		fullscreenStream << _currentFullscreen;
		SpriteBatch::DrawString(fullscreenStream.str().c_str(), _fullscreenPos, Color::White);
		SpriteBatch::Draw(_optionsSelectionDraw, _optionsSelectionDrawRectangle, nullptr);
		SpriteBatch::Draw(_applyButton, _applyButtonPos, _applyButtonRectangle);
		SpriteBatch::Draw(_backButton, _backButtonPos, _backButtonRectangle);
	}
	if (_startOfGame && !(_drawOptions))
	{
		SpriteBatch::Draw(_startMenuBackground, _startMenuBackgroundRectangle, nullptr);
		SpriteBatch::Draw(_startMenuTitle, _startMenuRectangle, nullptr);
		SpriteBatch::Draw(_startMenuStartButton, _startButtonPos, _startMenuStartButtonRectangle);
		SpriteBatch::Draw(_loadButton, _loadButtonPos, _loadButtonRectangle);
		SpriteBatch::Draw(_optionsButton, _optionsButtonPos, _optionsButtonRectangle);

	}
	if (!_startOfGame && !_drawOptions)
	{
		//draw pause menu if the game is paused...
		if (_paused)
		{
			std::stringstream menuStream;
			menuStream << "~Game Paused~";
			SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr);
			SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::Blue);
		}

	}
}