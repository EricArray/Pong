#pragma once

#include "Scene.hpp"

class NullScene : public Scene {
public:
    void on_event(Game&, const SDL_Event&) override { }
    void on_update(Game&) override { }
    void on_render(const Renderer&) override { }
};
