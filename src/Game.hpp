#pragma once

#include <memory>
#include "Scene.hpp"
#include "Renderer.hpp"
#include "Sdl.hpp"
#include "PhysicsWorld.hpp"

class Game {
public:
    static const int FPS;
    static const int WINNING_SCORE;

    Game();

    void start();
    void quit();

    void change_scene(std::unique_ptr<Scene> new_next_scene);

    [[nodiscard]] const Renderer& renderer() const {
        return this->render_engine;
    }

private:
    void main_loop();

    void check_next_scene();
    void poll_events();
    void update_logic();
    void render();

    Sdl sdl;
    Renderer render_engine;
    bool running;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Scene> next_scene;
};
