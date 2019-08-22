#pragma once

#include "MatchState.hpp"
#include "OptionMenu.hpp"

class MatchStatePlaying : public MatchState {
public:
    MatchSceneAction on_keydown(SDL_Scancode key) override;
    MatchSceneAction on_update() override;
    void on_render(const Renderer& re) override;

};