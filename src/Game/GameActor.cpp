#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "GameActor.h"
#include "../Box2D/PhysicsWorld.h"

const constexpr auto RADIAN_IN_DEGREES = 57.29577;

GameActor::GameActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name, bool staticActor) :
        m_texture{tex},
                                                                                              m_ActorName{std::move(name)},
                                                                                              m_bodyDef{}, ballShapeDef{}, m_shape{}, m_position{pos}, m_circle{} {


    //Graphics
    m_sprite.setPosition(m_position.getAsSFML());
    m_sprite.setTexture(tex);

    if(staticActor) {
        m_bodyDef.type = b2_staticBody;
    } else {
        m_bodyDef.type = b2_dynamicBody;
    }

    m_bodyDef.position.Set(m_position.getAsBox2D().x, m_position.getAsBox2D().y);
    m_body = w.getWorld()->CreateBody(&m_bodyDef);

    if(m_ActorName != "ball") {
        m_shape.SetAsBox(tex.getSize().x / 2, tex.getSize().y / 2);
        m_fixture = m_body->CreateFixture(&m_shape, 0.005f);
        m_body->SetFixedRotation(true);
        m_body->SetBullet(true);
    } else {
        m_circle.m_radius = tex.getSize().x / 2;
        ballShapeDef.shape = &m_circle;
        ballShapeDef.density = 0.04f;
        ballShapeDef.friction = 0.2f;
        ballShapeDef.restitution = 0.9f;
        m_fixture = m_body->CreateFixture(&ballShapeDef);
    }
}

GameActor::~GameActor() {
}

std::string GameActor::getName() {
    return m_ActorName;
}

void GameActor::update(double deltaTime) {
    m_position = m_body->GetPosition();
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
    m_sprite.setPosition(m_position.getAsSFML().x, m_position.getAsSFML().y);
    m_sprite.setRotation((int)(m_body->GetAngle()*180/M_1_PI) % 360);
}

void GameActor::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

b2Body* GameActor::getBody() {
    return m_body;
}

sf::Sprite& GameActor::getSprite() {
    return m_sprite;
}

const GamePosition &GameActor::getM_position() const {
    return m_position;
}
