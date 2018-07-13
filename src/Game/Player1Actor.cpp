#include "Player1Actor.h"
#include "../Tools/Tools.h"

Player1Actor::Player1Actor(PhysicsWorld &w, sf::Texture &tex, const sf::Vector2f &pos, const std::string &name)
        : PlayerActor(w, tex, pos, "dino1") {
    for(auto file: Tools::getPathListOfDirectory4(getAnimDir())) {
        sf::Texture tex;
        tex.loadFromFile(file);
        m_textures.push_back(tex);
    }
    m_frameLenght = sf::seconds(0.2);
    m_currentFrameIndex = 0;
    selectTexture(0);
}
