#pragma once

#include "SFPhysics.h"

using namespace sfp;

class Paddle :
    public PhysicsRectangle
{
public:
    Paddle();
    virtual void updateCallback(unsigned int deltaMS) override;
};

