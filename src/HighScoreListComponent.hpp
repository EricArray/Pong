#pragma once

#include "Renderer.hpp"
#include "Game.hpp"

struct HighScoreItem {
    HighScoreItem(Texture rank, Texture name, Texture date, Texture scores) :
        rank(std::move(rank)),
        name(std::move(name)),
        date(std::move(date)),
        scores(std::move(scores)) {}

    Texture rank;
    Texture name;
    Texture date;
    Texture scores;
};

class HighScoreListComponent {
public:
    explicit HighScoreListComponent(const Game& game);

    void render(const Renderer& re, const SDL_Rect& dst) const;

private:
    std::vector<HighScoreItem> items;
};