#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include "../game/MatchSceneAction.hpp"

class BodyBehavior {
public:
    virtual ~BodyBehavior() = default;
    virtual MatchSceneAction on_collision() = 0;
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