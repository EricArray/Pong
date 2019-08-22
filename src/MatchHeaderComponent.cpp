
#include "Renderer.hpp"
#include "MatchHeaderComponent.hpp"

Texture create_scores_texture(const Game& game, int p1_score, int p2_score) {
    auto scores_text = std::to_string(p1_score) + " - " + std::to_string(p2_score);
    return game.renderer().create_text_texture(scores_text);
}

MatchHeaderComponent::MatchHeaderComponent(const Game& game, VsMode players_mode) :
    game(game),
    scores(create_scores_texture(game, 0, 0)),
    p1(game.renderer().create_text_texture(get_p1_name())),
    p2(game.renderer().create_text_texture(get_p2_name(players_mode))) {

}

void MatchHeaderComponent::set_scores(int p1_score, int p2_score) {
    this->scores = create_scores_texture(this->game, p1_score, p2_score);
}

void MatchHeaderComponent::render(const Renderer& renderer, const SDL_Point& pos) const {
    auto window_w_third = Renderer::WINDOW_W / 3;

    auto dst_third = rect(pos.x, pos.y, window_w_third, FONT_SIZE);

    renderer.render_texture(this->p1, center_rect(this->p1.size(), dst_third));
    renderer.render_texture(this->scores, center_rect(this->scores.size(), dst_third + point(window_w_third, 0)));
    renderer.render_texture(this->p2, center_rect(this->p2.size(), dst_third + point(window_w_third * 2, 0)));
}
