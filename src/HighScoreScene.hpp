#pragma once

#include "Scene.hpp"
#include "HighScoreListComponent.hpp"
#include "OptionMenu.hpp"

class HighScoreScene : public Scene {
public:
    explicit HighScoreScene(Game& game);

    void on_keydown(SDL_Scancode key) override;

    void on_update() override;

    void on_render() override;

private:
    OptionMenu menu;
    HighScoreListComponent list_component;
};
