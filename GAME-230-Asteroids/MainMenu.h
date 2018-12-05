#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "AppState.h"
#include "GameLevel.h"
#include "Const.h"

using namespace sf;
class MainMenu : public AppState
{
private:
	Font font;
	Text mainMenuChoice[2];
	Text MainText;
	RectangleShape currentChoiceRect;
	int currentIndex;
public:
	MainMenu();
	virtual AppState* update_state(float dt);
	virtual void render_frame(RenderWindow &window);
};

