#include "OptionMenu.hpp"
#include "common.hpp"

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

void OptionMenu::render(const RenderEngine& re, int x, int y) {
    re.render_texture(this->title_tex.get(re), x, y);

    re.render_rect(
        rect(x + 0, y + 32, 512, static_cast<int>(this->options.size() * 32) + 20),
        FORE_COLOR
    );

    int i = 0;
    for (auto& option : this->options) {
        re.render_texture(option.texture.get(re), x + 10, y + 42 + i * 32);
        i += 1;
    }
}
