#pragma once
#include <SFPhysics.h>

using namespace sfp;

class BottomBorder :
    public PhysicsRectangle // cause it has no visual representation
{

private:
    PhysicsBody& ballBody;
public:
    bool collided = false;
    BottomBorder(PhysicsBody& ballBody);
    virtual void collisionCallback(
        PhysicsBodyCollisionResult& collision) override;
};

