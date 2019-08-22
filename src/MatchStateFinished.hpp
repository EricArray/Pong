#pragma once

#include "MatchState.hpp"
#include "OptionMenu.hpp"
#include "MatchSceneAction.hpp"

class MatchStateFinished : public MatchState {
public:
    explicit MatchStateFinished(Player winner, VsMode vs_mode);

    MatchSceneAction on_keydown(SDL_Scancode key) override;
    MatchSceneAction on_update() override;
    void on_render(const Renderer& re) override;

private:
    LazyStringTexture winner_texture;
    Uint32 ticks_created;
};