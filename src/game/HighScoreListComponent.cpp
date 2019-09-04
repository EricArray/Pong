#include "HighScoreListComponent.hpp"
#include "../common.hpp"
#include "HighScores.hpp"

#include <string>

using namespace std::string_literals;

std::string format_date(const std::string& date) {
    auto year = date.substr(0, 4);
    auto month = date.substr(4, 2);
    auto day = date.substr(6, 2);
    return day + "/" + month + "/" + year;
}

HighScoreListComponent::HighScoreListComponent() {
    auto high_score_entries = load_high_score_entries();
    this->items.reserve(high_score_entries.size());
    int i = 0;
    for (auto& entry : high_score_entries) {
        this->items.emplace_back(
            LazyStringTexture("#"s + std::to_string(i + 1)),
            LazyStringTexture(entry.name),
            LazyStringTexture(format_date(entry.date)),
            LazyStringTexture(std::to_string(entry.score_p1) + " - " + std::to_string(entry.score_p2))
        );
        i += 1;
    }
}

void HighScoreListComponent::render(const Renderer& re, const SDL_Rect& dst) {
    re.set_view_port(dst);

    re.render_rect(rect(0, 0, dst.w, dst.h), FORE_COLOR, std::nullopt);

    int i = 0;
    for (auto& item : this->items) {
        auto item_y = FONT_SIZE * i;

        auto& rank = item.rank.get(re);
        auto& name = item.name.get(re);
        auto& scores = item.scores.get(re);
        auto& date = item.date.get(re);

        re.render_texture(rank, rank.bounding_box() + point(15, item_y));
        re.render_texture(name, name.bounding_box() + point(85, item_y));
        re.render_texture(scores, scores.bounding_box() + point(dst.w - 400, item_y));
        re.render_texture(date, date.bounding_box() + point(dst.w - 250, item_y));

        i += 1;
    }

    re.clear_view_port();
}
