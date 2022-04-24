#include "Brick.h"


Brick::Brick() : collided(false){}

void Brick::collisionCallback(PhysicsBodyCollisionResult& collision)
{
	collided = true;
}
