#include "Asteroid.h"

Asteroid::Asteroid(Texture &tex, int type, Vector2f pos, int level) {
	//srand((unsigned)time(NULL));
	hitFlag = false;
	Vector2f np;
	int board = rand() % 4;
	int dir = rand() % 360;
	vel = Vector2f(cosf(((float)dir / 360) * 2 * PI), sinf(((float)dir / 360) * 2 * PI));
	switch (type)
	{
	case 3:
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
		radius = ASTEROIDR3;
		velv = ASTEROIDV3 + level * 10;
		break;
	case 2:
		np = pos;
		radius = ASTEROIDR2;
		velv = ASTEROIDV2 + level * 10;
		break;
	case 1:
		np = pos;
		radius = ASTEROIDR1;
		velv = ASTEROIDV1 + level * 10;
		break;
	}
	this->type = type;
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
	if (!hitFlag && !obj->getHitFlag()) {
		Vector2f v = shape.getPosition() - obj->getCenter();
		float len = GameObject::length(v);
		Ship* ship;
		if (len <= (radius + obj->getRadius() - 5)) {
			switch (obj->getType())
			{
			case SHIP:
				ship = (Ship*)obj;
				if (!ship->getInviFlag()) {
					if (ship->getShieldFlag()) {
						setHitFlag();
						ship->loseShield();
					}
					else {
						obj->setHitFlag();
					}
				}
				break;
			case BULLET:
				if (((Bullet*)obj)->getBulletType() == PCBULLET) {
					setHitFlag();
					obj->setHitFlag();
				}				
				break;
			case ASTEROID:
				vel = Vector2f(v.x / len, v.y / len);
				break;
			}
		}
	}
	
}

bool Asteroid::getHitFlag() {
	return hitFlag;
}

int Asteroid::setHitFlag() {
	hitFlag = true;
	return 0;
}

float Asteroid::getRadius() {
	return radius;
}

int Asteroid::getSize() {
	return type;
}