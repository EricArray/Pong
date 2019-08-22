#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <future>

using namespace std::string_literals;


inline constexpr SDL_Point point(int x, int y) noexcept {
    return {x, y};
}

inline constexpr SDL_Point operator + (const SDL_Point& a, const SDL_Point& b) noexcept {
    return point(a.x + b.x, a.y + b.y);
}

inline constexpr SDL_Point operator - (const SDL_Point& a, const SDL_Point& b) noexcept {
    return point(a.x - b.x, a.y - b.y);
}

inline constexpr SDL_Rect rect(int x, int y, int w, int h) noexcept {
    return {x, y, w, h};
}

inline constexpr SDL_Rect operator + (const SDL_Rect& r, const SDL_Point& p) noexcept {
    return rect(r.x + p.x, r.y + p.y, r.w, r.h);
}

inline constexpr SDL_Rect operator - (const SDL_Rect& r, const SDL_Point& p) noexcept {
    return rect(r.x - p.x, r.y - p.y, r.w, r.h);
}

inline constexpr SDL_Rect center_rect(const SDL_Point& smaller_size, const SDL_Rect& into) noexcept {
    auto diff_w = into.w - smaller_size.x;
    auto diff_h = into.h - smaller_size.y;
    return rect(into.x + diff_w / 2, into.y + diff_h / 2, smaller_size.x, smaller_size.y);
}

inline constexpr SDL_Color rgba(Uint8 r, Uint8 g, Uint8 b, Uint8 a) noexcept {
    return {r, g, b, a};
}

extern const int FONT_SIZE;

extern const SDL_Color FORE_COLOR;
extern const SDL_Color MENU_COLOR;
extern const SDL_Color FIELD_COLOR;
extern const SDL_Color BLACK;

inline std::runtime_error sdl_exception() {
    return std::runtime_error(SDL_GetError());
}

inline std::runtime_error ttf_exception() {
    return std::runtime_error(TTF_GetError());
}


inline std::runtime_error unexpected() {
    throw std::runtime_error("Unexpected value");
}

inline void fail(const std::string& error) {
    throw std::runtime_error("Test failed: "s + error);
}
