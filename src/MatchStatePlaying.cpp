
#include "MatchScene.hpp"
#include "MatchStatePlaying.hpp"
#include "MatchStatePaused.hpp"

MatchSceneAction MatchStatePlaying::on_keydown(SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_ESCAPE:
            return MatchSceneAction::Pause;
        case SDL_SCANCODE_1:
            return MatchSceneAction::GoalForP1;
        case SDL_SCANCODE_2:
            return MatchSceneAction::GoalForP2;
        default:
            return MatchSceneAction::NoAction;
    }
}

MatchSceneAction MatchStatePlaying::on_update() {
    return MatchSceneAction::UpdateWorld;
}

void MatchStatePlaying::on_render(const RenderEngine&) {

}
