#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include "Player.hpp"
#include "MatchSceneAction.hpp"

class BodyBehavior {
public:
    virtual ~BodyBehavior() = default;
    virtual MatchSceneAction on_collision() = 0;
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

class PhysicsWorld: public b2ContactListener {
public:
    PhysicsWorld();
    ~PhysicsWorld() override;

    b2Body* create_body(b2BodyDef& def, const std::vector<b2FixtureDef>& fixture_defs, std::unique_ptr<BodyBehavior> body_behavior);

    void update();

    std::vector<BodyBehavior*> get_last_collisions();

private:
    void BeginContact(b2Contact* contact) override;

    b2World world;
    float32 timeStamp;
    std::vector<BodyBehavior*> last_collisions;
};