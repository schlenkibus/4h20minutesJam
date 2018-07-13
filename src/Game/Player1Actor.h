#pragma once

#include <iostream>
#include "PlayerActor.h"
#include "../Tools/TimeUtils.h"
#include "../Box2D/PhysicsWorld.h"

class Player1Actor : public PlayerActor {
public:
    Player1Actor(PhysicsWorld &w, sf::Texture &tex, const sf::Vector2f &pos, const std::string &name);

protected:
    virtual std::string getAnimDir() {
        return "../Resources/tv/dino/";
    }

    virtual void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            getBody()->GetLinearVelocity().y <= 3 &&
            TimeUtils::Logic::canJump()) {
            getBody()->SetLinearVelocity(b2Vec2(0, 300));
            getBody()->ApplyLinearImpulse(b2Vec2(0, 600), getBody()->GetWorldCenter(), true);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            auto p1 = m_world.getActor("ball")->getM_position().getAsSFML();
            auto p2 = getM_position().getAsSFML();
            p2.x = p2.x + 20;
            p2.y = p2.y + 50;
            auto distance = sqrt(pow((p1.x - p2.x),2)+pow((p1.y - p2.y), 2));
            if(distance < 65) {
                std::cout << "player1: " << distance << '\n';
                auto ball = m_world.getActor("ball");
                ball->getBody()->ApplyLinearImpulse(b2Vec2(500, 700), ball->getBody()->GetWorldCenter(), true);
            }

        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            getBody()->ApplyForceToCenter(b2Vec2(-1700, 0), true);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            getBody()->ApplyForceToCenter(b2Vec2(1700, 0), true);
        }

        clampForce();
    }


};
