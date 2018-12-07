#include "GameLevel.h"

GameLevel::GameLevel(int level, int lives, int score) {
	this->lives = lives;
	enemiesRemaining = 0;
	shootCD = 0;
	alienCD = 3;
	tempCD = SHOOTCD;
	soundFlag = false;
	aliencrashFlag = false;
	levelTextTime = 2;
	alienFlag = true;
	this->score = score;
	this->level = level;
	font.loadFromFile("font.ttf");
	shipTex.loadFromFile("ship.png");
	asteroidTex.loadFromFile("asteroid.png");
	bulletTex.loadFromFile("bullet.png");
	crashTex.loadFromFile("crash.png");
	ufocrashTex.loadFromFile("ufocrash.png");
	ufobulletTex.loadFromFile("ufobullet.png");
	fireBuf.loadFromFile("fire.wav");
	explodeBuf.loadFromFile("explode.wav");
	crashBuf.loadFromFile("crash.wav");
	buffBuf.loadFromFile("buff.wav");
	winBuf.loadFromFile("win.wav");
	winSound.setBuffer(winBuf);
	fireSound.setBuffer(fireBuf);
	buffSound.setBuffer(buffBuf);
	explodeSound.setBuffer(explodeBuf);
	crashSound.setBuffer(crashBuf);

	winSound.play();

	liveText.setFont(font);
	liveText.setCharacterSize(50);
	liveText.setString("Lives: " + std::to_string(this->lives));
	liveText.setFillColor(Color::White);
	liveText.setPosition(20, 0);

	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setString("Scores: " + std::to_string(this->score));
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(WIDTH - 450, 0);

	mainText.setFont(font);
	mainText.setCharacterSize(100);
	mainText.setString("LEVEL " + std::to_string(level));
	mainText.setFillColor(Color::Black);
	mainText.setPosition(400, 300);
	shape.setRadius(SHIPR);
	shape.setOrigin(SHIPR, SHIPR);
	shape.setTexture(&crashTex);
	shape.setPosition(-500,-500);
	ufoshape.setRadius(UFOR);
	ufoshape.setOrigin(UFOR, UFOR);
	ufoshape.setTexture(&ufocrashTex);
	ufoshape.setPosition(-500, -500);
	GameObject* starShip = new Ship(shipTex);
	objs.push_back(starShip);
	for (int i = 0; i < 3 * level; i++) {
		GameObject* asteroid = new Asteroid(asteroidTex, 3, Vector2f(0,0),this->level);
		objs.push_back(asteroid);
		enemiesRemaining++;
	}
	for (int i = 0; i < objs.size(); ++i) {
		GameObject * obj = objs[i];
		Vector2i curBucket =
			getBucket(obj->getCenter());
		bucket_add(curBucket, obj);
	}
	if (!backTex.loadFromFile("galaxy.jpg"))
	{
		exit(0);
	}
	else
	{
		Vector2u TextureSize = backTex.getSize(); //Get size of texture.
		Vector2u WindowSize = Vector2u(WIDTH, HEIGHT);             //Get size of window.
		float ScaleX = (float)WindowSize.x / TextureSize.x;
		float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.
		background.setTexture(backTex);
		background.setScale(ScaleX, ScaleY);      //Set scale.  
	}
}

