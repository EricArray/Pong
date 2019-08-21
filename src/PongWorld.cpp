
#include "PongWorld.hpp"
#include "Player.hpp"

const float WORLD_ZOOM = 40.0f;

const float BALL_SPEED = 10.0f;

const float FIELD_WIDTH = 20.0f;
const float FIELD_HEIGHT = 10.0f;
const float BALL_RADIUS = 0.5f;
const float PADDLE_WIDTH = 0.5f;
const float PADDLE_HEIGHT = 3.0f;

const int RENDER_FIELD_WIDTH = static_cast<int>(FIELD_WIDTH * WORLD_ZOOM);
const int RENDER_FIELD_HEIGHT = static_cast<int>(FIELD_HEIGHT * WORLD_ZOOM);
const float RENDER_BALL_RADIUS = BALL_RADIUS * WORLD_ZOOM;
const int RENDER_PADDLE_WIDTH = static_cast<int>(PADDLE_WIDTH * WORLD_ZOOM);
const int RENDER_PADDLE_HEIGHT = static_cast<int>(PADDLE_HEIGHT * WORLD_ZOOM);

const b2Vec2 TOP_LEFT(0, 0);
const b2Vec2 TOP_RIGHT(FIELD_WIDTH, 0);
const b2Vec2 BOTTOM_LEFT(0, FIELD_HEIGHT);
const b2Vec2 BOTTOM_RIGHT(FIELD_WIDTH, FIELD_HEIGHT);
const b2Vec2 MIDDLE_LEFT(0, FIELD_HEIGHT / 2);
const b2Vec2 MIDDLE_RIGHT(FIELD_WIDTH, FIELD_HEIGHT / 2);
const b2Vec2 MIDDLE(FIELD_WIDTH / 2, FIELD_HEIGHT / 2);

b2Body* create_table_sensor(PhysicsWorld& world, float width, float height) {
    b2BodyDef body_def;
    body_def.type = b2_staticBody;

    b2PolygonShape shape;
    shape.SetAsBox(width, height / 2);
    shape.m_centroid.Set(0, height);

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.isSensor = true;

    std::unique_ptr<BodyBehavior> behavior(new BodyBehaviorTable());

    b2Body* body = world.create_body(body_def, fixture_def, std::move(behavior));

    shape.m_centroid.Set(0, -height);
    body->CreateFixture(&fixture_def);

    return body;
}

b2Body* create_side_border(PhysicsWorld& world, const b2Vec2& a, const b2Vec2& b) {
    b2BodyDef body_def;
    body_def.type = b2_staticBody;

    b2EdgeShape shape;
    shape.Set(a, b);

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;

    return world.create_body(body_def, fixture_def, nullptr);
}

b2Body* create_goal_border(PhysicsWorld& world, const b2Vec2& a, const b2Vec2& b, Player goal_keeper) {
    b2BodyDef body_def;
    body_def.type = b2_staticBody;

    b2EdgeShape shape;
    shape.Set(a, b);

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.isSensor = true;

    std::unique_ptr<BodyBehavior> body_behavior(new BodyBehaviorGoal(goal_keeper));

    return world.create_body(body_def, fixture_def, std::move(body_behavior));
}

b2Body* create_ball(PhysicsWorld& world, const b2Vec2& position, float radius) {
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
    body_def.position = position;
    body_def.bullet = true;
    body_def.fixedRotation = true;

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.restitution = 1.0f;
    fixture_def.friction = 0.0f;

    return world.create_body(body_def, fixture_def, nullptr);
}

b2Body* create_paddle(PhysicsWorld& world, const b2Vec2& position, float width, float height) {
    b2BodyDef body_def;
    body_def.type = b2_kinematicBody;
    body_def.position = position;

    b2PolygonShape shape;
    shape.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;

    return world.create_body(body_def, fixture_def, nullptr);
}

