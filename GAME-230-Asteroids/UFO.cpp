#include "UFO.h"

UFO::UFO(Vector2f pos) {
    hitFlag = false;
	
	changeTime = 5;
	changeCD = changeTime;
	changeFlag = false;
	/*shieldTex.loadFromFile("shield.png");
	shipTex.loadFromFile("ship.png");
	invishipTex.loadFromFile("inviship.png");
	thrustinviTex.loadFromFile("thrustinvi.png");
	thrustTex.loadFromFile("thrust.png");
	thrustShieldTex.loadFromFile("thrustshield.png");
	thrustBuf.loadFromFile("thrust.wav");
	thrustSound.setBuffer(thrustBuf);*/
	shipTex.loadFromFile("ufo.png");
	shape.setRadius(UFOR);
	shape.setOrigin(UFOR, UFOR);
	shape.setTexture(&shipTex);
	shape.setPosition(pos);
	dir = rand() % 360;
	vel = Vector2f(cosf(((float)dir / 360) * 2 * PI), sinf(((float)dir / 360) * 2 * PI));
	velv = UFOV;
	//shootCD = 0;
	//bulletTex.loadFromFile("bullet.png");
}
int UFO::update(float dt, std::vector<GameObject*> &objs)
{	
	changeCD -= dt;
	if (changeCD <= 0) {
		changeCD = changeTime;
		dir = rand() % 360;
		vel = Vector2f(cosf(((float)dir / 360) * 2 * PI), sinf(((float)dir / 360) * 2 * PI));
	}
	Vector2f np = shape.getPosition();
	np.x = np.x + velv * vel.x * dt;
	np.y = np.y + velv * vel.y * dt;
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
void UFO::draw(RenderWindow &window)
{
	window.draw(shape);
}

float UFO::getDir() {
	return dir;
}

Vector2f UFO::getPosition() {
	return shape.getPosition();
}

int UFO::getType() {
	return ALIEN;
}

Vector2f UFO::getCenter() {
	return shape.getPosition();
}

void UFO::checkCollisionWith(GameObject* obj) {
	if (!hitFlag && !obj->getHitFlag()) {
		Vector2f v = shape.getPosition() - obj->getCenter();
		float len = GameObject::length(v);
		if (len <= (UFOR + obj->getRadius() - 5)) {
			switch (obj->getType())
			{
			case BULLET:
				if (((Bullet*)obj)->getBulletType() == PCBULLET) {
					setHitFlag();
					obj->setHitFlag();
				}				
				break;
			}
		}
	}
}

bool UFO::getHitFlag() {
	return hitFlag;
}

int UFO::setHitFlag() {
	hitFlag = true;
	return 0;
}

float UFO::getRadius() {
	return UFOR;
}