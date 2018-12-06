#include "PowerUp.h"

PowerUp::PowerUp(int type, Vector2f pos) {
	hitFlag = false;
	pu1Tex.loadFromFile("powerup1.png");
	pu2Tex.loadFromFile("powerup2.png");
	pu3Tex.loadFromFile("powerup3.png");
	int board = rand() % 4;
	dir = rand() % 360;
	vel = Vector2f(cosf(((float)dir / 360) * 2 * PI), sinf(((float)dir / 360) * 2 * PI));
	velv = POWERUPV;
	this->type = type;
	shape.setRadius(POWERUPR);
	shape.setOrigin(POWERUPR, POWERUPR);
	shape.setRotation(dir);
	shape.setPosition(pos);
	switch (type)
	{
	case RAPIDFIRE:
		shape.setTexture(&pu1Tex);
		break;
	case SHIELD:
		shape.setTexture(&pu2Tex);
		break;
	case INVINCIBILE:
		shape.setTexture(&pu3Tex);
		break;
	}
	
}
int PowerUp::update(float dt, std::vector<GameObject*> &objs) {
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
	dir = dir + 360 * dt / 2;
	shape.setRotation(dir);
	shape.setPosition(np);
	return 0;
}
void PowerUp::draw(RenderWindow &window) {
	window.draw(shape);
}
int PowerUp::getType() {
	return POWERUP;
}
Vector2f PowerUp::getCenter() {
	return shape.getPosition();
}
void PowerUp::checkCollisionWith(GameObject* obj) {

}
float PowerUp::getRadius() {
	return POWERUPR;
}
bool PowerUp::getHitFlag() {
	return hitFlag;
}
int PowerUp::setHitFlag() {
	hitFlag = true;
	return 0;
}

int PowerUp::getSize() {
	return type;
}