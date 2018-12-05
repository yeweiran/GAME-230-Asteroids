#include "Asteroid.h"

Asteroid::Asteroid(Texture &tex, int type) {
	//srand((unsigned)time(NULL));
	hitFlag = false;
	int board = rand() % 4;
	Vector2f np;
	switch (board)
	{
	case 0:
		np.x = rand() % (WIDTH - 1) + 1;
		np.y = 1;		
		break;
	case 1:
		np.x = WIDTH - 1;
		np.y = rand() % (HEIGHT - 1) + 1;
		break;
	case 2:
		np.x = rand() % (WIDTH - 1) + 1;
		np.y = HEIGHT - 1;
		break;
	case 3:
		np.x = 1;
		np.y = rand() % (HEIGHT - 1) + 1;
		break;
	}
	int dir = rand() % 360;
	vel = Vector2f(cosf(((float)dir / 360) * 2 * PI), sinf(((float)dir / 360) * 2 * PI));
	switch (type)
	{
	case 3:
		radius = ASTEROIDR3;
		velv = ASTEROIDV3;
		break;
	case 2:
		radius = ASTEROIDR2;
		velv = ASTEROIDV2;
		break;
	case 1:
		radius = ASTEROIDR1;
		velv = ASTEROIDV1;
		break;
	}
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setRotation(dir);
	shape.setPosition(np);
	shape.setTexture(&tex);
}
int Asteroid::update(float dt, std::vector<GameObject*> &objs)
{

	//position += velocity * dt;
	Vector2f np = shape.getPosition() + vel * velv * dt;
	if (np.x < 0) {
		np.x = WIDTH;
	}
	if (np.x > WIDTH) {
		np.x = 0;
	}
	if (np.y < 0) {
		np.y = HEIGHT;
	}
	if (np.y > HEIGHT) {
		np.y = 0;
	}
	shape.setPosition(np);
	// Check for collisions.
	return 0;
}
void Asteroid::draw(RenderWindow &window)
{
	window.draw(shape);
}

int Asteroid::getType() {
	return ASTEROID;
}

Vector2f Asteroid::getCenter() {
	return shape.getPosition();
}

void Asteroid::checkCollisionWith(GameObject* obj) {
	if (!hitFlag) {
		Vector2f v = shape.getPosition() - obj->getCenter();
		float len = GameObject::length(v);
		//TODO    gameObj->getRadius()
	}
	

}

bool Asteroid::getHitFlag() {
	return hitFlag;
}

int Asteroid::setHitFlag() {
	hitFlag = true;
}