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

using namespace sf;

class Bullet : public GameObject
{
private:
	CircleShape shape;
	Vector2f position;
	Vector2f vel;
	float lifeTime;
	bool hitFlag;
public:
	Bullet(Vector2f position, float dir, Texture &tex);
	virtual int update(float dt, std::vector<GameObject*> &objs);
	virtual void draw(RenderWindow &window);
	virtual int getType();
	virtual Vector2f getCenter();
	virtual void checkCollisionWith(GameObject* obj);
	virtual float getRadius();
	virtual bool getHitFlag();
	virtual int setHitFlag();
};

