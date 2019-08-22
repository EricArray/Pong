
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

int position_centered_in(int source_width, int dest_width) {
    return (dest_width - source_width) / 2;
}

void MatchHeaderComponent::render(const Renderer& renderer, const SDL_Point& pos) const {
    auto window_third = Renderer::WINDOW_W / 3;

    auto p1_x = position_centered_in(this->p1.width(), window_third);
    auto score_x = window_third + position_centered_in(this->scores.width(), window_third);
    auto p2_x = window_third * 2 + position_centered_in(this->p2.width(), window_third);

    renderer.render_texture(this->p1, pos + point(p1_x, 0));
    renderer.render_texture(this->scores, pos + point(score_x, 0));
    renderer.render_texture(this->p2, pos + point(p2_x, 0));
}
