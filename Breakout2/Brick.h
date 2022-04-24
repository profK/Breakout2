#pragma once
#include "SFPhysics.h"

using namespace sfp;

class Brick :
    public PhysicsRectangle
{

public:
    enum STATE {ACTIVE,COLLIDED,REMOVED};
    Brick();
    STATE state;
    virtual void collisionCallback(PhysicsBodyCollisionResult& collision) override;
};

