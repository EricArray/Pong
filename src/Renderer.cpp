#include "Renderer.hpp"
#include "common.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>

using namespace std::string_literals;

const char* const Renderer::WINDOW_TITLE = "Pong";
const int Renderer::WINDOW_W = 1024;
const int Renderer::WINDOW_H = 720;

static const Uint32 RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

void render_engine_test(Renderer& re);

Window create_window() {
    auto window = SDL_CreateWindow(
        Renderer::WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        Renderer::WINDOW_W, Renderer::WINDOW_H,
        0
    );
    if (!window) {
        throw sdl_exception();
    }
    return Window(window, &SDL_DestroyWindow);
}

RendererPtr create_renderer(SDL_Window& window) {
    auto renderer = SDL_CreateRenderer(&window, -1, RENDERER_FLAGS);
    if (!renderer) {
        throw sdl_exception();
    }
    return RendererPtr(renderer, &SDL_DestroyRenderer);
}

Font load_font() {
    TTF_Font* font = TTF_OpenFont("font.ttf", FONT_SIZE);
    if (!font) {
        throw ttf_exception();
    }
    return Font(font, &TTF_CloseFont);
}

Renderer::Renderer() :
    window(create_window()), renderer(create_renderer(*this->window)), font(load_font()) {
    render_engine_test(*this);
}

void Renderer::clear() const {
    this->set_render_color(BLACK);
    if (SDL_RenderClear(this->renderer.get()) < 0) {
        throw sdl_exception();
    }
}

void Renderer::present() const {
    SDL_RenderPresent(this->renderer.get());
}

Texture Renderer::create_text_texture(const std::string& text) const {
    auto fixed_text = text.length() > 0 ? text.c_str() : " ";
    SDL_Surface* surface = TTF_RenderText_Blended(this->font.get(), fixed_text, FORE_COLOR);
    if (!surface) {
        throw ttf_exception();
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer.get(), surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        throw std::runtime_error("Error creating texture from surface: "s + SDL_GetError());
    }

    return Texture(texture);
}

void Renderer::render_line(const SDL_Point& a, const SDL_Point& b, SDL_Color color) const {
    this->set_render_color(color);
    if (SDL_RenderDrawLine(this->renderer.get(), a.x, a.y, b.x, b.y) < 0) {
        throw sdl_exception();
    }
}

void Renderer::render_rect(const SDL_Rect& dst, SDL_Color border_color, std::optional<SDL_Color> fill_color) const {
    if (fill_color) {
        this->set_render_color(*fill_color);
        if (SDL_RenderFillRect(this->renderer.get(), &dst) < 0) {
            throw sdl_exception();
        }
    }

    this->set_render_color(border_color);
    if (SDL_RenderDrawRect(this->renderer.get(), &dst) < 0) {
        throw sdl_exception();
    }
}

void Renderer::render_circle(const SDL_Point& center, const SDL_Point& size, SDL_Color color,
                             std::optional<SDL_Color> fill_color) const {
    if (fill_color) {
        auto& fill = *fill_color;
        filledEllipseRGBA(this->renderer.get(), center.x, center.y, size.x, size.y, fill.r, fill.g, fill.b, fill.a);
    }
    ellipseRGBA(this->renderer.get(), center.x, center.y, size.x, size.y, color.r, color.g, color.b, color.a);
}

void Renderer::render_texture(const Texture& texture, const SDL_Rect& dst) const {
    SDL_Rect src_rect = texture.bounding_box();
    if (SDL_RenderCopy(this->renderer.get(), texture.get(), &src_rect, &dst) < 0) {
        throw std::runtime_error("Error rendering texture: "s + SDL_GetError());
    }
}

void Renderer::set_render_color(SDL_Color color) const {
    if (SDL_SetRenderDrawColor(this->renderer.get(), color.r, color.g, color.b, color.a) < 0) {
        throw sdl_exception();
    }
}

void Renderer::set_view_port(const SDL_Rect& rect) const {
    if (SDL_RenderSetViewport(this->renderer.get(), &rect) < 0) {
        throw sdl_exception();
    }
}

void Renderer::clear_view_port() const {
    if (SDL_RenderSetViewport(this->renderer.get(), nullptr) < 0) {
        throw sdl_exception();
    }
}

void render_engine_test(Renderer& re) {
    re.clear();

    Texture textTexture = re.create_text_texture("Some text 1234567890!\"#$%&/()=?");

    re.render_rect(rect(10, 10, 300, 300), rgba(10, 23, 54, 95), std::nullopt);
    re.render_rect(rect(-10, -10, 300, 300), rgba(10, 23, 54, 95), rgba(1, 2, 3, 4));
    re.render_rect(rect(10, 10, 9999, 9999), rgba(10, 23, 54, 95), std::nullopt);

    re.render_texture(textTexture, textTexture.bounding_box() + point(0, 0));
    re.render_texture(textTexture, textTexture.bounding_box() + point(10, 10));
    re.render_texture(textTexture, textTexture.bounding_box() + point(-10, -10));
    re.render_texture(textTexture, textTexture.bounding_box() + point(9999, 9999));

    re.set_view_port(rect(10, 10, 100, 100));
    re.render_texture(textTexture, textTexture.bounding_box() + point(-10, -10));
    re.render_texture(textTexture, textTexture.bounding_box() + point(9999, 9999));
    re.clear_view_port();

    re.present();
}