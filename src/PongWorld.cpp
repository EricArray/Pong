
#include "PongWorld.hpp"
#include "Player.hpp"

const float WORLD_ZOOM = 40.0f;

const float BALL_SPEED = 5.0f;
const float PADDLE_SPEED = 5.0f;

const float FIELD_W = 20.0f;
const float FIELD_H = 10.0f;
const float BALL_RADIUS = 0.5f;
const float PADDLE_W = 0.5f;
const float PADDLE_H = 3.0f;

const int RENDER_FIELD_W = static_cast<int>(FIELD_W * WORLD_ZOOM);
const int RENDER_FIELD_H = static_cast<int>(FIELD_H * WORLD_ZOOM);
const float RENDER_BALL_RADIUS = BALL_RADIUS * WORLD_ZOOM;
const int RENDER_PADDLE_W = static_cast<int>(PADDLE_W * WORLD_ZOOM);
const int RENDER_PADDLE_H = static_cast<int>(PADDLE_H * WORLD_ZOOM);

const b2Vec2 TOP_L(0, 0);
const b2Vec2 TOP_R(FIELD_W, 0);
const b2Vec2 BOT_L(0, FIELD_H);
const b2Vec2 BOT_R(FIELD_W, FIELD_H);
const b2Vec2 MID_L(0, FIELD_H / 2);
const b2Vec2 MID_R(FIELD_W, FIELD_H / 2);
const b2Vec2 CENTER(FIELD_W / 2, FIELD_H / 2);

b2Body* create_side_wall(PhysicsWorld& world, const b2Vec2& pos, const b2Vec2& size) {
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position = pos;

    b2PolygonShape shape;
    shape.SetAsBox(size.x / 2, size.y / 2);

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.restitution = 1.0;

    return world.create_body(body_def, fixture_def, nullptr);
}

b2Body* create_goal(PhysicsWorld& world, const b2Vec2& pos, const b2Vec2& size, Player goal_keeper) {
    b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position = pos;

    b2PolygonShape shape;
    shape.SetAsBox(size.x / 2, size.y / 2);

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.isSensor = true;

    std::unique_ptr<BodyBehavior> body_behavior(new BodyBehaviorGoal(goal_keeper));

    return world.create_body(body_def, fixture_def, std::move(body_behavior));
}

b2Body* create_ball(PhysicsWorld& world, float radius) {
    b2BodyDef body_def;
    body_def.type = b2_dynamicBody;
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
    fixture_def.restitution = 1.0;

    return world.create_body(body_def, fixture_def, nullptr);
}

PongWorld::PongWorld() {
    create_side_wall(this->physics_world, b2Vec2(FIELD_W / 2, -FIELD_H / 2), b2Vec2(FIELD_W * 2, FIELD_H));
    create_side_wall(this->physics_world, b2Vec2(FIELD_W / 2, FIELD_H * 1.5), b2Vec2(FIELD_W * 2, FIELD_H));

    create_goal(this->physics_world, b2Vec2(-FIELD_W / 2, FIELD_H / 2), b2Vec2(FIELD_W, FIELD_H), Player::P1);
    create_goal(this->physics_world, b2Vec2(FIELD_W * 1.5, FIELD_H / 2), b2Vec2(FIELD_W, FIELD_H), Player::P2);

    this->ball = create_ball(this->physics_world, BALL_RADIUS);
    this->reset_ball();

    this->paddle_p1 = create_paddle(this->physics_world, MID_L + b2Vec2(2, 0), PADDLE_W, PADDLE_H);
    this->paddle_p2 = create_paddle(this->physics_world, MID_R - b2Vec2(2, 0), PADDLE_W, PADDLE_H);
}

std::vector<MatchSceneAction> PongWorld::update() {
    this->physics_world.update();

    std::vector<MatchSceneAction> actions;
    for (auto body : this->physics_world.get_last_collisions()) {
        actions.push_back(body->on_collision());
    }
    return actions;
}

void PongWorld::render(const RenderEngine& re, int x, int y) {
    auto field_rect = rect(0, 0, RENDER_FIELD_W, RENDER_FIELD_H);
    auto view_port = field_rect + point(x, y);

    re.set_view_port(view_port);

    re.render_rect(field_rect, FORE_COLOR);

    auto top_half = point(RENDER_FIELD_W / 2, 0);
    auto bottom_half = point(RENDER_FIELD_W / 2, RENDER_FIELD_H);
    re.render_line(top_half, bottom_half, FORE_COLOR);

    re.render_rect(rect(RENDER_FIELD_W / 2 - 30, RENDER_FIELD_H / 2 - 30, 60, 60), FORE_COLOR);

    auto& ball_position = this->ball->GetPosition();
    auto render_ball_position = point(static_cast<int>(ball_position.x * WORLD_ZOOM),
                                      static_cast<int>(ball_position.y * WORLD_ZOOM));
    re.render_circle(render_ball_position, RENDER_BALL_RADIUS, FORE_COLOR);

    auto& p1_position = this->paddle_p1->GetPosition();
    auto base_p1_rect = rect(-RENDER_PADDLE_W / 2, -RENDER_PADDLE_H / 2, RENDER_PADDLE_W, RENDER_PADDLE_H);
    auto p1_position_offset = point(static_cast<int>(p1_position.x * WORLD_ZOOM),
                                    static_cast<int>(p1_position.y * WORLD_ZOOM));
    re.render_rect(base_p1_rect + p1_position_offset, FORE_COLOR);

    auto& p2_position = this->paddle_p2->GetPosition();
    auto base_p2_rect = rect(-RENDER_PADDLE_W / 2, -RENDER_PADDLE_H / 2, RENDER_PADDLE_W, RENDER_PADDLE_H);
    auto p2_position_offset = point(static_cast<int>(p2_position.x * WORLD_ZOOM),
                                    static_cast<int>(p2_position.y * WORLD_ZOOM));
    re.render_rect(base_p2_rect + p2_position_offset, FORE_COLOR);

    re.clear_view_port();
}

void PongWorld::reset_ball() {
    this->ball->SetTransform(CENTER, 0);

    auto ticks = SDL_GetTicks();
    auto angle = ticks % 180;
    if (angle > 90) angle += 90;
    angle -= 45;
    auto radians = angle * M_PI / 180;
    auto dir = b2Vec2(std::cos(radians), std::sin(radians));

    this->ball->SetLinearVelocity(BALL_SPEED * dir);
}

void set_paddle_movement(PaddleMovement paddle_movement, b2Body* paddle) {
    auto& pos = paddle->GetPosition();
    auto too_close_to_wall =
        (paddle_movement == PaddleMovement::Up && pos.y - PADDLE_H / 2 <= BALL_RADIUS * 2) ||
        (paddle_movement == PaddleMovement::Down && pos.y + PADDLE_H / 2 >= FIELD_H - BALL_RADIUS * 2);
    if (too_close_to_wall) {
        paddle_movement = PaddleMovement::None;
    }

    float y;
    switch (paddle_movement) {
        case PaddleMovement::None: y = 0; break;
        case PaddleMovement::Up: y = -1; break;
        case PaddleMovement::Down: y = 1; break;
        default: throw unexpected();
    }
    paddle->SetLinearVelocity(PADDLE_SPEED * b2Vec2(0, y));
}

void PongWorld::set_paddle_movement_p1(PaddleMovement paddle_movement) {
    set_paddle_movement(paddle_movement, this->paddle_p1);
}

void PongWorld::set_paddle_movement_p2(PaddleMovement paddle_movement) {
    set_paddle_movement(paddle_movement, this->paddle_p2);
}
