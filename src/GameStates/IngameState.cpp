#include <iostream>
#include "IngameState.h"
#include "../Tools/TimeUtils.h"
#include "../Game/genericGameObject.h"
#include "MenuGameState.h"
#include "../Game/animatedGenericGameObject.h"
#include "../Game/genericMultiAnimationGameObject.h"

IngameState::IngameState() : GameState(), m_distribution(0, 3) {
    m_world = std::make_unique<PhysicsWorld>();
    m_tvGame = std::make_unique<TvGame>(m_world.get());

    m_labels.push_back(std::make_unique<Label>(sf::Vector2f(0, 0), "mouse pos: ", [this](Label* l){
        auto pos = sf::Mouse::getPosition(Application::get().getWindow());
        l->setText(std::string("x: ") + std::to_string(pos.x) + " y: " + std::to_string(pos.y));
    }));

    Application::get().setGameState("g:r");
}

void IngameState::onMessageRecieved(std::string message) {
  
}


IngameState::~IngameState() {

}

void IngameState::update(double deltaTime) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        Application::get().installState(std::make_unique<MenuGameState>());
    }

    m_world->update(deltaTime);

    if(TimeUtils::Physics::shouldUpdatePhysics())
        m_world->updatePhysics();

    for(auto& l: m_labels) {
        l->update(deltaTime);
    }

    m_tvGame->update(deltaTime);
}

void IngameState::draw(sf::RenderWindow &window) {
    m_world->draw(window);

    m_tvGame->draw(window);
}
