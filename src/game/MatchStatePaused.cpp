
#include "MatchScene.hpp"
#include "MatchStatePaused.hpp"
#include "MainMenuScene.hpp"

MatchStatePaused::MatchStatePaused() :
    menu(
        "Match in Pause",
        {
            {"Continue", SDL_SCANCODE_ESCAPE},
            {"Quit",     SDL_SCANCODE_Q},
        }
    ) {

}

MatchSceneAction MatchStatePaused::on_event(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                return MatchSceneAction::Resume;
            case SDL_SCANCODE_Q:
                return MatchSceneAction::Quit;
            default:
                return MatchSceneAction::NoAction;
        }
    } else {
        return MatchSceneAction::NoAction;
    }
}

MatchSceneAction MatchStatePaused::on_update() {
    return MatchSceneAction::NoAction;
}

void MatchStatePaused::on_render(const Renderer& re) {
    auto dst = center_rect(point(500, 500), rect(0, 0, Renderer::WINDOW_W, Renderer::WINDOW_H));
    this->menu.render(re, dst);
}
