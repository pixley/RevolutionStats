#include "stdafx.h"
#include "display.h"
#include <iostream>
using namespace sf;
using namespace std;

//helper function for Display::Draw()
Color statColor(int stat)
{
	Uint8 red;
	Uint8 green;
	Uint8 blue = 0;
	Uint8 alpha = 255;

	//bad stats red, middling stats around yellow, good stats around green, exceptional stats cyan
	if (stat <= 0)
	{
		red = 0;
		green = 0;
		blue = 0;
		alpha = 0;
	}
	else if (stat < 100)
	{
		red = 255;
		green = 0;
	}
	else if (stat < 200)
	{
		red = 255;
		green = ((stat - 100) / 100.0f) * 255;
	}
	else if (stat == 200)
	{
		red = 255;
		green = 255;
	}
	else if (stat < 300)
	{
		red = (1 - (stat - 200) / 100.0f) * 255;
		green = 255;
	}
	else if (stat < 400)
	{
		red = 0;
		green = 255;
		blue = ((stat - 300) / 100.0f) * 255;
	}
	else
	{
		red = 0;
		green = 255;
		blue = 255;
	}

	return Color(red, green, blue, alpha);
}

Display::Display(match& bout, RenderWindow& win) : Win(win), Match(bout)
{
	if (!Consolas.loadFromFile("consola.ttf"))
		cout << "Failed to load font.\n";
	if (!BkgTex.loadFromFile("Bkg.png"))
		cout << "Failed to load background.\n";
	BkgSpr.setTexture(BkgTex);
	BkgSpr.setPosition(0, 0);

	HeaderSize = 48;
	TextSize = 32;
}

void Display::Draw()
{
	Win.draw(BkgSpr);

	//establish the text object that'll be used to draw stuff
	Text textObj("", Consolas, TextSize);

	//draw the stat header
	string leftStatHead("HP  Atk Def SpA SpD Spe");
	string rightStatHead("Spe SpD SpA Def Atk HP");

	textObj.setString(leftStatHead);
	textObj.setPosition(Vector2f(15 + 11 * 18 + 15, 68));
	textObj.setColor(Color::White);
	Win.draw(textObj);

	textObj.setString(rightStatHead);
	textObj.setPosition(Vector2f(15 + 11 * 18 + 15 + (6 * 4 - 1) * 18 + 100, 68));
	Win.draw(textObj);

	//draw combatants' names
	for (int i = 0; i < 3; i++)
	{
		//draw the blue team Pokemon's name
		textObj.setString(Match.bluePokes[i]);
		//right-justification going on here
		float blueNameWid = textObj.getLocalBounds().width;
		textObj.setPosition(15 + (11 * 18 - blueNameWid), 68 + 42 * (i + 1));
		textObj.setColor(Color::Blue);
		Win.draw(textObj);

		//draw the red team Pokemon's name
		textObj.setString(Match.redPokes[i]);
		textObj.setPosition(15 + 11 * 18 + 15 + (6 * 4 - 1) * 18 + 100 + (6 * 4 - 1) * 18 + 15, 68 + 42 * (i + 1));
		textObj.setColor(Color::Red);
		Win.draw(textObj);
	}

	//draw stats
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			//draw blue team Pokemon's stats
			textObj.setString(to_string(Match.blueStats[i][j]));
			textObj.setPosition(15 + 11 * 18 + 15 + 4 * 18 * j, 68 + 42 * (i + 1));
			textObj.setColor(statColor(Match.blueStats[i][j]));
			Win.draw(textObj);

			//draw red team Pokemon's stats
			textObj.setString(to_string(Match.redStats[i][5 - j]));
			textObj.setPosition(15 + 11 * 18 + 15 + 4 * 18 * 6 - 18 + 100 + 4 * 18 * j, 68 + 42 * (i + 1));
			textObj.setColor(statColor(Match.redStats[i][5 - j]));
			Win.draw(textObj);
		}
	}

	//draw title
	textObj.setCharacterSize(HeaderSize);
	textObj.setColor(Color::White);
	textObj.setString("RevolutionStats by Pixley");
	textObj.setPosition(15 + 11 * 18 + 15 + 4 * 18 * 6 - 18 + 50 - 337, 10);
	Win.draw(textObj);

	Win.display();
}