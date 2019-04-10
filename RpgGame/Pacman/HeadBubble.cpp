#include "HeadBubble.h"

#include <sstream>
#include <iostream>

HeadBubble::~HeadBubble()
{
	delete bubbleTexture;
	delete bubblePos;
	delete bubbleRect;
}
void HeadBubble::LoadContent()
{
	bubbleTexture = new Texture2D();
	bubbleTexture->Load("Textures/EnemyTextBox.Png", false);
	bubblePos = new Vector2(0, 0);
	bubbleRect = new Rect(0, 0, 96, 36);
}

void HeadBubble::Update(int elapsedTime)
{

}

void HeadBubble::Draw(int elapsedTime)
{
	SpriteBatch::Draw(bubbleTexture, bubblePos, bubbleRect);// Draws Bubble
	if (canDrawText)
	{
		std::stringstream sayText;
		sayText << whatToSay;
		int stringLength = whatToSay.length();
		cout << "String Length: " << stringLength << "\n";
		Vector2* DrawPosition = new Vector2((bubblePos->X + 46) - (4.5 * stringLength), bubblePos->Y + 24);
		SpriteBatch::DrawString(sayText.str().c_str(), DrawPosition, Color::Black);
	}
}