#pragma once
#include "AppState.h"
#include "GameObject.h"
#include "OverMenu.h"
#include "MainMenu.h"
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "PowerUp.h"
#include "vector"
#include <algorithm>

class GameLevel : public AppState
{
private:
	int level;
	std::vector<GameObject*> objs;
	int lives;
	int enemiesRemaining;
	int score;
	float shootCD;
	float tempCD;
	float levelTextTime;
	Texture bulletTex;
	Texture shipTex;
	Texture asteroidTex;
	Texture crashTex;
	Text liveText;
	Text scoreText;
	Text mainText;
	Font font;
	bool soundFlag;
	Texture backTex;
	Sprite background;
	CircleShape shape;
	SoundBuffer winBuf;
	Sound winSound;
	SoundBuffer fireBuf;
	Sound fireSound;
	SoundBuffer explodeBuf;
	Sound explodeSound;
	SoundBuffer crashBuf;
	Sound crashSound;
	SoundBuffer buffBuf;
	Sound buffSound;
	std::vector<GameObject*> grid[COLUMNS][ROWS];

	Vector2i getBucket(Vector2f pos);
	void bucket_add(Vector2i b, GameObject* obj);
	void bucket_remove(Vector2i b, GameObject* obj);
	void detect_collisions(GameObject* obj,Vector2i b);
public:
	GameLevel(int level, int lives, int score);

	virtual AppState* update_state(
		float dt);
	virtual void render_frame(RenderWindow &window);
};
