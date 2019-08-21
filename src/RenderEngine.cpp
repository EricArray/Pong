#include "RenderEngine.hpp"
#include "common.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>

using namespace std::string_literals;

const char* const RenderEngine::WINDOW_TITLE = "Pong";
const int RenderEngine::WINDOW_WIDTH = 1024;
const int RenderEngine::WINDOW_HEIGHT = 720;
static const Uint32 RENDERER_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

void render_engine_test(RenderEngine& re);

Window create_window() {
    auto window = SDL_CreateWindow(
        RenderEngine::WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        RenderEngine::WINDOW_WIDTH, RenderEngine::WINDOW_HEIGHT,
        0
    );
    if (!window) {
        throw sdl_exception();
    }
    return Window(window, &SDL_DestroyWindow);
}

Renderer create_renderer(SDL_Window& window) {
    auto renderer = SDL_CreateRenderer(&window, -1, RENDERER_FLAGS);
    if (!renderer) {
        throw sdl_exception();
    }
    return Renderer(renderer, &SDL_DestroyRenderer);
}

Font load_font() {
    TTF_Font* font = TTF_OpenFont("font.ttf", 32);
    if (!font) {
        throw ttf_exception();
    }
    return Font(font, &TTF_CloseFont);
}

RenderEngine::RenderEngine() :
    window(create_window()), renderer(create_renderer(*this->window)), font(load_font()) {
    render_engine_test(*this);
}

void RenderEngine::clear() const {
    this->set_render_color(BLACK);
    if (SDL_RenderClear(this->renderer.get()) < 0) {
        throw sdl_exception();
    }
}

void RenderEngine::present() const {
    SDL_RenderPresent(this->renderer.get());
}

Texture RenderEngine::create_text_texture(const std::string& text) const {
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

void RenderEngine::render_line(const SDL_Point& a, const SDL_Point& b, SDL_Color color) const {
    this->set_render_color(color);
    if (SDL_RenderDrawLine(this->renderer.get(), a.x, a.y, b.x, b.y) < 0) {
        throw sdl_exception();
    }
}

void RenderEngine::render_rect(const SDL_Rect& rect, SDL_Color color) const {
    this->set_render_color(color);
    if (SDL_RenderDrawRect(this->renderer.get(), &rect) < 0) {
        throw sdl_exception();
    }
}

void RenderEngine::render_circle(const SDL_Point& center, float radius, SDL_Color color) const {
    filledCircleRGBA(this->renderer.get(), center.x, center.y, radius, color.r, color.g, color.b, color.a);
}

void RenderEngine::render_texture(const Texture& texture, int x, int y) const {
    SDL_Rect src_rect = texture.bounding_box();
    SDL_Rect dst_rect = src_rect;
    dst_rect.x = x;
    dst_rect.y = y;
    if (SDL_RenderCopy(this->renderer.get(), texture.get(), &src_rect, &dst_rect) < 0) {
        throw std::runtime_error("Error rendering texture: "s + SDL_GetError());
    }
}

void RenderEngine::set_render_color(SDL_Color color) const {
    if (SDL_SetRenderDrawColor(this->renderer.get(), color.r, color.g, color.b, color.a) < 0) {
        throw sdl_exception();
    }
}

void RenderEngine::set_view_port(const SDL_Rect& rect) const {
    if (SDL_RenderSetViewport(this->renderer.get(), &rect) < 0) {
        throw sdl_exception();
    }
}

void RenderEngine::clear_view_port() const {
    if (SDL_RenderSetViewport(this->renderer.get(), nullptr) < 0) {
        throw sdl_exception();
    }
}

void render_engine_test(RenderEngine& re) {
    re.clear();

    Texture textTexture = re.create_text_texture("Some text 1234567890!\"#$%&/()=?");

    re.render_rect(rect(10, 10, 300, 300), rgba(10, 23, 54, 95));
    re.render_rect(rect(-10, -10, 300, 300), rgba(10, 23, 54, 95));
    re.render_rect(rect(10, 10, 9999, 9999), rgba(10, 23, 54, 95));

    re.render_texture(textTexture, 0, 0);
    re.render_texture(textTexture, 10, 10);
    re.render_texture(textTexture, -10, -10);
    re.render_texture(textTexture, 9999, 9999);

    re.set_view_port(rect(10, 10, 100, 100));
    re.render_texture(textTexture, -10, -10);
    re.render_texture(textTexture, 9999, 9999);
    re.clear_view_port();

    re.present();
}