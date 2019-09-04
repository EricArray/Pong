
#include "../core/Renderer.hpp"
#include "MatchHeaderComponent.hpp"

LazyStringTexture create_scores_texture(int p1_score, int p2_score) {
    auto scores_text = std::to_string(p1_score) + " - " + std::to_string(p2_score);
    return LazyStringTexture(scores_text);
}

MatchHeaderComponent::MatchHeaderComponent(VsMode players_mode) :
    scores(create_scores_texture(0, 0)),
    p1(get_p1_name()),
    p2(get_p2_name(players_mode)) {

}

void MatchHeaderComponent::set_scores(int p1_score, int p2_score) {
    this->scores = create_scores_texture(p1_score, p2_score);
}

void MatchHeaderComponent::render(const Renderer& renderer, const SDL_Point& pos) {
    auto window_w_third = Renderer::WINDOW_W / 3;

    auto dst_third = rect(pos.x, pos.y, window_w_third, FONT_SIZE);

    auto& p1 = this->p1.get(renderer);
    auto& scores = this->scores.get(renderer);
    auto& p2 = this->p2.get(renderer);

    renderer.render_texture(p1, center_rect(p1.size(), dst_third));
    renderer.render_texture(scores, center_rect(scores.size(), dst_third + point(window_w_third, 0)));
    renderer.render_texture(p2, center_rect(p2.size(), dst_third + point(window_w_third * 2, 0)));
}
