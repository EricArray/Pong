#pragma once

#include "Scene.hpp"
#include "HighScoreListComponent.hpp"
#include "Player.hpp"
#include "../core/LazyStringTexture.hpp"

class SaveHighScoreScene : public Scene {
public:
    SaveHighScoreScene(
        Player winner,
        VsMode vs_mode,
        int score_p1, int score_p2
    );

    void on_event(Game& game, const SDL_Event& event) override;

    void on_update(Game& game) override;

    void on_render(const Renderer& renderer) override;

private:
    Player winner;
    VsMode vs_mode;
    int score_p1, score_p2;

    LazyStringTexture title_texture;
    std::string name;
    LazyStringTexture name_texture;
};
