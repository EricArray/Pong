#pragma once

#include "Scene.hpp"
#include "HighScoreListComponent.hpp"
#include "LazyStringTexture.hpp"

class SaveHighScoreScene : public Scene {
public:
    explicit SaveHighScoreScene(Game& game,
                                Player winner,
                                VsMode vs_mode,
                                int score_p1, int score_p2);

    void on_keydown(SDL_Scancode key) override;

    void on_update() override;

    void on_render() override;

private:
    Player winner;
    VsMode vs_mode;
    int score_p1, score_p2;

    LazyStringTexture title_texture;
    std::string name;
    LazyStringTexture name_texture;
};
