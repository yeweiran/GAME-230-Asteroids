#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class GameObject
{
public:
	virtual int update(float dt, std::vector<GameObject*> &objs) = 0;
	virtual void draw(RenderWindow &window) = 0;
	virtual int getType() = 0;
	virtual Vector2f getCenter() = 0;
	virtual void checkCollisionWith(GameObject* obj) = 0;
	float length(Vector2f v) {
		return sqrtf(v.x*v.x + v.y*v.y);
	}
};
