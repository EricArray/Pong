#include "PhysicsWorld.hpp"
#include "Game.hpp"

const int32 WORLD_VELOCITY_ITERATIONS = 10;
const int32 WORLD_POSITION_ITERATIONS = 10;

PhysicsWorld::PhysicsWorld() :
    world(b2Vec2_zero), timeStamp(1.0 / Game::FPS) {
    world.SetContactListener(this);
}

PhysicsWorld::~PhysicsWorld() {
    for (auto body = this->world.GetBodyList(); body; body = body->GetNext()) {
        void* user_data = body->GetUserData();
        if (user_data) {
            body->SetUserData(nullptr);
            auto body_behavior = static_cast<BodyBehavior*>(user_data);
            delete body_behavior;
        }
        this->world.DestroyBody(body);
    }
}

void PhysicsWorld::update() {
    this->world.Step(
        this->timeStamp,
        WORLD_VELOCITY_ITERATIONS,
        WORLD_POSITION_ITERATIONS
    );
}

b2Body*
PhysicsWorld::create_body(b2BodyDef& def, const std::vector<b2FixtureDef>& fixture_defs, std::unique_ptr<BodyBehavior> body_behavior) {
    auto body = this->world.CreateBody(&def);
    for (auto& fixture_def : fixture_defs) {
        body->CreateFixture(&fixture_def);
    }
    if (body_behavior) {
        body->SetUserData(body_behavior.release());
    }
    return body;
}

void PhysicsWorld::BeginContact(b2Contact* contact) {
    auto body_behavior_a = static_cast<BodyBehavior*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto body_behavior_b = static_cast<BodyBehavior*>(contact->GetFixtureB()->GetBody()->GetUserData());
    if (body_behavior_a) this->last_collisions.push_back(body_behavior_a);
    if (body_behavior_b) this->last_collisions.push_back(body_behavior_b);
}

std::vector<BodyBehavior*> PhysicsWorld::get_last_collisions() {
    std::vector<BodyBehavior*> temp;
    temp.swap(this->last_collisions);
    return temp;
}

