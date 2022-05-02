#include "Paddle.h"
#include <SFML/Window.hpp>

const float movePPMs = 1;

Paddle::Paddle():
	PhysicsRectangle()
{
	setCenter(Vector2f(400, 580));
	setSize(Vector2f(75, 20));
	getBody().setStatic(true);
}

void Paddle::updateCallback(unsigned int deltaMS)
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		Vector2f center = getCenter();
		setCenter(getCenter() - Vector2f(movePPMs * deltaMS, 0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right)) {
		setCenter(getCenter() + Vector2f(movePPMs * deltaMS, 0));
	}
	
}


