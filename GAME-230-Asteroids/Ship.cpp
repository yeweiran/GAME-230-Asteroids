#include "Ship.h"
#include "stdlib.h"
#include "iostream"

Ship::Ship(Texture &tex) {
	hitFlag = false;
	shape.setRadius(SHIPR);
	shape.setOrigin(SHIPR, SHIPR);
	shape.setTexture(&tex);
	shape.setPosition(WIDTH / 2, HEIGHT / 2);
	dir = 0;
	vel = 0;
	shootCD = 0;
	bulletTex.loadFromFile("bullet.png");
}
int Ship::update(float dt, std::vector<GameObject*> &objs)
{
	shootCD -= dt;
	if (Keyboard::isKeyPressed(Keyboard::Space) && shootCD <= 0) {
		GameObject* bullet = new Bullet(shape.getPosition(),dir,bulletTex);
		objs.push_back(bullet);
		shootCD = SHOOTCD;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		dir = dir - 360 * dt / 2;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		dir = dir + 360 * dt / 2;
	}

	shape.setRotation(dir);
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (vel < SHIPV) {
			vel += (SHIPV * dt / 2);
		}
	}
	else {
		if (vel > 0) {
			vel -= (SHIPV * dt / 2);
		}
		if (vel < 0) {
			vel = 0;
		}
	}
	Vector2f np = shape.getPosition();
	np.x = np.x + cosf(((dir - 90) / 360) * 2 * PI) * vel * dt;
	np.y = np.y + sinf(((dir - 90) / 360) * 2 * PI) * vel * dt;
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
	return 0;
}
void Ship::draw(RenderWindow &window)
{
	window.draw(shape);
}

float Ship::getDir() {
	return dir;
}

Vector2f Ship::getPosition() {
	return shape.getPosition();
}

int Ship::getType() {
	return SHIP;
}

Vector2f Ship::getCenter() {
	return shape.getPosition();
}

void Ship::checkCollisionWith(GameObject* obj) {

}

bool Ship::getHitFlag() {
	return hitFlag;
}

int Ship::setHitFlag() {
	hitFlag = true;
}