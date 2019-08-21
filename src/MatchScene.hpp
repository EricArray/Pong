#pragma once

#include <map>
#include "Scene.hpp"
#include "Player.hpp"
#include "MatchHeaderComponent.hpp"
#include "PongWorld.hpp"
#include "MatchSceneAction.hpp"
#include "MatchState.hpp"

class PaddleController {
public:
    virtual ~PaddleController() = default;

    virtual PaddleMovement get_movement() = 0;
};

class PaddleControllerPlayer: public PaddleController {
public:
    PaddleControllerPlayer(SDL_Scancode up, SDL_Scancode down): up(up), down(down) { }

    PaddleMovement get_movement() override {
        auto keys = SDL_GetKeyboardState(nullptr);
        if (keys[this->up] == keys[this->down]) {
            return PaddleMovement::None;
        } else if (keys[this->up]) {
            return PaddleMovement::Up;
        } else {
            return PaddleMovement::Down;
        }
    }

private:
    SDL_Scancode up;
    SDL_Scancode down;
};

class PaddleControllerComputer: public PaddleController {
public:
    PaddleControllerComputer(): start(SDL_GetTicks()) { }
    
    PaddleMovement get_movement() override {
        auto now = SDL_GetTicks();
        auto diff = now - start;
        auto normal = diff % 1200;
        if (300 <= normal && normal < 900) {
            return PaddleMovement::Down;
        } else {
            return PaddleMovement::Up;
        }
    }
    
private:
    Uint32 start;
};

class MatchScene : public Scene {
public:
    MatchScene(Game& game, VsMode vs_mode);

    void on_keydown(SDL_Scancode key) override;
    void on_update() override;
    void on_render() override;

    void goal(Player player);
    void change_state(std::unique_ptr<MatchState> new_state);

private:
    void react(MatchSceneAction action);

    VsMode vs_mode;
    int p1_score;
    int p2_score;
    PongWorld pong_world;
    MatchHeaderComponent header_component;
    std::unique_ptr<MatchState> state;
    std::unique_ptr<MatchState> next_state;
    std::unique_ptr<PaddleController> controller_p1;
    std::unique_ptr<PaddleController> controller_p2;
};
