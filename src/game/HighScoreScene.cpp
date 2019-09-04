#include <memory>

#include "MainMenuScene.hpp"
#include "HighScoreScene.hpp"
#include "Game.hpp"

HighScoreScene::HighScoreScene() :
    menu(
        "High Scores",
        {
            {"Back", SDL_SCANCODE_ESCAPE }
        }
    ),
    list_component() {

}

void HighScoreScene::on_event(Game& game, const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        game.change_scene(std::unique_ptr<Scene>(new MainMenuScene()));
    }
}

void HighScoreScene::on_update(Game&) {

}

void HighScoreScene::on_render(const Renderer& renderer) {
    this->menu.render(renderer, rect(0, 0, Renderer::WINDOW_W, 80));
    this->list_component.render(renderer, rect(0, 100, Renderer::WINDOW_W, Renderer::WINDOW_H - 100));
}
