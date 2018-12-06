#include "Bullet.h"

Bullet::Bullet(Vector2f position, float dir, Texture &tex) {
	hitFlag = false;
	shape.setRadius(BULLETR);
	shape.setOrigin(BULLETR, BULLETR);
	shape.setRotation(dir);
	shape.setTexture(&tex);
	vel = Vector2f(cosf(((dir - 90) / 360) * 2 * PI), sinf(((dir - 90) / 360) * 2 * PI));
	shape.setPosition(position.x + vel.x * (SHIPR-10), position.y + vel.y * (SHIPR-10));
	lifeTime = 0;
}

int Bullet::update(float dt, std::vector<GameObject*> &objs)
{
	lifeTime += dt;
	if (lifeTime >= BULLETTIME) {
		return 1;
	}
	Vector2f np = shape.getPosition() + vel * (float)BULLETV * dt;
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
void Bullet::draw(RenderWindow &window)
{
	window.draw(shape);
}

int Bullet::getType() {
	return BULLET;
}

Vector2f Bullet::getCenter() {
	return shape.getPosition();
}

void Bullet::checkCollisionWith(GameObject* obj) {

}

bool Bullet::getHitFlag() {
	return hitFlag;
}

int Bullet::setHitFlag() {
	hitFlag = true;
	return 0;
}

float Bullet::getRadius() {
	return BULLETR;
}