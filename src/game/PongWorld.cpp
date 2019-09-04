
#include "PongWorld.hpp"
#include "Player.hpp"

const float BALL_SPEED = 6.0f;
const float PADDLE_SPEED = 8.0f;

const float FIELD_W = 30.0f;
const float FIELD_H = 15.0f;
const float BALL_RADIUS = 0.5f;
const float PADDLE_W = 0.5f;
const float PADDLE_H = 3.0f;

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

    return world.create_body(body_def, {fixture_def}, nullptr);
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

    return world.create_body(body_def, {fixture_def}, std::move(body_behavior));
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

    std::unique_ptr<BodyBehavior> body_behavior(new BodyBehaviorBall());

    return world.create_body(body_def, {fixture_def}, std::move(body_behavior));
}

b2Body* create_paddle(PhysicsWorld& world, const b2Vec2& position, float width, float height) {
    b2BodyDef body_def;
    body_def.type = b2_kinematicBody;
    body_def.position = position;

    b2PolygonShape base_shape;
    base_shape.SetAsBox(width / 2, height / 2);

    b2FixtureDef base_fixture_def;
    base_fixture_def.shape = &base_shape;
    base_fixture_def.restitution = 1.0;

    b2CircleShape top_tip_shape;
    top_tip_shape.m_radius = width / 2;
    top_tip_shape.m_p.Set(0, -height / 2);

    b2FixtureDef top_tip_fixture_def;
    top_tip_fixture_def.shape = &top_tip_shape;
    top_tip_fixture_def.restitution = 1.0;

    b2CircleShape bot_tip_shape;
    bot_tip_shape.m_radius = width / 2;
    bot_tip_shape.m_p.Set(0, height / 2);

    b2FixtureDef bot_tip_fixture_def;
    bot_tip_fixture_def.shape = &bot_tip_shape;
    bot_tip_fixture_def.restitution = 1.0;

    return world.create_body(body_def, {base_fixture_def, top_tip_fixture_def, bot_tip_fixture_def}, nullptr);
}

void pong_world_tests(PongWorld& pong_world);

PongWorld::PongWorld() {
    create_side_wall(this->physics_world, b2Vec2(FIELD_W / 2, -FIELD_H / 2), b2Vec2(FIELD_W * 2, FIELD_H));
    create_side_wall(this->physics_world, b2Vec2(FIELD_W / 2, FIELD_H * 1.5), b2Vec2(FIELD_W * 2, FIELD_H));

    create_goal(this->physics_world, b2Vec2(-FIELD_W / 2, FIELD_H / 2), b2Vec2(FIELD_W, FIELD_H), Player::P1);
    create_goal(this->physics_world, b2Vec2(FIELD_W * 1.5, FIELD_H / 2), b2Vec2(FIELD_W, FIELD_H), Player::P2);

    this->ball = create_ball(this->physics_world, BALL_RADIUS);
    this->reset_ball();

    this->paddle_p1 = create_paddle(this->physics_world, MID_L + b2Vec2(2, 0), PADDLE_W, PADDLE_H);
    this->paddle_p2 = create_paddle(this->physics_world, MID_R - b2Vec2(2, 0), PADDLE_W, PADDLE_H);

    pong_world_tests(*this);
}

std::vector<MatchSceneAction> PongWorld::update() {
    this->physics_world.update();

    std::vector<MatchSceneAction> actions;
    for (auto body : this->physics_world.get_last_collisions()) {
        actions.push_back(body->on_collision());
    }
    return actions;
}

void render_ball(const Renderer& re, const b2Vec2& zoom, b2Body* ball) {
    auto& ball_position = ball->GetPosition();
    auto render_ball_position = point(zoom.x * ball_position.x, zoom.y * ball_position.y);
    re.render_circle(render_ball_position, point(zoom.x * BALL_RADIUS, zoom.y * BALL_RADIUS), FORE_COLOR, FORE_COLOR);
}

void render_paddle(const Renderer& re, const b2Vec2& zoom, b2Body* paddle) {
    auto& pos = paddle->GetPosition();
    auto base_rect = rect(-zoom.x * PADDLE_W / 2, -zoom.y * PADDLE_H / 2, zoom.x * PADDLE_W, zoom.y * PADDLE_H);
    auto pos_offset = point(zoom.x * pos.x, zoom.y * pos.y);
    re.render_rect(base_rect + pos_offset, FORE_COLOR, FORE_COLOR);

}

void PongWorld::render(const Renderer& re, const SDL_Rect& dst) {
    b2Vec2 zoom(dst.w / FIELD_W, dst.h / FIELD_H);

    re.set_view_port(dst);

    re.render_rect(rect(0, 0, dst.w, dst.h), FORE_COLOR, FIELD_COLOR);

    auto top_half = point(zoom.x * FIELD_W / 2, 0);
    auto bottom_half = point(zoom.x * FIELD_W / 2, zoom.y * FIELD_H);
    re.render_line(top_half, bottom_half, FORE_COLOR);

    re.render_circle(point(zoom.x * FIELD_W / 2, zoom.y * FIELD_H / 2), point(zoom.x * 1, zoom.x * 1),
                     FORE_COLOR, std::nullopt);

    render_ball(re, zoom, this->ball);
    render_paddle(re, zoom, this->paddle_p1);
    render_paddle(re, zoom, this->paddle_p2);

    re.clear_view_port();
}

float get_random_ball_starting_angle() {
    auto ticks = SDL_GetTicks();
    auto angle = static_cast<int>(ticks / 10) % 180;
    angle -= 45;
    if (angle > 45) angle += 90;
    return angle * M_PI / 180;
}

void PongWorld::reset_ball() {
    auto radians = get_random_ball_starting_angle();
    auto dir = b2Vec2(std::cos(radians), std::sin(radians));

    this->ball->SetTransform(CENTER, 0);
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
        case PaddleMovement::None:
            y = 0;
            break;
        case PaddleMovement::Up:
            y = -1;
            break;
        case PaddleMovement::Down:
            y = 1;
            break;
        default:
            throw unexpected();
    }
    paddle->SetLinearVelocity(PADDLE_SPEED * b2Vec2(0, y));
}

void PongWorld::set_paddle_movement_p1(PaddleMovement paddle_movement) {
    set_paddle_movement(paddle_movement, this->paddle_p1);
}

void PongWorld::set_paddle_movement_p2(PaddleMovement paddle_movement) {
    set_paddle_movement(paddle_movement, this->paddle_p2);
}

void pong_world_tests(PongWorld&) {
    for (int i = 0; i < 1000; ++i) {
        auto radians = get_random_ball_starting_angle();

        auto in_right_triangle = -M_PI/4 <= radians && radians <= M_PI/4;
        auto in_left_triangle = M_PI*3/4 <= radians && radians <= M_PI*5/4;
        assert(in_right_triangle || in_left_triangle);
    }
}