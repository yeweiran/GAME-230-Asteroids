#include "Asteroids.h"
void Asteroids::update(float dt)
{
	position += velocity * dt;
	shape.setPosition(position);
	// Check for collisions.
}
void Asteroids::draw(RenderWindow &window)
{
	window.draw(shape);
}