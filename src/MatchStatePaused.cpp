
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

MatchSceneAction MatchStatePaused::on_keydown(SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_ESCAPE: return MatchSceneAction::Resume;
        case SDL_SCANCODE_Q: return MatchSceneAction::Quit;
        default: return MatchSceneAction::NoAction;
    }
}

MatchSceneAction MatchStatePaused::on_update() {
    return MatchSceneAction::NoAction;
}

void MatchStatePaused::on_render(const Renderer& re) {
    this->menu.render(re, rect(100, 100, 500, 500));
}
