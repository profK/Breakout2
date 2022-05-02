#include "BottomBorder.h"

BottomBorder::BottomBorder(PhysicsBody& ballBody):
	PhysicsRectangle(),
	ballBody(ballBody)
{
	setCenter(Vector2f(400, 597.5));
	setSize(Vector2f(800, 5));
	getBody().setStatic(true);
}

void BottomBorder::collisionCallback(PhysicsBodyCollisionResult& collision)
{
	if ((&collision.object1 == &ballBody) ||
		(&collision.object2 == &ballBody)) {
		collided = true;
	}
}
