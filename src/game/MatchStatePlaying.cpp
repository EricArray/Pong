
#include "MatchScene.hpp"
#include "MatchStatePlaying.hpp"
#include "MatchStatePaused.hpp"

MatchSceneAction MatchStatePlaying::on_event(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                return MatchSceneAction::Pause;
            case SDL_SCANCODE_1:
                return MatchSceneAction::GoalForP1;
            case SDL_SCANCODE_2:
                return MatchSceneAction::GoalForP2;
            default:
                return MatchSceneAction::NoAction;
        }
    } else {
        return MatchSceneAction::NoAction;
    }
}

MatchSceneAction MatchStatePlaying::on_update() {
    return MatchSceneAction::UpdateWorld;
}

void MatchStatePlaying::on_render(const Renderer&) {

}
