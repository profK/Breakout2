#include "BottomBorder.h"

BottomBorder::BottomBorder(PhysicsBody& ballBody):
	PhysicsRectangle(Vector2f(400,597.5),Vector2f(800,5),true),
	ballBody(ballBody)
{
	
}

void BottomBorder::collisionCallback(PhysicsBodyCollisionResult& collision)
{
	if ((&collision.object1 == &ballBody) ||
		(&collision.object2 == &ballBody)) {
		collided = true;
	}
}
