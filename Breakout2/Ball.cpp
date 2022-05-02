#include "Ball.h"

const float maxVelocity = 1.0;
Ball::Ball() : PhysicsCircle()
{

}

void Ball::collisionCallback(PhysicsBodyCollisionResult& collision)
{
	Vector2f velocity = getBody().getVelocity();
	float spdSqd = pow(velocity.x, 2) + pow(velocity.y, 2);
	if (pow(maxVelocity, 2) < spdSqd) {
		Vector2f newVelocity = velocity / (sqrt(spdSqd)) * maxVelocity;
	}

}
