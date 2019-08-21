#pragma once

#include "Scene.hpp"
#include "Player.hpp"
#include "OptionMenu.hpp"

class MainMenuScene : public Scene {
public:
    explicit MainMenuScene(Game& game);

    void on_keydown(SDL_Scancode key) override;

    void on_update() override;

    void on_render() override;

private:
    VsMode players_mode;
    OptionMenu option_menu;
};
