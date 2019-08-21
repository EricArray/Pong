#pragma once

#include "RenderEngine.hpp"
#include "Game.hpp"
#include "Player.hpp"

class MatchHeaderComponent {
public:
    explicit MatchHeaderComponent(const Game& game, VsMode players_mode);

    void set_scores(int p1_score, int p2_score);
    void render(const RenderEngine& renderer, int x, int y) const;

private:
    const Game& game;
    Texture scores;
    Texture p1;
    Texture p2;
};