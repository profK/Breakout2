#pragma once
#include "SFPhysics.h"

using namespace sfp;

class Brick :
    public PhysicsRectangle
{

public:
    Brick();
    bool collided;
    virtual void collisionCallback(PhysicsBodyCollisionResult& collision) override;
};

