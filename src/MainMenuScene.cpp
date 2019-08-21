#include "MainMenuScene.hpp"
#include "HighScoreScene.hpp"
#include "Game.hpp"
#include "MatchScene.hpp"

MainMenuScene::MainMenuScene(Game& game) :
    Scene(game),
    players_mode(VsMode::VsComputer),
    option_menu(
        "Main menu",
        {
            {"Start",       SDL_SCANCODE_RETURN},
            {"Players",     SDL_SCANCODE_P},
            {"High Scores", SDL_SCANCODE_H},
            {"Quit",        SDL_SCANCODE_Q},
        }
    ) {

}

void MainMenuScene::on_keydown(SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_RETURN: {
            this->game.change_scene(std::unique_ptr<Scene>(new MatchScene(this->game, this->players_mode)));
            break;
        }
        case SDL_SCANCODE_P: {
            this->players_mode = invert_vs_mode(this->players_mode);
            break;
        }
        case SDL_SCANCODE_H: {
            this->game.change_scene(std::unique_ptr<Scene>(new HighScoreScene(this->game)));
            break;
        }
        case SDL_SCANCODE_Q: {
            this->game.quit();
            break;
        }
        default:;
    }
}

void MainMenuScene::on_update() {

}

void MainMenuScene::on_render() {
    this->option_menu.render(this->game.renderer(), 0, 0);
}