PongWorld::PongWorld() {
    create_table_sensor(this->physics_world, FIELD_WIDTH, FIELD_HEIGHT);

    create_side_border(this->physics_world, TOP_LEFT, TOP_RIGHT);
    create_side_border(this->physics_world, BOTTOM_LEFT, BOTTOM_RIGHT);

    create_goal_border(this->physics_world, TOP_LEFT, BOTTOM_LEFT, Player::P1);
    create_goal_border(this->physics_world, TOP_RIGHT, BOTTOM_RIGHT, Player::P2);

    this->ball = create_ball(this->physics_world, MIDDLE, BALL_RADIUS);
    this->reset_ball();

    this->paddle_p1 = create_paddle(this->physics_world, MIDDLE_LEFT + b2Vec2(0.5, 0), PADDLE_WIDTH, PADDLE_HEIGHT);
    this->paddle_p2 = create_paddle(this->physics_world, MIDDLE_RIGHT - b2Vec2(0.5, 0), PADDLE_WIDTH, PADDLE_HEIGHT);
}

std::vector<MatchSceneAction> PongWorld::update() {
    this->physics_world.update();

    std::vector<MatchSceneAction> actions;
    for (auto body : this->physics_world.get_last_collisions()) {
        actions.push_back(body->on_collision());
    }
    return actions;
}

void PongWorld::render(const RenderEngine &re, int x, int y) {
    auto field_rect = rect(0, 0, RENDER_FIELD_WIDTH, RENDER_FIELD_HEIGHT);
    auto view_port = field_rect + point(x, y);

    re.set_view_port(view_port);

    re.render_rect(field_rect, FORE_COLOR);

    auto top_half = point(RENDER_FIELD_WIDTH / 2, 0);
    auto bottom_half = point(RENDER_FIELD_WIDTH / 2, RENDER_FIELD_HEIGHT);
    re.render_line(top_half, bottom_half, FORE_COLOR);

    re.render_rect(rect(RENDER_FIELD_WIDTH / 2 - 30, RENDER_FIELD_HEIGHT / 2 - 30, 60, 60), FORE_COLOR);

    auto& ball_position = this->ball->GetPosition();
    auto render_ball_position = point(static_cast<int>(ball_position.x * WORLD_ZOOM), static_cast<int>(ball_position.y * WORLD_ZOOM));
    re.render_circle(render_ball_position, RENDER_BALL_RADIUS, FORE_COLOR);

    auto& p1_position = this->paddle_p1->GetPosition();
    auto base_p1_rect = rect(-RENDER_PADDLE_WIDTH/2, -RENDER_PADDLE_HEIGHT/2, RENDER_PADDLE_WIDTH, RENDER_PADDLE_HEIGHT);
    auto p1_position_offset = point(static_cast<int>(p1_position.x * WORLD_ZOOM), static_cast<int>(p1_position.y * WORLD_ZOOM));
    re.render_rect(base_p1_rect + p1_position_offset, FORE_COLOR);

    auto& p2_position = this->paddle_p2->GetPosition();
    auto base_p2_rect = rect(-RENDER_PADDLE_WIDTH/2, -RENDER_PADDLE_HEIGHT/2, RENDER_PADDLE_WIDTH, RENDER_PADDLE_HEIGHT);
    auto p2_position_offset = point(static_cast<int>(p2_position.x * WORLD_ZOOM), static_cast<int>(p2_position.y * WORLD_ZOOM));
    re.render_rect(base_p2_rect + p2_position_offset, FORE_COLOR);

    re.clear_view_port();
}

b2Vec2 linear_vel_of(PaddleMovement movement) {
    switch (movement) {
        case PaddleMovement::None:
            return b2Vec2_zero;
        case PaddleMovement::Up:
            return b2Vec2(0, -5);
        case PaddleMovement::Down:
            return b2Vec2(0, 5);
        default:
            throw unexpected();
    }
}

void PongWorld::reset_ball() {
    this->ball->SetTransform(MIDDLE, 0);
    
    auto ticks = SDL_GetTicks();
    auto angle = ticks % 180;
    if (angle > 90) angle += 90;
    angle -= 45;
    auto radians = angle * M_PI / 180;
    auto dir = b2Vec2(std::cos(radians), std::sin(radians));

    this->ball->SetLinearVelocity(BALL_SPEED * dir);
}

void PongWorld::set_paddle_movement_p1(PaddleMovement paddle_movement) {
    this->paddle_p1->SetLinearVelocity(linear_vel_of(paddle_movement));
}

void PongWorld::set_paddle_movement_p2(PaddleMovement paddle_movement) {
    this->paddle_p2->SetLinearVelocity(linear_vel_of(paddle_movement));
}
