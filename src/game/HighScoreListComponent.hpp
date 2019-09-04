#pragma once

#include "../core/Renderer.hpp"
#include "Game.hpp"
#include "../core/LazyStringTexture.hpp"

struct HighScoreItem {
    HighScoreItem(LazyStringTexture rank, LazyStringTexture name, LazyStringTexture date, LazyStringTexture scores) :
        rank(std::move(rank)),
        name(std::move(name)),
        date(std::move(date)),
        scores(std::move(scores)) {}

    LazyStringTexture rank;
    LazyStringTexture name;
    LazyStringTexture date;
    LazyStringTexture scores;
};

class HighScoreListComponent {
public:
    HighScoreListComponent();

    void render(const Renderer& re, const SDL_Rect& dst);

private:
    std::vector<HighScoreItem> items;
};