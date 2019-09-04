#pragma once

#include "Scene.hpp"
#include "Player.hpp"
#include "../core/OptionMenu.hpp"

class MainMenuScene : public Scene {
public:
     MainMenuScene();

    void on_event(Game& game, const SDL_Event& event) override;

    void on_update(Game& game) override;

    void on_render(const Renderer& renderer) override;

private:
    VsMode vs_mode;
    OptionMenu option_menu;
    LazyStringTexture vs_mode_tex;
};
