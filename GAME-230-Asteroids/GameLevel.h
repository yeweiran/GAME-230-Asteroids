#pragma once
#include "AppState.h"
#include "GameObject.h"
#include "OverMenu.h"
#include "MainMenu.h"
#include "vector"

class GameLevel : public AppState
{
private:
	int level;
	std::vector<std::unique_ptr<GameObject>> objs;
	int lives;
	int enemiesRemaining;
public:
	GameLevel(int level);

	virtual AppState* update_state(
		float dt);
	virtual void render_frame(RenderWindow &window);
};
