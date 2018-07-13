#include <iostream>
#include <thread>
#include "Application.h"
#include "Tools/TimeUtils.h"
#include "GameStates/MenuGameState.h"
#include "SFML/Network.hpp"
#include "GameStates/IngameState.h"

Application::Application() : m_window(sf::VideoMode(1366,768), "420 Jam", sf::Style::Fullscreen),
                             currentState{}, m_resourceManager{} {
}

Application& Application::get() {
    static Application theApp;
    return theApp;
}

int Application::run() {

    currentState.reset(std::make_unique<MenuGameState>().release());

    sf::Event event;
    while(m_window.isOpen()) {
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
                quit();
                return 0;
            }
        }
        update();
        m_window.clear();
        draw();
        m_window.display();
    }
}

void Application::update() {
    auto delta = TimeUtils::getDeltaTime();

    if(currentState != nullptr) {
        currentState->update(delta);
    }
}

void Application::setGameState(std::string state) {
    m_currentGameState = state;
}

std::string Application::getGameState() {
    return m_currentGameState;
}

void Application::draw() {
    if(currentState != nullptr) {
        currentState->draw(m_window);
    }
}

void Application::quit() {
    exit(0);
}

IngameState* Application::getIngameGameState() {
    if(auto ingame = dynamic_cast<IngameState*>(currentState.get())) {
        return ingame;
    }
    return nullptr;
}

std::string Application::getCurrentGameSymbol() {
    if(auto ingameState = dynamic_cast<IngameState*>(currentState.get())) {
        return "i";
    } else {
        return "";
    }
}

void Application::installState(std::unique_ptr<GameState> newState) {
    currentState.reset(newState.release());
}

sf::Vector2u Application::getWindowSize() {
    return m_window.getSize();
}

sf::RenderWindow& Application::getWindow() {
    return m_window;
}

ResourceManager& Application::getResourceManager() {
    return m_resourceManager;
}
