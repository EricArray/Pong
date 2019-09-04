#include "MainMenuScene.hpp"
#include "HighScoreScene.hpp"
#include "Game.hpp"
#include "MatchScene.hpp"

MainMenuScene::MainMenuScene() :
    vs_mode(VsMode::VsComputer),
    option_menu(
        "Main menu",
        {
            {"Start",       SDL_SCANCODE_RETURN},
            {"Players",     SDL_SCANCODE_P},
            {"High Scores", SDL_SCANCODE_H},
            {"Quit",        SDL_SCANCODE_Q},
        }
    ),
    vs_mode_tex(get_vs_mode_name(this->vs_mode)) {

}

void MainMenuScene::on_event(Game& game, const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_RETURN: {
                game.change_scene(std::unique_ptr<Scene>(new MatchScene(this->vs_mode)));
                break;
            }
            case SDL_SCANCODE_P: {
                this->vs_mode = invert_vs_mode(this->vs_mode);
                this->vs_mode_tex = LazyStringTexture(get_vs_mode_name(this->vs_mode));
                break;
            }
            case SDL_SCANCODE_H: {
                game.change_scene(std::unique_ptr<Scene>(new HighScoreScene()));
                break;
            }
            case SDL_SCANCODE_Q: {
                game.quit();
                break;
            }
            default:;
        }
    }
}

void MainMenuScene::on_update(Game&) {

}

void MainMenuScene::on_render(const Renderer& renderer) {
    auto menu_size = point(Renderer::WINDOW_W / 2, Renderer::WINDOW_H / 3);
    auto window_rect = rect(0, 0, Renderer::WINDOW_W, Renderer::WINDOW_H);
    auto menu_dst = center_rect(menu_size, window_rect);
    this->option_menu.render(renderer, menu_dst);

    auto& vs_mode_tex = this->vs_mode_tex.get(renderer);
    auto vs_mode_dst = center_rect(vs_mode_tex.size(), rect(0, menu_dst.y + menu_dst.h, window_rect.w, vs_mode_tex.size().y));
    renderer.render_texture(vs_mode_tex, vs_mode_dst);
}
