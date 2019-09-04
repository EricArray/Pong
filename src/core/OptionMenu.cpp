#include "OptionMenu.hpp"
#include "../common.hpp"

#include <string>

using namespace std::string_literals;

std::vector<OptionMenuOption> generate_options(const std::vector<OptionMenuOptionDef>& option_defs) {
    std::vector<OptionMenuOption> options;
    options.reserve(option_defs.size());
    for (auto& option : option_defs) {
        auto key_name = SDL_GetScancodeName(option.key);
        auto full_description = "["s + key_name + "]  "s + option.description;
        options.emplace_back(std::move(full_description), option.key);
    }
    return options;
}

OptionMenu::OptionMenu(std::string&& title, const std::vector<OptionMenuOptionDef>& option_defs) :
    title_tex(std::move(title)),
    options(generate_options(option_defs)) {
}

void OptionMenu::render(const Renderer& re, const SDL_Rect& dst) {
    auto& title = this->title_tex.get(re);
    re.render_texture(title, center_rect(title.size(), rect(dst.x, dst.y, dst.w, FONT_SIZE)));

    re.render_rect(
        rect(dst.x, dst.y + FONT_SIZE, dst.w, dst.h - FONT_SIZE),
        FORE_COLOR, MENU_COLOR);

    int i = 0;
    for (auto& option : this->options) {
        auto& texture = option.texture.get(re);
        re.render_texture(texture, texture.bounding_box() + point(dst.x + 10, dst.y + 42 + i * 32));
        i += 1;
    }
}
