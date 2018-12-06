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

class PowerUp : public GameObject
{
private:
	CircleShape shape;
	Vector2f position;
	Vector2f vel;
	float velv;
	float radius;
	int type;
	bool hitFlag;
	float dir;
	Texture pu1Tex;
	Texture pu2Tex;
	Texture pu3Tex;
public:
	PowerUp(int type, Vector2f pos);
	virtual int update(float dt, std::vector<GameObject*> &objs);
	virtual void draw(RenderWindow &window);
	virtual int getType();
	virtual Vector2f getCenter();
	virtual void checkCollisionWith(GameObject* obj);
	virtual float getRadius();
	virtual bool getHitFlag();
	virtual int setHitFlag();
	int getSize();
};