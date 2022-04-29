#pragma once
#include <SFPhysics.h>
using namespace sfp;

class Ball :
    public PhysicsCircle
{
public:
    Ball();
    virtual void collisionCallback(PhysicsBodyCollisionResult& collision) override;
};

