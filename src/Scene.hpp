#pragma once

#include <functional>
#include <vector>
#include <SDL2/SDL.h>

class Game;

class Scene {
public:
    explicit Scene(Game& game);
    virtual ~Scene();

    void poll_event(const SDL_Event& event);

    virtual void on_keydown(SDL_Scancode key) = 0;
    virtual void on_update() = 0;
    virtual void on_render() = 0;

    [[nodiscard]] const Game& get_game() const { return this->game; }
    [[nodiscard]] Game& get_game() { return this->game; }

protected:
    Game& game;
};
