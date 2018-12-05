#include "GameLevel.h"

GameLevel::GameLevel(int level) {
	
}

AppState* GameLevel::update_state(float dt) {
	for (int i = 0; i < objs.size(); ++i)
		objs[i]->update(dt);

	if (lives <= 0)
		return new OverMenu();
	if (enemiesRemaining <= 0)
		return new GameLevel(level + 1);
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		return new MainMenu();
	return nullptr;
	
}

void GameLevel::render_frame(RenderWindow &window) {
	for (int i = 0; i < objs.size(); ++i)
		objs[i]->draw(window);
}