#pragma once

#include <initializer_list>
#include <tuple>
#include <SDL2/SDL_scancode.h>
#include <vector>

#include "Renderer.hpp"
#include "../game/Game.hpp"
#include "LazyStringTexture.hpp"

struct OptionMenuOptionDef {
    std::string description;
    SDL_Scancode key;
};

struct OptionMenuOption {
    OptionMenuOption(std::string&& description, SDL_Scancode key) :
        texture(std::move(description)), key(key) {}

    OptionMenuOption(OptionMenuOption&& other) :
        texture(std::move(other.texture)), key(other.key) {}

    LazyStringTexture texture;
    SDL_Scancode key;
};

class OptionMenu {
public:
    OptionMenu(std::string&& title, const std::vector<OptionMenuOptionDef>& option_defs);

    void render(const Renderer& re, const SDL_Rect& dst);

private:
    LazyStringTexture title_tex;
    std::vector<OptionMenuOption> options;
};
