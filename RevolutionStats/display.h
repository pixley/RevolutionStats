#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "util.h"
#include "match.h"
using namespace sf;
using namespace std;


#ifndef DISPLAY_H
#define DISPLAY_H
class Display {
private:
	Texture BkgTex;
	Sprite BkgSpr;
	Font Consolas;
	RenderWindow& Win;
	match& Match;

	unsigned int HeaderSize;
	unsigned int TextSize;

public:
	Display(match& bout, RenderWindow& win);

	void Draw();
};

#endif