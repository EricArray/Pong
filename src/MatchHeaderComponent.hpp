#pragma once

#include "Renderer.hpp"
#include "Game.hpp"
#include "Player.hpp"

class MatchHeaderComponent {
public:
    explicit MatchHeaderComponent(const Game& game, VsMode players_mode);

    void set_scores(int p1_score, int p2_score);
    void render(const Renderer& renderer, const SDL_Point& point) const;

private:
    const Game& game;
    Texture scores;
    Texture p1;
    Texture p2;
};