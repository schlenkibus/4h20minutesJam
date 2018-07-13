#pragma once

#include "PlayerActor.h"

class Player2Actor : public PlayerActor {
public:
    Player2Actor(PhysicsWorld &w, sf::Texture &tex, const sf::Vector2f &pos, const std::string &name);
protected:
    virtual void handleInput();
    virtual std::string getAnimDir();
};