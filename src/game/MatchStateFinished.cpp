
#include "MatchStateFinished.hpp"

const Uint32 WINNER_TEXTURE_DISPLAY_PERIOD = 1000;

MatchStateFinished::MatchStateFinished(Player winner, VsMode vs_mode) :
    winner_texture(get_player_name(winner, vs_mode) + " WINS!"),
    ticks_created(SDL_GetTicks()) {

}

MatchSceneAction MatchStateFinished::on_event(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
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
        auto& texture = this->winner_texture.get(re);
        re.render_texture(texture, center_rect(texture.size(), rect(0, 0, Renderer::WINDOW_W, Renderer::WINDOW_H)));
    }
}
