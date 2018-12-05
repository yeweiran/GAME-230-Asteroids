#include "GameLevel.h"

GameLevel::GameLevel(int level) {
	lives = 3;
	enemiesRemaining = 1;
	
	this->level = level;
	shipTex.loadFromFile("ship.png");
	asteroidTex.loadFromFile("asteroid.png");
	GameObject* starShip = new Ship(shipTex);
	objs.push_back(starShip);
	for (int i = 0; i < 5 * level; i++) {
		GameObject* asteroid = new Asteroid(asteroidTex, 3);
		objs.push_back(asteroid);
	}
}

AppState* GameLevel::update_state(float dt) {
	
	for (int i = 0; i < objs.size(); ++i)
	{
		GameObject * obj = objs[i];
		Vector2i curBucket =
			getBucket(obj->getCenter());

		if (objs[i]->update(dt, objs)) {
			objs.erase(objs.begin() + i);
			continue;
		}

		Vector2i newBucket =
			getBucket(obj->getCenter());
		if (curBucket != newBucket)
		{
			bucket_remove(curBucket, obj);
			bucket_add(newBucket, obj);
		}
		//detect_collisions(obj, newBucket);
	}

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

Vector2i GameLevel::getBucket(Vector2f pos)
{
	int col = int(pos.x / BUCKET_WIDTH);
	if (col < 0)
		col = 0;
	else if (col >= COLUMNS)
		col = COLUMNS - 1;

	int row = int(pos.y / BUCKET_HEIGHT);
	if (row < 0)
		row = 0;
	else if (row >= ROWS)
		row = ROWS - 1;

	return Vector2i(col, row);
}

void GameLevel::bucket_add(Vector2i b,GameObject* obj)
{
	std::vector<GameObject*>& v = grid[b.x][b.y];
	v.push_back(obj);
}

void GameLevel::bucket_remove(Vector2i b,GameObject* obj)
{
	std::vector<GameObject*>& v = grid[b.x][b.y];
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] == obj)
		{
			v.erase(v.begin() + i);
			break;
		}
	}
}

void GameLevel::detect_collisions(GameObject* obj,Vector2i b)
{
	int left = std::max(b.x - 1, 0);
	int right = std::min(b.x + 1, COLUMNS - 1);
	int top = std::max(b.y - 1, 0);
	int bot = std::min(b.y + 1, ROWS - 1);

	for (int bx = left; bx <= right; ++bx)
	{
		for (int by = top; by <= bot; ++by)
		{
			std::vector<GameObject*> & v = grid[bx][by];
			for (GameObject* o : v)
			{
				if (o != obj)
					obj->checkCollisionWith(o);
			}
		}
	}
}


