#pragma once

#include "../core/Renderer.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "../core/LazyStringTexture.hpp"

class MatchHeaderComponent {
public:
    MatchHeaderComponent(VsMode players_mode);

    void set_scores(int p1_score, int p2_score);
    void render(const Renderer& renderer, const SDL_Point& point);

private:
    LazyStringTexture scores;
    LazyStringTexture p1;
    LazyStringTexture p2;
};