#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "AppState.h"
#include "MainMenu.h"
#include "Const.h"

using namespace sf;

class OverMenu : public AppState
{
private:
	Font font;
	Text endMenuChoice[2];
	Text endText;
	Text scoreText;
	int score;
	Texture backTex;
	Sprite background;
	RectangleShape currentChoiceRect;
	int currentIndex;
public:
	OverMenu(int score);
	virtual AppState* update_state(float dt);
	virtual void render_frame(RenderWindow &window);
};

