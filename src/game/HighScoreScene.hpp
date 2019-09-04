#pragma once

#include "Scene.hpp"
#include "HighScoreListComponent.hpp"
#include "../core/OptionMenu.hpp"

class HighScoreScene : public Scene {
public:
    HighScoreScene();

    void on_event(Game& game, const SDL_Event& event) override;

    void on_update(Game& game) override;

    void on_render(const Renderer& renderer) override;

private:
    OptionMenu menu;
    HighScoreListComponent list_component;
};
