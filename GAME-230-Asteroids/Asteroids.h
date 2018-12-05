#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"

using namespace sf;

class Asteroids : public GameObject
{
private:
	CircleShape shape;
	Vector2f position;
	Vector2f velocity;
public:
	virtual void update(float dt);
	virtual void draw(RenderWindow &window);
};

