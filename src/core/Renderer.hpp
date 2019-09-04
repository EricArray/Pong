#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <functional>
#include "Texture.hpp"

using Window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>;
using RendererPtr = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>;
using Font = std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>>;

class OptionMenu;

class Renderer {
public:
    static const char* const WINDOW_TITLE;
    static const int WINDOW_W;
    static const int WINDOW_H;

    Renderer();

    void clear() const;
    void present() const;

    void render_line(const SDL_Point& a, const SDL_Point& b, SDL_Color color) const;
    void render_rect(const SDL_Rect& dst, SDL_Color border_color, std::optional<SDL_Color> fill_color) const;
    void render_circle(const SDL_Point& center, const SDL_Point& size, SDL_Color color, std::optional<SDL_Color> fill_color) const;
    void render_texture(const Texture& texture, const SDL_Rect& dst) const;

    void set_view_port(const SDL_Rect& rect) const;
    void clear_view_port() const;

    [[nodiscard]] Texture create_text_texture(const std::string& text) const;

private:
    void set_render_color(SDL_Color color) const;

    Window window;
    RendererPtr renderer;
    Font font;
};
