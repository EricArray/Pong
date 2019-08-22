#pragma once

#include "MatchState.hpp"
#include "OptionMenu.hpp"

class MatchStatePaused : public MatchState {
public:
    explicit MatchStatePaused();

    MatchSceneAction on_keydown(SDL_Scancode key) override;
    MatchSceneAction on_update() override;
    void on_render(const Renderer& re) override;

private:
    OptionMenu menu;
};