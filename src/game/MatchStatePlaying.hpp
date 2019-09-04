#pragma once

#include "MatchState.hpp"
#include "../core/OptionMenu.hpp"

class MatchStatePlaying : public MatchState {
public:
    MatchSceneAction on_event(const SDL_Event& event) override;
    MatchSceneAction on_update() override;
    void on_render(const Renderer& re) override;

};