#pragma once

#include "S2D/S2D.h"
using namespace S2D;

class Menu
{
private:
	int screenWidth;
	int screenHeight;

	//for gaining input from peripherals
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	//start menu
	Texture2D* _startMenuTitle;
	Rect* _startMenuRectangle;
	Texture2D* _startMenuStartButton;
	Rect* _startMenuStartButtonRectangle;
	Vector2* _startButtonPos;
	Texture2D* _loadButton;
	Rect* _loadButtonRectangle;
	Vector2* _loadButtonPos;
	Texture2D* _optionsButton;
	Rect* _optionsButtonRectangle;
	Vector2* _optionsButtonPos;
	Texture2D* _startMenuBackground;
	Rect* _startMenuBackgroundRectangle;
	int _selectedBox;//the box of the start screen that is selected
	bool wIsDown = false;//used to control the main menu, if it is down, it will enable the keyup command to take away from _selectedBox
	bool sIsDown = false;//used for the same reason as wIsDown however it is used to subtract from _selectedBox
	bool aIsDown = false;
	bool dIsDown = false;
	bool _pKeyDown = false;
	Rect* _optionsMenuRectangle;
	Texture2D* _optionsMenuBackground;
	string _currentRes = "Resolution: 1024 X 768  <|>";
	Vector2* _resolutionPos;
	string _currentFullscreen = "Fullscreen: [No]";
	Vector2* _fullscreenPos;
	Rect* _optionsSelectionDrawRectangle;
	Texture2D* _optionsSelectionDraw;
	Texture2D* _applyButton;
	Rect* _applyButtonRectangle;
	Vector2* _applyButtonPos;
	Texture2D* _backButton;
	Rect* _backButtonRectangle;
	Vector2* _backButtonPos;
	Texture2D* _menuBackground;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;

	SoundEffect* menuBeep;
	bool soundOnce = true;

public:
	bool _startOfGame = true;
	bool _drawOptions = false;//if this is true, draw the options menu, not the start menu, but still keep _startOfGame as true	bool _paused;
	bool _paused = false;
	/// <summary> Destroys any data associated with the class. </summary>
	virtual ~Menu();
	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	void virtual Draw(int elapsedTime);

};