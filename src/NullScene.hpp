#pragma once

#include "Scene.hpp"

class NullScene : public Scene {
public:
    using Scene::Scene;

    void on_keydown(SDL_Scancode) override { }
    void on_update() override { }
    void on_render() override { }
};
