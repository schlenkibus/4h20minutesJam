//
// Created by justus on 23.01.18.
//

#include <iostream>
#include "PlayerActor.h"
#include "../GameStates/IngameState.h"
#include "../Tools/TimeUtils.h"
#include "../Tools/Tools.h"
#include <experimental/filesystem>

PlayerActor::PlayerActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name) : GameActor(w, tex, pos, name, false), m_world(w) {
}

void PlayerActor::selectTexture(size_t index) {
    m_currentFrameIndex = index;
    m_sprite.setTexture(m_textures[index]);
}

bool PlayerActor::shouldStepAnim() {
    auto curr = clock.getElapsedTime();
    if(curr.asSeconds() > m_frameLenght.asSeconds()) {
        clock.restart();
        return true;
    }
    return false;
}

void PlayerActor::playOnce() {
    playing = true;
}

bool PlayerActor::isPlaying() {
    return playing;
}

void PlayerActor::clampForce() {
    auto force = getBody()->GetLinearVelocity();
    float32 maxVelX = 80;
    float32 minVelX = -80;

    if(force.x > 0)
        force.x = std::min(maxVelX, force.x);
    else
        force.x = std::max(minVelX, force.x);

    getBody()->SetLinearVelocity(force);
}

void PlayerActor::update(double delta) {
    if(playing) {
        if (shouldStepAnim()) {
            if (m_currentFrameIndex + 1 < m_textures.size()) {
                m_currentFrameIndex++;
                selectTexture(m_currentFrameIndex);
            } else {
                m_currentFrameIndex = -1;
                playing = false;
            }
        }
    }

    handleInput();

    if(!isPlaying()) {
        playOnce();
    }

    GameActor::update(delta);
}