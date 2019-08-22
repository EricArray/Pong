#pragma once

#include <SDL_scancode.h>
#include "MatchSceneAction.hpp"

class Renderer;

class MatchState {
public:
    virtual ~MatchState() = default;

    virtual MatchSceneAction on_keydown(SDL_Scancode key) = 0;
    virtual MatchSceneAction on_update() = 0;
    virtual void on_render(const Renderer& re) = 0;
};