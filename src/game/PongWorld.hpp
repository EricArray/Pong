#pragma once

#include "../core/PhysicsWorld.hpp"
#include "../core/Renderer.hpp"
#include "Player.hpp"

enum class PaddleMovement {
    None,
    Up,
    Down,
};

class PongWorld {
public:
    PongWorld();

    std::vector<MatchSceneAction> update();

    void render(const Renderer &re, const SDL_Rect& dst);

    void reset_ball();
    void set_paddle_movement_p1(PaddleMovement paddle_movement);
    void set_paddle_movement_p2(PaddleMovement paddle_movement);

private:
    PhysicsWorld physics_world;
    b2Body* ball;
    b2Body* paddle_p1;
    b2Body* paddle_p2;
};

class BodyBehaviorBall: public BodyBehavior {
public:
    MatchSceneAction on_collision() override {
        return MatchSceneAction::PlayBounceSound;
    }
};

class BodyBehaviorGoal: public BodyBehavior {
public:
    explicit BodyBehaviorGoal(Player goal_keeper) : goal_keeper(goal_keeper) { }

    MatchSceneAction on_collision() override {
        switch (goal_keeper) {
            case Player::P1: return MatchSceneAction::GoalForP2;
            case Player::P2: return MatchSceneAction::GoalForP1;
            default: throw unexpected();
        }
    }

private:
    Player goal_keeper;
};
