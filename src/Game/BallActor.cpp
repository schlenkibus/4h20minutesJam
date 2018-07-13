#include "BallActor.h"

BallActor::BallActor(PhysicsWorld &w, const sf::Vector2f &pos)
        : GameActor(w, Application::get().getResourceManager().getTexture("tv/ball.png"), pos, "ball", false) {

}
