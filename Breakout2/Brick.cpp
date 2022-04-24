#include "Brick.h"


Brick::Brick() : state(ACTIVE){}

void Brick::collisionCallback(PhysicsBodyCollisionResult& collision)
{
	state = COLLIDED;
}
