#include <memory>

#include "MainMenuScene.hpp"
#include "HighScoreScene.hpp"
#include "Game.hpp"

HighScoreScene::HighScoreScene(Game& game) :
    Scene(game),
    menu(
        "High Scores",
        {
            {"Back", SDL_SCANCODE_ESCAPE }
        }
    ),
    list_component(game) {

}

void HighScoreScene::on_keydown(SDL_Scancode key) {
    if (key == SDL_SCANCODE_ESCAPE) {
        this->game.change_scene(std::unique_ptr<Scene>(new MainMenuScene(this->game)));
    }
}

void HighScoreScene::on_update() {

}

void HighScoreScene::on_render() {
    this->menu.render(this->game.renderer(), 0, 0);
    this->list_component.render(this->game.renderer(), 0, 100);
}