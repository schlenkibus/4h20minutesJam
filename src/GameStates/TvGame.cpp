//
// Created by justus on 27.01.18.
//

#include <iostream>
#include "TvGame.h"
#include "../Tools/TimeUtils.h"
#include "IngameState.h"
#include "../Game/genericGameObject.h"
#include "../Game/BallActor.h"
#include "../Game/Player2Actor.h"
#include "../Game/Player1Actor.h"

TvGame::TvGame(PhysicsWorld *parent) : m_parent(parent) {

    m_label.push_back(std::make_unique<Label>(sf::Vector2f(1200, 90), "0"));
    m_label.push_back(std::make_unique<Label>(sf::Vector2f(100, 90), "0"));


    m_torlinks = (std::make_unique<genericGameObject>(Application::get().getIngameGameState(), Application::get().getResourceManager().getTexture("tv/tornetz.png")));
    m_torlinks->setPosition(sf::Vector2f( 40, 415));

    m_torrechts = (std::make_unique<genericGameObject>(Application::get().getIngameGameState(), Application::get().getResourceManager().getTexture("tv/tornetz.png")));
    m_torrechts->setPosition(sf::Vector2f( 1280, 415));

    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/tor_top.png"), sf::Vector2f(50, 410), std::string("tortopl"), true));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/tor_top.png"), sf::Vector2f(1300, 410), std::string("tortopr"), true));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/tor_top.png"), sf::Vector2f(65, 420), std::string("tortopl2"), true));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/tor_top.png"), sf::Vector2f(1285, 420), std::string("tortopr2"), true));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/tor_hinte.png"), sf::Vector2f(40, 500), std::string("torhitenl"), true));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/tor_hinte.png"), sf::Vector2f(1310 ,500), std::string("torhitenr"), true));

    for(auto y = -1000; y < 1150; y += 150) {
        parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/sperre.png"), sf::Vector2f(5 ,y), std::string("lsperre"+y), true));
    }

    for(auto y = -1000; y <= 1150; y += 150) {
        parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/sperre.png"), sf::Vector2f(1350 ,y), std::string("rsperre"+y), true));
    }

    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/ground.png"), sf::Vector2f(0, 670), std::string("ground"), true));
    parent->getActor("ground")->getSprite().setColor(sf::Color(0,0,0,0));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/ground.png"), sf::Vector2f(800, 670), std::string("ground1"), true));
    parent->getActor("ground1")->getSprite().setColor(sf::Color(0,0,0,0));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/ground.png"), sf::Vector2f(1600, 670), std::string("ground2"), true));
    parent->getActor("ground2")->getSprite().setColor(sf::Color(0,0,0,0));

    parent->addActor<Player1Actor>(std::make_unique<Player1Actor>(*parent, Application::get().getResourceManager().getTexture("tv/dino/dino1.png"), sf::Vector2f(300, 417), std::string("dino")));
    parent->getActor("dino1")->getBody()->SetGravityScale(6);

    parent->addActor<Player2Actor>(std::make_unique<Player2Actor>(*parent, Application::get().getResourceManager().getTexture("tv/dino2/dino1.png"), sf::Vector2f(600, 417), std::string("dino2")));
    parent->getActor("dino2")->getBody()->SetGravityScale(6);

    parent->addActor<BallActor>(std::make_unique<BallActor>(*parent, sf::Vector2f(960, 200)));
    parent->getActor("ball")->getBody()->SetGravityScale(2);

    m_floor.push_back(std::make_unique<genericGameObject>(Application::get().getIngameGameState(), Application::get().getResourceManager().getTexture("/tv/ground.png")));
    m_floor.back()->setPosition(sf::Vector2f(1800, 571));
    m_floor.push_back(std::make_unique<genericGameObject>(Application::get().getIngameGameState(), Application::get().getResourceManager().getTexture("/tv/ground.png")));
    m_floor.back()->setPosition(sf::Vector2f(800, 571));
    m_floor.push_back(std::make_unique<genericGameObject>(Application::get().getIngameGameState(), Application::get().getResourceManager().getTexture("/tv/ground.png")));
    m_floor.back()->setPosition(sf::Vector2f(0, 571));

}

int TvGame::getScore() {
    return m_score;
}

void TvGame::update(double delta) {

    if(m_torlinks->getSprite().getGlobalBounds().contains(m_parent->getActor("ball")->getSprite().getPosition())) {
        m_parent->getActor("dino1")->getBody()->SetTransform(b2Vec2(130, 300), m_parent->getActor("dino1")->getBody()->GetAngle());
        m_parent->getActor("dino2")->getBody()->SetTransform(b2Vec2(930, 300), m_parent->getActor("dino2")->getBody()->GetAngle());

        m_parent->getActor("ball")->getBody()->SetTransform(b2Vec2(200, 200), m_parent->getActor("ball")->getBody()->GetAngle());
        m_scoreRechts++;
        m_label.front()->setText(std::to_string(m_scoreRechts));

    }

    if(m_torrechts->getSprite().getGlobalBounds().contains(m_parent->getActor("ball")->getSprite().getPosition())) {
        m_parent->getActor("ball")->getBody()->SetTransform(b2Vec2(700, 200), m_parent->getActor("ball")->getBody()->GetAngle());
        m_parent->getActor("dino1")->getBody()->SetTransform(b2Vec2(130, 300), m_parent->getActor("dino1")->getBody()->GetAngle());
        m_parent->getActor("dino2")->getBody()->SetTransform(b2Vec2(930, 300), m_parent->getActor("dino2")->getBody()->GetAngle());

        m_scoreLinks++;
        m_label.back()->setText(std::to_string(m_scoreLinks));
    }

    for(auto& l: m_label) {
       l->update(delta);
    }

    if(!m_gameOver) {

    }
}

void TvGame::draw(sf::RenderWindow& window) {

    for(auto& f: m_floor)
        f->draw(window);

    for(auto& l: m_label)
        l->draw(window);

    m_torrechts->draw(window);
    m_torlinks->draw(window);
}

bool TvGame::isGameOver() {
    return m_gameOver;
}

int TvGame::getLifes() {
    return m_lifes;
}

