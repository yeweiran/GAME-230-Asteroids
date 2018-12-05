#include "Bullet.h"
void Bullet::update(float dt)
{
	position += velocity * dt;
	shape.setPosition(position);
	// Check for collisions.
}
void Bullet::draw(RenderWindow &window)
{
	window.draw(shape);
}