AppState* GameLevel::update_state(float dt) {
	levelTextTime -= dt;
	if (lives <= 0 && crashSound.getStatus() != SoundSource::Playing) {
		gc();
		return new OverMenu(score);
	}
		
	if (enemiesRemaining <= 0) {
		gc();
		return new GameLevel(level + 1, lives, score);
	}
		
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		gc();
		return new MainMenu();
	}
	if (crashSound.getStatus() != SoundSource::Playing && winSound.getStatus() != SoundSource::Playing) {
		shape.setPosition(-500, -500);
		shootCD -= dt;
		if (soundFlag == true) {
			GameObject* starShip = new Ship(shipTex);
			objs.push_back(starShip);
			Vector2i tempBucket = getBucket(starShip->getCenter());
			bucket_add(tempBucket, starShip);
			soundFlag = false;
		}
		if (aliencrashFlag) {
			aliencrashTime -= dt;
			if (aliencrashTime <= 0) {
				ufoshape.setPosition(-500, -500);
				aliencrashFlag = false;
			}
		}
		for (int i = 0; i < objs.size(); ++i)
		{
			GameObject * obj = objs[i];
			Vector2i curBucket =
				getBucket(obj->getCenter());

			if (objs[i]->update(dt, objs) || objs[i]->getHitFlag()) {
				int size;
				Vector2i tempBucket;
				switch (objs[i]->getType())
				{
				case ASTEROID:
					explodeSound.play();
					enemiesRemaining--;
					size = ((Asteroid*)(objs[i]))->getSize();
					score += (5 - size) * 20;
					if (size > 1) {
						int dir = rand() % 360;
						Vector2f vel = Vector2f(cosf(((float)dir / 360) * 2 * PI), sinf(((float)dir / 360) * 2 * PI));
						GameObject* subAsteroid1 = new Asteroid(asteroidTex, size - 1, objs[i]->getCenter() + vel * 25.f * (float)(size - 1),level);
						GameObject* subAsteroid2 = new Asteroid(asteroidTex, size - 1, objs[i]->getCenter() - vel * 25.f * (float)(size - 1),level);
						objs.push_back(subAsteroid1);
						objs.push_back(subAsteroid2);
						tempBucket = getBucket(subAsteroid1->getCenter());
						bucket_add(curBucket, subAsteroid1);
						tempBucket = getBucket(subAsteroid2->getCenter());
						bucket_add(curBucket, subAsteroid2);
						enemiesRemaining += 2;
					}
					else if (size == 1) {
						int puType = rand() % 10;
						if (puType < 3) {
							int dir = rand() % 360;

							Vector2f vel = Vector2f(cosf(((float)dir / 360) * 2 * PI), sinf(((float)dir / 360) * 2 * PI));
							GameObject* powerup = new PowerUp(puType, objs[i]->getCenter());
							objs.push_back(powerup);
							tempBucket = getBucket(powerup->getCenter());
							bucket_add(curBucket, powerup);
						}
						else if (puType == 7 && alienFlag) {
							GameObject* ufo = new UFO(obj->getCenter());
							objs.push_back(ufo);
							Vector2i tempBucket = getBucket(ufo->getCenter());
							bucket_add(tempBucket, ufo);
							enemiesRemaining++;
							alienFlag = false;
						}
					}
					break;
				case SHIP: {
					crashSound.play();
					shape.setPosition(obj->getCenter());
					soundFlag = true;
					lives--;
				}
						   break;
				case POWERUP: {
					buffSound.play();
					for (int temp = 0; temp < objs.size(); ++temp) {
						if (objs[temp]->getType() == SHIP) {
							Ship* ship = (Ship*)(objs[temp]);
							switch (((PowerUp*)(objs[i]))->getSize())
							{
							case RAPIDFIRE:
								if (tempCD >= 0.05) {
									tempCD -= 0.02;
								}
								break;
							case SHIELD:
								ship->getShield();
								break;
							case INVINCIBILE:
								ship->setInviTiem(5);
								break;
							}
						}
					}
				}
							  break;
				case ALIEN:
					score += 100;
					explodeSound.play();
					ufoshape.setPosition(obj->getCenter());
					aliencrashFlag = true;
					aliencrashTime = 0.8;
					enemiesRemaining--;
					alienFlag = true;
					break;
				}
				objs.erase(objs.begin() + i);
				bucket_remove(curBucket, obj);
				continue;
			}

			Vector2i newBucket =
				getBucket(obj->getCenter());
			if (curBucket != newBucket)
			{
				bucket_remove(curBucket, obj);
				bucket_add(newBucket, obj);
			}
			detect_collisions(obj, newBucket);
		}

		if (Keyboard::isKeyPressed(Keyboard::Space) && shootCD <= 0) {
			fireSound.play();
			for (int i = 0; i < objs.size(); ++i) {
				if (objs[i]->getType() == SHIP) {
					Ship* ship = (Ship*)(objs[i]);
					GameObject* bullet = new Bullet(ship->getCenter(), ship->getDir(), bulletTex,PCBULLET);
					objs.push_back(bullet);
					Vector2i tempBucket = getBucket(bullet->getCenter());
					bucket_add(tempBucket, bullet);
					shootCD = tempCD;
				}
			}
		}

		if (!alienFlag) {
			alienCD-=dt;
			if (alienCD <= 0) {
				Ship* ship = nullptr;
				UFO* ufo;
				for (int i = 0; i < objs.size(); ++i) {
					if (objs[i]->getType() == SHIP) {
						ship = (Ship*)(objs[i]);
					}
					if (objs[i]->getType() == ALIEN) {
						ufo = (UFO*)(objs[i]);
					}
				}
				if (ship != nullptr) {
					Vector2f a = ship->getCenter() - ufo->getCenter();
					float d = atan2f(a.y, a.x) * 180 / PI + 90;
					GameObject* bullet = new Bullet(ufo->getCenter(), d, ufobulletTex, ALIENBULLET);
					objs.push_back(bullet);
					Vector2i tempBucket = getBucket(bullet->getCenter());
					bucket_add(tempBucket, bullet);
					alienCD = ALIENCD;
				}				
			}
		}

		liveText.setString("Lives: " + std::to_string(lives));
		scoreText.setString("Scores: " + std::to_string(score));
		
	}
	return nullptr;
	
}

void GameLevel::render_frame(RenderWindow &window) {
	window.clear();
	window.draw(background);
	
	for (int i = 0; i < objs.size(); ++i)
		objs[i]->draw(window);
	if (levelTextTime >= 0) {
		window.draw(mainText);
	}
	window.draw(liveText);
	window.draw(scoreText);
	window.draw(ufoshape);
	window.draw(shape);
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

void GameLevel::gc() {
	objs.clear();
	objs.shrink_to_fit();
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLUMNS; c++) {
			grid[c][r].clear();
			grid[c][r].shrink_to_fit();
		}
	}
}

bool GameLevel::getEndFlag() {
	return endFlag;
}
