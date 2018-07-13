//
// Created by jscheil on 13/07/18.
//

#include <iostream>
#include "Player2Actor.h"
#include "../Tools/TimeUtils.h"
#include "../Tools/Tools.h"
#include "../GameStates/IngameState.h"

Player2Actor::Player2Actor(PhysicsWorld &w, sf::Texture &tex, const sf::Vector2f &pos, const std::string &name)
        : PlayerActor(w, tex, pos, "dino2") {
    for(auto file: Tools::getPathListOfDirectory4(getAnimDir())) {
        sf::Texture tex;
        tex.loadFromFile(file);
        m_textures.push_back(tex);
    }
    m_frameLenght = sf::seconds(0.2);
    m_currentFrameIndex = 0;
    selectTexture(0);

}

void Player2Actor::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
        getBody()->GetLinearVelocity().y <= 3 &&
        TimeUtils::Logic::canJump()) {
        getBody()->SetLinearVelocity(b2Vec2(0, 300));
        getBody()->ApplyLinearImpulse(b2Vec2(0, 600), getBody()->GetWorldCenter(), true);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        auto p1 = m_world.getActor("ball")->getM_position().getAsSFML();
        auto p2 = getM_position().getAsSFML();
        p2.x = p2.x - 20;
        p2.y = p2.y + 50;
        auto distance = sqrt(pow((p1.x - p2.x),2)+pow((p1.y - p2.y), 2));
        if(distance < 65) {
            std::cout << "player2 :" << distance << '\n';
            auto ball = m_world.getActor("ball");
            ball->getBody()->ApplyLinearImpulse(b2Vec2(-500, 700), ball->getBody()->GetWorldCenter(), true);
        }

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        getBody()->ApplyForceToCenter(b2Vec2(-1700, 0), true);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        getBody()->ApplyForceToCenter(b2Vec2(1700, 0), true);
    }

    clampForce();
}

std::string Player2Actor::getAnimDir() {
    return "../Resources/tv/dino2/";
}
