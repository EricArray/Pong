#pragma once

#include "MatchState.hpp"
#include "../core/OptionMenu.hpp"
#include "MatchSceneAction.hpp"
#include "Player.hpp"

class MatchStateFinished : public MatchState {
public:
    explicit MatchStateFinished(Player winner, VsMode vs_mode);

    MatchSceneAction on_event(const SDL_Event& event) override;
    MatchSceneAction on_update() override;
    void on_render(const Renderer& re) override;

private:
    LazyStringTexture winner_texture;
    Uint32 ticks_created;
};