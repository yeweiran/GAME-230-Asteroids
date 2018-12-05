#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "GameObject.h"
#include "Const.h"
#include "Bullet.h"

using namespace sf;

class Ship : public GameObject
{
private:
	CircleShape shape;
	Vector2f position;
	Vector2f velocity;
	float vel;
	float dir;
	float shootCD;
	Texture bulletTex;
	bool hitFlag;
public:
	Ship(Texture &tex);
	float getDir();
	Vector2f getPosition();
	virtual int update(float dt, std::vector<GameObject*> &objs);
	virtual void draw(RenderWindow &window);
	virtual int getType();
	virtual Vector2f getCenter();
	virtual void checkCollisionWith(GameObject* obj);
	bool getHitFlag();
	int setHitFlag();
};

