#pragma once

#include "RenderEngine.hpp"
#include "Game.hpp"

static const int ITEM_HEIGHT = 40;

struct HighScoreItem {
    HighScoreItem(Texture rank, Texture name, Texture winner, Texture vs_mode, Texture score_p1, Texture score_p2) :
        rank(std::move(rank)), name(std::move(name)),
        winner(std::move(winner)),
        vs_mode(std::move(vs_mode)),
        score_p1(std::move(score_p1)),
        score_p2(std::move(score_p2)) {}

    Texture rank;
    Texture name;
    Texture winner;
    Texture vs_mode;
    Texture score_p1;
    Texture score_p2;
};

class HighScoreListComponent {
public:
    explicit HighScoreListComponent(const Game& game);

    void render(const RenderEngine& re, int x, int y) const;

private:
    std::vector<HighScoreItem> items;
};