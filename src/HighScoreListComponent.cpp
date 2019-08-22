#include "HighScoreListComponent.hpp"
#include "common.hpp"

#include <string>

using namespace std::string_literals;

HighScoreListComponent::HighScoreListComponent(const Game& game) {
    auto high_score_entries = game.get_high_score_entries();
    this->items.reserve(high_score_entries.size());
    int i = 0;
    for (auto& entry : high_score_entries) {
        auto rank = game.renderer().create_text_texture("#"s + std::to_string(i + 1));
        auto name = game.renderer().create_text_texture(entry.name);
        auto winner = game.renderer().create_text_texture(get_player_name(entry.winner, entry.vs_mode));
        auto vs_mode = game.renderer().create_text_texture(get_vs_mode_name(entry.vs_mode));
        auto score_p1 = game.renderer().create_text_texture(std::to_string(entry.score_p1));
        auto score_p2 = game.renderer().create_text_texture(std::to_string(entry.score_p2));

        this->items.emplace_back(
            std::move(rank),
            std::move(name),
            std::move(winner),
            std::move(vs_mode),
            std::move(score_p1),
            std::move(score_p2)
        );
        i += 1;
    }
}

void HighScoreListComponent::render(const Renderer& re, int x, int y) const {
    re.set_view_port(rect(x, y, 800, FONT_SIZE * 10));

    re.render_rect(rect(0, 0, 800, FONT_SIZE * 10), FORE_COLOR);

    int i = 0;
    for (auto& item : this->items) {
        auto item_y = FONT_SIZE * i;
        re.render_texture(item.rank, point(0, item_y));
        re.render_texture(item.name, point(100, item_y));
        re.render_texture(item.winner, point(400, item_y));
        re.render_texture(item.vs_mode, point(500, item_y));
        re.render_texture(item.score_p1, point(700, item_y));
        re.render_texture(item.score_p2, point(750, item_y));
        i += 1;
    }

    re.clear_view_port();
}
