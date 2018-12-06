#include "Ship.h"
#include "stdlib.h"
#include "iostream"

Ship::Ship(Texture &tex) {
	hitFlag = false;
	shieldFlag = false;
	inviTime = 2;
	changeTime = 0;
	changeFlag = false;
	shieldTex.loadFromFile("shield.png");
	shipTex.loadFromFile("ship.png");
	invishipTex.loadFromFile("inviship.png");
	thrustinviTex.loadFromFile("thrustinvi.png");
	thrustTex.loadFromFile("thrust.png");
	thrustShieldTex.loadFromFile("thrustshield.png");
	thrustBuf.loadFromFile("thrust.wav");
	thrustSound.setBuffer(thrustBuf);
	shape.setRadius(SHIPR);
	shape.setOrigin(SHIPR, SHIPR);
	shape.setTexture(&shipTex);
	shape.setPosition(WIDTH / 2, HEIGHT / 2);
	dir = 0;
	vel = 0;
	//shootCD = 0;
	//bulletTex.loadFromFile("bullet.png");
}
int Ship::update(float dt, std::vector<GameObject*> &objs)
{
	if(inviTime >= 0) {
		inviTime -= dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		dir = dir - 360 * dt / 2;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		dir = dir + 360 * dt / 2;
	}

	shape.setRotation(dir);
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (thrustSound.getStatus() != SoundSource::Playing) {
			thrustSound.play();
		}
		if (vel < SHIPV) {
			vel += (SHIPV * dt / 2);
		}
		if (getInviFlag()) {
			shape.setTexture(&thrustinviTex);
		}
		else if (shieldFlag) {
			shape.setTexture(&thrustShieldTex);
		}
		else {
			shape.setTexture(&thrustTex);
		}		
	}
	else {
		thrustSound.stop();
		if (vel > 0) {
			vel -= (SHIPV * dt / 2);
		}
		if (vel < 0) {
			vel = 0;
		}
		if (getInviFlag()) {
			shape.setTexture(&invishipTex);
		}
		else if (shieldFlag) {
			shape.setTexture(&shieldTex);
		}
		else {
			shape.setTexture(&shipTex);
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
	if (!hitFlag && !obj->getHitFlag()) {
		Vector2f v = shape.getPosition() - obj->getCenter();
		float len = GameObject::length(v);
		if (len <= (SHIPR + obj->getRadius() - 5)) {
			switch (obj->getType())
			{
			case POWERUP:
				obj->setHitFlag();
				break;
			}
		}
	}
}

bool Ship::getHitFlag() {
	return hitFlag;
}

int Ship::setHitFlag() {
	hitFlag = true;
	return 0;
}

float Ship::getRadius() {
	return SHIPR;
}

void Ship::getShield() {
	shieldFlag = true;
	shape.setTexture(&shieldTex);
}

bool Ship::getShieldFlag() {
	return shieldFlag;
}

void Ship::setInviTiem(float time) {
	inviTime = time;
}
bool Ship::getInviFlag() {
	if (inviTime > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Ship::loseShield(){
	shieldFlag = false;
	shape.setTexture(&shipTex);
}