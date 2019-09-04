#pragma once

#include <functional>
#include <vector>
#include <SDL2/SDL.h>

class Game;
class Renderer;

class Scene {
public:
    virtual void on_event(Game& game, const SDL_Event& event) = 0;
    virtual void on_update(Game& game) = 0;
    virtual void on_render(const Renderer& renderer) = 0;

};
