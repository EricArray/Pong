#pragma once

#include "PhysicsWorld.hpp"
#include "RenderEngine.hpp"

enum class PaddleMovement {
    None,
    Up,
    Down,
};

class PongWorld {
public:
    PongWorld();

    std::vector<MatchSceneAction> update();

    void render(const RenderEngine &re, int x, int y);

    void reset_ball();
    void set_paddle_movement_p1(PaddleMovement paddle_movement);
    void set_paddle_movement_p2(PaddleMovement paddle_movement);

private:
    PhysicsWorld physics_world;
    b2Body* ball;
    b2Body* paddle_p1;
    b2Body* paddle_p2;
};