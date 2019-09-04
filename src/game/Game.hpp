#pragma once

#include <memory>
#include "Scene.hpp"
#include "../core/Renderer.hpp"
#include "../core/Sdl.hpp"
#include "../core/PhysicsWorld.hpp"
#include "../core/Mixer.hpp"

class Game {
public:
    static const int FPS;
    static const int WINNING_SCORE;

    Game();

    void start();
    void quit();

    void change_scene(std::unique_ptr<Scene> new_next_scene);

    [[nodiscard]] const Renderer& renderer() const {
        return this->_renderer;
    }

    [[nodiscard]] const Mixer& mixer() const {
        return this->_mixer;
    }

private:
    void main_loop();

    void check_next_scene();
    void poll_events();
    void update_logic();
    void render();

    Sdl sdl;
    Renderer _renderer;
    Mixer _mixer;
    bool running;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Scene> next_scene;
};
