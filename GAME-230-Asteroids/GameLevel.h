#pragma once
#include "AppState.h"
#include "GameObject.h"
#include "OverMenu.h"
#include "MainMenu.h"
#include "Ship.h"
#include "Asteroid.h"
#include "vector"
#include <algorithm>

class GameLevel : public AppState
{
private:
	int level;
	std::vector<GameObject*> objs;
	int lives;
	int enemiesRemaining;
	Texture shipTex;
	Texture asteroidTex;
	
	std::vector<GameObject*> grid[COLUMNS][ROWS];

	Vector2i getBucket(Vector2f pos);
	void bucket_add(Vector2i b, GameObject* obj);
	void bucket_remove(Vector2i b, GameObject* obj);
	void detect_collisions(GameObject* obj,Vector2i b);
public:
	GameLevel(int level);

	virtual AppState* update_state(
		float dt);
	virtual void render_frame(RenderWindow &window);
};
