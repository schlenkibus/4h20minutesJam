#pragma once

#include "GameActor.h"

class BallActor : public GameActor {
public:
    BallActor(PhysicsWorld &w, const sf::Vector2f &pos);

};
