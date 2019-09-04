#pragma once

#include <SDL2/SDL.h>
#include "MatchSceneAction.hpp"

class Renderer;

class MatchState {
public:
    virtual ~MatchState() = default;

    virtual MatchSceneAction on_event(const SDL_Event& event) = 0;
    virtual MatchSceneAction on_update() = 0;
    virtual void on_render(const Renderer& re) = 0;
};