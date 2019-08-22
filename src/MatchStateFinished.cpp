
#include "MatchStateFinished.hpp"

const Uint32 WINNER_TEXTURE_DISPLAY_PERIOD = 1000;

MatchStateFinished::MatchStateFinished(Player winner, VsMode vs_mode) :
    winner_texture(get_player_name(winner, vs_mode) + " wins!"),
    ticks_created(SDL_GetTicks()) {

}

MatchSceneAction MatchStateFinished::on_keydown(SDL_Scancode key) {
    if (key == SDL_SCANCODE_RETURN) {
        return MatchSceneAction::CompleteMatch;
    } else {
        return MatchSceneAction::NoAction;
    }
}

MatchSceneAction MatchStateFinished::on_update() {
    return MatchSceneAction::NoAction;
}

void MatchStateFinished::on_render(const Renderer& re) {
    auto ticks_now = SDL_GetTicks();
    auto ticks_diff = this->ticks_created - ticks_now;
    auto ticks_normalized = ticks_diff % WINNER_TEXTURE_DISPLAY_PERIOD;
    if (ticks_normalized < WINNER_TEXTURE_DISPLAY_PERIOD/2) {
        re.render_texture(this->winner_texture.get(re), point(200, 200));
    }
}
