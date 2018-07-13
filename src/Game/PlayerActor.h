#pragma once

#include "GameActor.h"

class PlayerActor : public GameActor {
public:
    PlayerActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name);
    void update(double delta) override;
    void playOnce();
    bool isPlaying();
    void clampForce();

protected:
    void selectTexture(size_t index);
    virtual void handleInput() = 0;
    virtual std::string getAnimDir() {return "anus";};
    size_t m_currentFrameIndex;
    bool playing = false;
    bool shouldStepAnim();
    sf::Clock clock;
    std::vector<sf::Texture> m_textures;
    sf::Time m_frameLenght;
    PhysicsWorld& m_world;

};