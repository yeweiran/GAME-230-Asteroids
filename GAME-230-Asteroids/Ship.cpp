#include "Ship.h"
void Ship::update(float dt)
{
	position += velocity * dt;
	shape.setPosition(position);
	// Check for collisions.
}
void Ship::draw(RenderWindow &window)
{
	window.draw(shape);
}