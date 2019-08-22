#include "HighScoreListComponent.hpp"
#include "common.hpp"
#include "HighScores.hpp"

#include <string>

using namespace std::string_literals;

std::string format_date(const std::string& date) {
    auto year = date.substr(0, 4);
    auto month = date.substr(4, 2);
    auto day = date.substr(6, 2);
    return day + "/" + month + "/" + year;
}

HighScoreListComponent::HighScoreListComponent(const Game& game) {
    auto high_score_entries = load_high_score_entries();
    this->items.reserve(high_score_entries.size());
    int i = 0;
    for (auto& entry : high_score_entries) {
        auto rank = game.renderer().create_text_texture("#"s + std::to_string(i + 1));
        auto name = game.renderer().create_text_texture(entry.name);
        auto date = game.renderer().create_text_texture(format_date(entry.date));
        auto scores = game.renderer().create_text_texture(std::to_string(entry.score_p1) + " - " + std::to_string(entry.score_p2));

        this->items.emplace_back(
            std::move(rank),
            std::move(name),
            std::move(date),
            std::move(scores)
        );
        i += 1;
    }
}

void HighScoreListComponent::render(const Renderer& re, const SDL_Rect& dst) const {
    re.set_view_port(dst);

    re.render_rect(rect(0, 0, dst.w, dst.h), FORE_COLOR, std::nullopt);

    int i = 0;
    for (auto& item : this->items) {
        auto item_y = FONT_SIZE * i;
        re.render_texture(item.rank, item.rank.bounding_box() + point(25, item_y));
        re.render_texture(item.name, item.name.bounding_box() + point(75, item_y));
        re.render_texture(item.scores, item.scores.bounding_box() + point(dst.w - 400, item_y));
        re.render_texture(item.date, item.date.bounding_box() + point(dst.w - 250, item_y));
        i += 1;
    }

    re.clear_view_port();
}
