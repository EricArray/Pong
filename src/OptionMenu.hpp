#pragma once

#include <initializer_list>
#include <tuple>
#include <SDL2/SDL_scancode.h>
#include <vector>

#include "RenderEngine.hpp"
#include "Game.hpp"
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

    void render(const RenderEngine& re, int x, int y);

private:
    LazyStringTexture title_tex;
    std::vector<OptionMenuOption> options;
};